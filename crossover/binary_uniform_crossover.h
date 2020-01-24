//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_BINARY_UNIFORM_CROSSOVER_H
#define GX_BINARY_UNIFORM_CROSSOVER_H

#include "../core/app.h"
#include "binary_crossover_factory.h"

namespace gx
{
    template <typename T, typename V>
    struct binary_uniform_crossover : binary_crossover<T, V>
    {
        explicit binary_uniform_crossover(float probability);

        void produce_one_children(T* first, T* second, size_t size, T* result) const override;
        void produce_two_children(T* first, T* second, size_t size, T* result_first, T* result_second) const override;
        void produce_one_children_batch(T* first, T* second, size_t batch_size, size_t size, T* result) const override;
        void produce_two_children_batch(T* first, T* second, size_t batch_size, size_t size, T* result_first, T* result_second) const override;

        static bool register_type() noexcept ;
        static bool hreg;
    };

    template <typename T, typename V>
    binary_uniform_crossover<T, V>::binary_uniform_crossover(float probability)
            : binary_crossover<T, V>(probability)
    {
    }

    template <typename T, typename V>
    void binary_uniform_crossover<T, V>::produce_one_children(T* first, T* second, size_t size, T* result) const
    {
        auto& engine = app::random_engine();
        constexpr auto vector_size = sizeof(V) / sizeof(T);

        if(size >= vector_size)
        {
            for (size_t i = 0; i < size; i += vector_size)
            {
                V first_v;
                V second_v;

                first_v.load(&first[i]);
                second_v.load(&second[i]);

                const auto mask = V(engine.random256b());

                ((first_v & mask) ^ (second_v & ~mask)).store(&result[i]);
            }
        }
        else
        {
            for (size_t i = 0; i < size; ++i)
            {
                const auto mask = T(engine.random64b());
                result[i] = ((first[i] & mask) ^ (second[i] & ~mask));
            }
        }
    }

    template <typename T, typename V>
    void binary_uniform_crossover<T, V>::produce_two_children(T* first, T* second, size_t size, T* result_first, T* result_second) const
    {
        auto& engine = app::random_engine();
        constexpr auto vector_size = sizeof(V) / sizeof(T);

        if (size >= vector_size)
        {
            for (size_t i = 0; i < size; i += vector_size)
            {
                V first_v;
                V second_v;

                first_v.load(&first[i]);
                second_v.load(&second[i]);

                const auto mask = V(engine.random256b());

                V child = V((first_v & mask) ^ (second_v & ~mask));
                child.store(&result_first[i]);
                (~child).store(&result_second[i]);
            }
        }
        else
        {
            for (size_t i = 0; i < size; ++i)
            {
                const auto mask = T(engine.random64b());
                result_first[i] = ((first[i] & mask) ^ (second[i] & ~mask));
                result_second[i] = ~result_first[i];
            }
        }
    }

    template <typename T, typename V>
    void binary_uniform_crossover<T, V>::produce_one_children_batch(T* first, T* second,
                                                                    size_t batch_size, size_t size, T* result) const
    {
        produce_one_children(first, second, batch_size, result);
    }

    template <typename T, typename V>
    void binary_uniform_crossover<T, V>::produce_two_children_batch(T* first, T* second,
                                                                    size_t batch_size, size_t size, T* result_first, T* result_second) const
    {
        produce_two_children(first, second, batch_size, result_first, result_second);
    }

    template <typename T, typename V>
    bool binary_uniform_crossover<T, V>::register_type() noexcept
    {
        return binary_crossover_factory<T, V>::instance().register_creator(crossover_type ::binary_uniform_crossover, [](const crossover_info& info)
        {
            return std::make_unique<binary_uniform_crossover<T, V>>(info.probability);
        });
    }
}


#endif //GX_BINARY_UNIFORM_CROSSOVER_H
