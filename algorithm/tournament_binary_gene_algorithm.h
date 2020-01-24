//
// Created by Oshikuru on 15.9.2019..
//

#ifndef GX_TOURNAMENT_BINARY_GENE_ALGORITHM_H
#define GX_TOURNAMENT_BINARY_GENE_ALGORITHM_H

#include <mutex>
#include <numeric>
#include "binary_gene_algorithm.h"
#include "../decoder/decoder_factory.h"
#include "../crossover/binary_crossover_factory.h"
#include "../mutation/binary_mutation_factory.h"
#include "../core/app.h"
#include "binary_gene_algorithm_factory.h"

namespace gx
{
    template<typename T, typename V>
    struct tournament_binary_gene_algorithm : binary_gene_algorithm
    {
        tournament_binary_gene_algorithm(
                decoder_ptr<T, V> &&decoder, std::vector<binary_crossover_ptr<T, V>> &&crossovers,
                std::vector<binary_mutation_ptr<T, V>> &&mutations);

        void init_population(size_t population_size) override;
        void run(size_t epochs) override;

        [[nodiscard]] const std::vector<feature> &best() const noexcept override;
        [[nodiscard]] float best_fitness() const noexcept override;
        [[nodiscard]] size_t epoch() const noexcept override;
        std::vector<float> extract_plot_data() override;

        static bool hreg;
        static bool register_type() noexcept ;

    private:
        size_t feature_count_;
        size_t feature_container_count_;
        size_t total_bits_;
        size_t population_size_{0};
        decoder_ptr<T, V> decoder_;
        std::vector<binary_crossover_ptr<T, V>> crossovers_;
        std::vector<binary_mutation_ptr<T, V>> mutations_;

        size_t data_size_{0};
        std::vector<T> data_;
        std::vector<float> fitness_data_;

        std::vector<feature> current_best_;
        size_t epoch_{0};
        float best_fitness_{-std::numeric_limits<float>::infinity()};
        std::vector<float> fitness_history_;
        std::mutex fitness_history_mutex_;
    };

    template<typename T, typename V>
    tournament_binary_gene_algorithm<T, V>::tournament_binary_gene_algorithm(
            decoder_ptr<T, V> &&decoder,
            std::vector<binary_crossover_ptr<T, V>> &&crossovers,
            std::vector<binary_mutation_ptr<T, V>> &&mutations)
            : decoder_(std::move(decoder)), crossovers_(std::move(crossovers)), mutations_(std::move(mutations))
    {
        feature_count_ = decoder_->feature_count();
        total_bits_ = decoder_->total_bit_count();
        // Calculate how much space we need to save our features.
        feature_container_count_ = ((total_bits_ + 7) / 8 + sizeof(T) - 1) / sizeof(T);

        auto total_crossover_probability = std::accumulate(crossovers_.begin(), crossovers_.end(), 0.f,
                                                           [](float &total, binary_crossover_ptr<T, V> &c)
                                                           {
                                                               return total + c->probability;
                                                           });

        if (total_crossover_probability <= 0.f)
            for (auto &crossover : crossovers_)
                crossover->probability = 1.f / crossovers_.size();
        else if (total_crossover_probability != 1.f)
            for (auto &crossover : crossovers_)
                crossover->probability /= total_crossover_probability;

        auto total_mutation_probability = std::accumulate(mutations_.begin(), mutations_.end(), 0.f,
                                                          [](float &total, binary_mutation_ptr<T, V> &m)
                                                          {
                                                              return total + m->probability;
                                                          });

        if (total_mutation_probability <= 0.f)
            for (auto &mutation : mutations_)
                mutation->probability = 1.f / mutations_.size();
        else if (total_mutation_probability != 1.f)
            for (auto &mutation : mutations_)
                mutation->probability /= total_mutation_probability;
    }

    template<typename T, typename V>
    void tournament_binary_gene_algorithm<T, V>::init_population(size_t population_size)
    {
        population_size_ = population_size;
        data_size_ = population_size_ * feature_container_count_;
        constexpr int64_t vector_size = sizeof(V) / sizeof(T);
        const auto real_data_size = (population_size_ * feature_container_count_ + vector_size - 1) & (-vector_size);
        data_.resize(real_data_size);
        fitness_data_.resize(population_size_);
        best_fitness_ = -std::numeric_limits<float>::infinity();
        auto &engine = app::random_engine();
        std::vector<feature> features(feature_count_);

        for (size_t i = 0, j = 0; i < data_size_; i += vector_size)
        {
            engine.random256b().store(&data_[i]);
            while (i + vector_size > j * feature_container_count_ && j < population_size_)
            {
                fitness_data_[j] = decoder_->fitness_value(data_.data() + j * feature_container_count_,
                                                           features.data());
                if (fitness_data_[j] > best_fitness_)
                {
                    best_fitness_ = fitness_data_[j];
                    current_best_ = features;
                }
                ++j;
            }
        }
    }

