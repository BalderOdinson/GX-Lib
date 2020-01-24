//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_BINARY_SIMPLE_MUTATION_H
#define GX_BINARY_SIMPLE_MUTATION_H

#include "../core/app.h"
#include "binary_mutation_factory.h"
#include "binary_simple_mutation_args.h"

namespace gx
{
    template <typename T, typename V>
    struct binary_simple_mutation : binary_mutation<T, V>
    {
        binary_simple_mutation(float probability, float mutation_probability);

        void mutate(T* value, size_t size, T* result) override;
        void batch_mutate(T* batch, size_t batch_size, size_t size, T* result) override;

        static bool register_type();
        static bool hreg;

    private:
        float probability_;
        uint32_t factor_;
    };

    template <typename T, typename V>
    binary_simple_mutation<T, V>::binary_simple_mutation(float probability, float mutation_probability) :
            binary_mutation<T, V>(probability),
            probability_(mutation_probability),
            factor_(bit_scan_reverse(static_cast<uint32_t>(1 / mutation_probability)))
    {
    }

    template <typename T, typename V>
    void binary_simple_mutation<T, V>::mutate(T* value, size_t size, T* result)
    {
        auto& engine = app::random_engine();
        constexpr auto vector_size = sizeof(V) / sizeof(T);

        if (size >= vector_size)
        {
            for (size_t i = 0; i < size; i += vector_size)
            {
                V value_v;
                value_v.load(&value[i]);

                auto mask = engine.random256b();
                for (auto j = 0u; j < factor_; ++j)
                    mask &= engine.random256b();

                (value_v ^ V(mask)).store(&result[i]);
            }
        }
        else
        {
            for (size_t i = 0; i < size; ++i)
            {
                auto mask = engine.random32b();
                for (auto j = 0u; j < factor_; ++j)
                    mask &= engine.random32b();

                result[i] = value[i] ^ mask;
            }
        }
    }

    template <typename T, typename V>
    void binary_simple_mutation<T, V>::batch_mutate(T* batch, size_t batch_size, size_t size, T* result)
    {
        mutate(batch, batch_size, result);
    }

    template <typename T, typename V>
    bool binary_simple_mutation<T, V>::register_type()
    {
        return binary_mutation_factory<T, V>::instance().register_creator(mutation_type::binary_simple, [](const mutation_info& info)
        {
            auto probability = 0.5f;
            auto args = static_cast<binary_simple_mutation_args*>(info.args);
            if(args)
                probability = args->probability;
            return std::make_unique<binary_simple_mutation<T, V>>(info.probability, probability);
        });
    }
}


#endif //GX_BINARY_SIMPLE_MUTATION_H
