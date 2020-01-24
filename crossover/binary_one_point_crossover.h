//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_BINARY_ONE_POINT_CROSSOVER_H
#define GX_BINARY_ONE_POINT_CROSSOVER_H

#include "binary_crossover_factory.h"
#include "../core/app.h"

namespace gx
{
    template <typename T, typename V>
    struct binary_one_point_crossover : binary_crossover<T, V>
    {
        explicit binary_one_point_crossover(float probability);

        void produce_one_children(T* first, T* second, size_t size, T* result) const override;
        void produce_two_children(T* first, T* second, size_t size, T* result_first, T* result_second) const override;
        void produce_one_children_batch(T* first, T* second, size_t batch_size, size_t size, T* result) const override;
        void produce_two_children_batch(T* first, T* second, size_t batch_size, size_t size, T* result_first, T* result_second) const override;

        static bool register_type() noexcept ;
        static bool hreg;
    private:
        static V indices_;
    };

    template <typename T, typename V>
    binary_one_point_crossover<T, V>::binary_one_point_crossover(float probability)
            : binary_crossover<T, V>(probability)
    {
    }

    template <typename T, typename V>
    void binary_one_point_crossover<T, V>::produce_one_children(T* first, T* second, size_t size, T* result) const
    {
        auto& engine = app::random_engine();
        constexpr auto vector_size = sizeof(V) / sizeof(T);
        constexpr auto size_t_bits = sizeof(T) * 8;

        const auto point = engine.random1i(0, size * size_t_bits - 1);
        const auto point_index = point / size_t_bits;
        T point_mask = -1;
        point_mask <<= (size_t_bits - point % size_t_bits);

        if (size >= vector_size)
        {
            const auto point_index_v = V(point_index);
            const auto false_mask = V(T(0));
            const auto true_mask = V(T(-1));
            for (size_t i = 0; i < size; i += vector_size)
            {
                V first_v;
                V second_v;

                first_v.load(&first[i]);
                second_v.load(&second[i]);

                const auto current_indices = indices_ + i;

                const auto mask = select(
                        current_indices == point_index_v, point_mask,
                        select(current_indices < point_index_v, true_mask, false_mask));

                ((first_v & mask) ^ (second_v & ~mask)).store(&result[i]);
            }
        }
        else
        {
            const auto false_mask = T(0);
            const auto true_mask = T(-1);
            for (size_t i = 0; i < size; ++i)
            {
                const auto mask = i < point_index ? true_mask : (i == point_index ? point_mask : false_mask);
                result[i] = ((first[i] & mask) ^ (second[i] & ~mask));
            }
        }
    }

    template <typename T, typename V>
    void binary_one_point_crossover<T, V>::produce_two_children(T* first, T* second, size_t size, T* result_first, T* result_second) const
    {
        auto& engine = app::random_engine();
        constexpr auto vector_size = sizeof(V) / sizeof(T);
        constexpr auto size_t_bits = sizeof(T) * 8;

        const auto point = engine.random1i(0, size * size_t_bits - 1);
        const auto point_index = point / size_t_bits;
        T point_mask = -1;
        point_mask <<= (size_t_bits - point % size_t_bits);

        if (size >= vector_size)
        {
            const auto point_index_v = V(point_index);
            const auto false_mask = V(T(0));
            const auto true_mask = V(~false_mask);
            for (size_t i = 0; i < size; i += vector_size)
            {
                V first_v;
                V second_v;

                first_v.load(&first[i]);
                second_v.load(&second[i]);

                const auto current_indices = indices_ + i;

                const auto mask = select(
                        current_indices == point_index_v, point_mask,
                        select(current_indices < point_index_v, true_mask, false_mask));

                V child = V((first_v & mask) ^ (second_v & ~mask));
                child.store(&result_first[i]);
                (~child).store(&result_second[i]);
            }
        }
        else
        {
            const auto false_mask = T(0);
            const auto true_mask = ~false_mask;
            for (auto i = 0ull; i < size; ++i)
            {
                const auto mask = i < point_index ? true_mask : (i == point_index ? point_mask : false_mask);
                result_first[i] = ((first[i] & mask) ^ (second[i] & ~mask));
                result_second[i] = ~result_first[i];
            }
        }
    }

    template <typename T, typename V>
    void binary_one_point_crossover<T, V>::produce_one_children_batch(T* first, T* second,
                                                                      size_t batch_size, size_t size, T* result) const
    {
        for (size_t i = 0; i < batch_size * size; i += size)
            produce_one_children(first + i, second + i, size, result + i);
    }

    template <typename T, typename V>
    void binary_one_point_crossover<T, V>::produce_two_children_batch(T* first, T* second,
                                                                      size_t batch_size, size_t size, T* result_first, T* result_second) const
    {
        for (size_t i = 0; i < batch_size * size; i += size)
            produce_two_children(first + i, second + i, size, result_first + i, result_second + i);
    }

    template <typename T, typename V>
    bool binary_one_point_crossover<T, V>::register_type() noexcept
    {
        return binary_crossover_factory<T, V>::instance().register_creator(crossover_type::binary_one_point_crossover, [](const crossover_info& info)
        {
            return std::make_unique<binary_one_point_crossover<T, V>>(info.probability);
        });
    }
}


#endif //GX_BINARY_ONE_POINT_CROSSOVER_H
