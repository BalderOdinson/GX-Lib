//
// Created by Oshikuru on 15.9.2019..
//

#ifndef GX_DEFAULT_DECODER_H
#define GX_DEFAULT_DECODER_H

#include <vector>
#include "decoder.h"
#include "../gene/feature_info.h"
#include "../gene/feature_decoder.h"
#include "fitness_evaluator_delegate.h"
#include "decoder_factory.h"
#include "default_decoder_args.h"
#include "../core/gx_exception.h"

namespace gx
{
    template<typename T, typename V>
    struct default_decoder : decoder<T, V>
    {
        default_decoder(const std::vector<feature_info> &features, fitness_evaluator_delegate fitness_evaluator,
                        batch_fitness_evaluator_delegate batch_fitness_evaluator) noexcept;

        float fitness_value(T *gene, feature* decoded_features) const override;
        void batch_fitness_value(T *gene, size_t batch_size, float* result, feature* decoded_features) const override;
        void decode(T* gene,  feature* result) const override;

        [[nodiscard]] size_t total_bit_count() const noexcept override;
        [[nodiscard]] size_t feature_count() const noexcept override;

        static bool register_type() noexcept;
        static bool hreg;
    private:
        std::vector<feature_decoder> feature_decoders_;
        fitness_evaluator_delegate fitness_evaluator_;
        batch_fitness_evaluator_delegate batch_fitness_evaluator_;
        size_t features_count_;
        size_t total_bits_;
    };

    template<typename T, typename V>
    default_decoder<T, V>::default_decoder(const std::vector<feature_info> &features,
                                           fitness_evaluator_delegate fitness_evaluator,
                                           batch_fitness_evaluator_delegate batch_fitness_evaluator) noexcept
            : fitness_evaluator_(fitness_evaluator), batch_fitness_evaluator_(batch_fitness_evaluator)
    {
        total_bits_ = 0u;
        uint16_t offset = 0u;
        features_count_ = features.size();
        for (size_t i = 0; i < features_count_; ++i)
        {
            if (features[i].type == data_type::floating_point)
                feature_decoders_.emplace_back(
                        feature_decoder::create_floating_point(features[i].precision_f, features[i].min_f,
                                                               features[i].max_f, offset));
            else
                feature_decoders_.emplace_back(
                        feature_decoder::create_integer(features[i].min_i, features[i].max_i, offset));

            total_bits_ += feature_decoders_.back().bit_length();
            offset += feature_decoders_.back().bit_length();
        }
    }

    template<typename T, typename V>
    float default_decoder<T, V>::fitness_value(T *gene, feature* decoded_features) const
    {
        for (size_t i = 0; i < features_count_; ++i)
        {
            if (feature_decoders_[i].type() == data_type::floating_point)
            {
                decoded_features[i].type = data_type::floating_point;
                decoded_features[i].fp_value = feature_decoders_[i].decodef(gene);
            }
            else
            {
                decoded_features[i].type = data_type::integer;
                decoded_features[i].int_value = feature_decoders_[i].decodei(gene);
            }
        }

        return fitness_evaluator_(decoded_features, features_count_);
    }

    template<typename T, typename V>
    void default_decoder<T, V>::batch_fitness_value(T *gene, size_t batch_size,
            float* result, feature* decoded_features) const
    {
        for (size_t j = 0; j < batch_size; ++j)
        {
            for (size_t i = 0; i < features_count_; ++i)
            {
                if (feature_decoders_[i].type() == data_type::floating_point)
                {
                    decoded_features[j * features_count_ + i].type = data_type::floating_point;
                    decoded_features[j * features_count_ + i].fp_value = feature_decoders_[i].decodef(gene);
                }
                else
                {
                    decoded_features[j * features_count_ + i].type = data_type::integer;
                    decoded_features[j * features_count_ + i].int_value = feature_decoders_[i].decodei(gene);
                }
            }
        }

        batch_fitness_evaluator_(decoded_features, features_count_, batch_size, result);
    }

    template<typename T, typename V>
    void default_decoder<T, V>::decode(T *gene, feature *result) const
    {
        for (size_t i = 0; i < features_count_; ++i)
        {
            if (feature_decoders_[i].type() == data_type::floating_point)
            {
                result[i].type = data_type::floating_point;
                result[i].fp_value = feature_decoders_[i].decodef(gene);
            }
            else
            {
                result[i].type = data_type::integer;
                result[i].int_value = feature_decoders_[i].decodei(gene);
            }
        }
    }

    template<typename T, typename V>
    size_t default_decoder<T, V>::total_bit_count() const noexcept
    {
        return total_bits_;
    }

    template<typename T, typename V>
    size_t default_decoder<T, V>::feature_count() const noexcept
    {
        return features_count_;
    }

    template<typename T, typename V>
    bool default_decoder<T, V>::register_type() noexcept
    {
        return decoder_factory<T, V>::instance().register_creator(decoder_type::default_decoder, [](const decoder_info &info)
        {
            auto args = static_cast<default_decoder_args*>(info.args);
            if(!args)
                throw gx::gx_exception(gx::gx_exception_code::null_reference, "No args provided for default decoder!");
            std::vector<feature_info> features(info.gene.features,info.gene.features + info.gene.features_size);

            return std::make_unique<default_decoder<T, V>>(
                    features,
                    args->fitness_evaluator,
                    args->batch_fitness_evaluator);
          });
    }
}


#endif //GX_DEFAULT_DECODER_H