    template<typename T, typename V>
    void tournament_binary_gene_algorithm<T, V>::run(size_t epochs)
    {
        auto &engine = app::random_engine();
        std::vector<int32_t> indices(8);
        std::vector<float> crossovers_probs(4);
        std::vector<int32_t> crossovers_indices(4);
        std::vector<float> mutations_probs(4);
        std::vector<int32_t> mutations_indices(4);
        constexpr int64_t vector_size = sizeof(V) / sizeof(T);
        std::vector<T> child((feature_container_count_ + vector_size - 1) & (-vector_size));
        fitness_history_.clear();
        std::vector<feature> features(feature_count_);

        for (epoch_ = 0; epoch_ < epochs; epoch_ += 4)
        {
            engine.random8i(0, population_size_ - 1).store(indices.data());
            if (crossovers_.size() > 1) engine.random4f().store(crossovers_probs.data());
            if (mutations_.size() > 1) engine.random4f().store(mutations_probs.data());
            for (size_t i = 0; i < crossovers_indices.size(); ++i)
            {
                if (crossovers_.size() == 1 && mutations_.size() == 1) break;

                auto total_probability = 0.f;
                if (crossovers_.size() > 1)
                {
                    for (auto j = 0u; j < crossovers_.size(); ++j)
                    {
                        if (crossovers_[j]->probability == 0.f)
                            continue;
                        total_probability += crossovers_[j]->probability;
                        if (crossovers_probs[i] <= total_probability)
                        {
                            crossovers_indices[i] = j;
                            break;
                        }
                    }
                }

                total_probability = 0.f;
                if (mutations_.size() > 1)
                {
                    for (auto j = 0u; j < mutations_.size(); ++j)
                    {
                        if (mutations_[j]->probability == 0.f)
                            continue;
                        total_probability += mutations_[j]->probability;
                        if (mutations_probs[i] <= total_probability)
                        {
                            mutations_indices[i] = j;
                            break;
                        }
                    }
                }
            }

            for (auto i = 0; i < 4; ++i)
            {
                crossovers_[crossovers_indices[i]]->produce_one_children(
                        data_.data() + indices[i * 2] * feature_container_count_,
                        data_.data() + indices[i * 2 + 1] * feature_container_count_, feature_container_count_,
                        child.data());
                mutations_[mutations_indices[i]]->mutate(child.data(), feature_container_count_, child.data());

                const auto fitness = decoder_->fitness_value(child.data(), features.data());
                if (fitness_data_[indices[i * 2]] >= fitness_data_[indices[i * 2 + 1]])
                {
                    if (fitness_data_[indices[i * 2 + 1]] < fitness)
                    {
                        fitness_data_[indices[i * 2 + 1]] = fitness;
                        memcpy(data_.data() + indices[i * 2 + 1] * feature_container_count_,
                               child.data(), sizeof(T) * feature_container_count_);
                    }
                }
                else
                {
                    if (fitness_data_[indices[i * 2]] < fitness)
                    {
                        fitness_data_[indices[i * 2]] = fitness;
                        memcpy(data_.data() + indices[i * 2] * feature_container_count_,
                               child.data(), sizeof(T) * feature_container_count_);
                    }
                }

                if (fitness > best_fitness_)
                {
                    best_fitness_ = fitness;
                    current_best_ = features;
                }

                {
                    std::lock_guard<std::mutex> guard(fitness_history_mutex_);
                    fitness_history_.push_back(best_fitness_);
                }
            }
        }
    }

    template<typename T, typename V>
    const std::vector<feature> &tournament_binary_gene_algorithm<T, V>::best() const noexcept
    {
        return current_best_;
    }

    template<typename T, typename V>
    float tournament_binary_gene_algorithm<T, V>::best_fitness() const noexcept
    {
        return best_fitness_;
    }

    template<typename T, typename V>
    size_t tournament_binary_gene_algorithm<T, V>::epoch() const noexcept
    {
        return epoch_;
    }

    template<typename T, typename V>
    std::vector<float> tournament_binary_gene_algorithm<T, V>::extract_plot_data()
    {
        std::lock_guard<std::mutex> guard(fitness_history_mutex_);
        return std::move(fitness_history_);
    }

    template<typename T, typename V>
    bool tournament_binary_gene_algorithm<T, V>::register_type() noexcept
    {
        return binary_gene_algorithm_factory<T, V>::instance().register_creator(algorithm_type::tournament,
        [](const decoder_info &decoder_info,
           const std::vector<crossover_info> &crossover_info,
           const std::vector<mutation_info> &mutation_info, void* args)
        {
            std::vector<gx::binary_crossover_ptr<T, V>> crossovers;
            std::vector<gx::binary_mutation_ptr<T, V>> mutations;

            auto decoder = gx::decoder_factory<T, V>::instance().create(
                    decoder_info.type,
                    decoder_info);

            for (auto &crossover : crossover_info)
                crossovers.emplace_back(
                        gx::binary_crossover_factory<T, V>::instance().create(
                                crossover.type,
                                crossover));

            for (auto &mutation : mutation_info)
                mutations.emplace_back(
                        gx::binary_mutation_factory<T, V>::instance().create(
                                mutation.type,
                                mutation));

            return new tournament_binary_gene_algorithm<T, V>(
                    std::move(decoder),
                    std::move(crossovers),
                    std::move(mutations));
        });
    }
}

#endif //GX_TOURNAMENT_BINARY_GENE_ALGORITHM_H
