//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_BINARY_ROTATE_MIX_MUTATION_H
#define GX_BINARY_ROTATE_MIX_MUTATION_H

#include "../core/app.h"
#include "binary_mutation_factory.h"

namespace gx
{
    struct rotl
    {
        static uint8_t shift(uint8_t value, uint32_t shift)
        {
            return (value << shift) | (value >> (8 - shift));
        }

        static uint16_t shift(uint16_t value, uint32_t shift)
        {
            return (value << shift) | (value >> (16 - shift));
        }

        static uint32_t shift(uint32_t value, uint32_t shift)
        {
            return _rotl(value, shift);
        }

        static uint64_t shift(uint64_t value, uint32_t shift)
        {
            return _rotl64(value, shift);
        }
    };

    struct rotr
    {
        static uint8_t shift(uint8_t value, uint32_t shift)
        {
            return (value >> shift) | (value << (8 - shift));
        }

        static uint16_t shift(uint16_t value, uint32_t shift)
        {
            return (value >> shift) | (value << (16 - shift));
        }

        static uint32_t shift(uint32_t value, uint32_t shift)
        {
            return _rotr(value, shift);
        }

        static uint64_t shift(uint64_t value, uint32_t shift)
        {
            return _rotr64(value, shift);
        }
    };

    template<typename T, typename V>
    struct binary_rotate_mix_mutation : binary_mutation<T, V>
    {
        explicit binary_rotate_mix_mutation(float probability);
        void mutate(T *value, size_t size, T *result) override;
        void batch_mutate(T *batch, size_t batch_size, size_t size, T *result) override;

        static bool register_type() noexcept ;
        static bool hreg;
    };

    template<typename T, typename V>
    binary_rotate_mix_mutation<T, V>::binary_rotate_mix_mutation(float probability) :
            binary_mutation<T, V>(probability)
    {
    }

    template<typename T, typename V>
    void binary_rotate_mix_mutation<T, V>::mutate(T *value, size_t size, T *result)
    {
        auto &engine = app::random_engine();
        constexpr auto vector_size = sizeof(V) / sizeof(T);

        if (size >= vector_size)
        {
            for (size_t i = 0; i < size; i += vector_size)
            {
                V value_v;
                value_v.load(&value[i]);

                const auto left_rotate = engine.random1i(0, sizeof(T) * 8 - 1);
                const auto right_rotate = -engine.random1i(0, sizeof(T) * 8 - 1);

                rotate_left(rotate_left(value_v, left_rotate), right_rotate).store(&result[i]);
            }
        }
        else
        {
            for (size_t i = 0; i < size; ++i)
            {
                const auto left_rotate = engine.random1i(0, sizeof(T) * 8 - 1);
                const auto right_rotate = engine.random1i(0, sizeof(T) * 8 - 1);

                result[i] = rotr::shift(rotl::shift(value[i], left_rotate), right_rotate);
            }
        }
    }

    template<typename T, typename V>
    void binary_rotate_mix_mutation<T, V>::batch_mutate(T *batch, size_t batch_size, size_t size, T *result)
    {
        mutate(batch, batch_size, result);
    }

    template<typename T, typename V>
    bool binary_rotate_mix_mutation<T, V>::register_type() noexcept
    {
        return binary_mutation_factory<T, V>::instance().register_creator(mutation_type::binary_rotate_mix, [](const mutation_info &info)
        {
            return std::make_unique<binary_rotate_mix_mutation<T, V>>(
                      info.probability);
        });
    }
}


#endif //GX_BINARY_ROTATE_MIX_MUTATION_H
