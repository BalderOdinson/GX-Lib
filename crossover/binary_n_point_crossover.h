//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_BINARY_N_POINT_CROSSOVER_H
#define GX_BINARY_N_POINT_CROSSOVER_H

#include <set>
#include "../core/app.h"
#include "binary_crossover_factory.h"
#include "binary_n_point_crossover_args.h"

namespace gx
{
    template <typename T, typename V>
    struct binary_n_point_crossover : binary_crossover<T, V>
    {
        explicit binary_n_point_crossover(float probability, uint32_t n);

        void produce_one_children(T* first, T* second, size_t size, T* result) const override;
        void produce_two_children(T* first, T* second, size_t size, T* result_first, T* result_second) const override;
        void produce_one_children_batch(T* first, T* second, size_t batch_size, size_t size, T* result) const override;
        void produce_two_children_batch(T* first, T* second, size_t batch_size, size_t size, T* result_first, T* result_second) const override;

        static bool register_type() noexcept;
        static bool hreg;
    private:
        static V indices_;
        uint32_t n_;
    };

    template <typename T, typename V>
    binary_n_point_crossover<T, V>::binary_n_point_crossover(float probability, uint32_t n)
            : binary_crossover<T, V>(probability), n_(n)
    {
    }

    template <typename T, typename V>
    void binary_n_point_crossover<T, V>::produce_one_children(T* first, T* second, size_t size, T* result) const
    {
        auto& engine = app::random_engine();
        constexpr auto vector_size = sizeof(V) / sizeof(T);
        constexpr auto size_t_bits = sizeof(T) * 8;

        std::set<uint32_t> indices;
        for (size_t i = 0; i < n_; ++i)
            indices.insert(engine.random1i(0, size * size_t_bits - 1));

        auto first_index = *indices.begin() / size_t_bits;

        if (size >= vector_size)
        {
            auto current_mask = V(T(-1));
            auto crossover_point = V(first_index);
            auto is_true_mask = true;
            for (size_t i = 0; i < size; i += vector_size)
            {
                V first_v;
                V second_v;

                first_v.load(&first[i]);
                second_v.load(&second[i]);

                const auto current_indices = indices_ + i;
                auto mask = select(current_indices < crossover_point, current_mask, ~current_mask);

                while (first_index < i + vector_size)
                {
                    auto point_mask = is_true_mask ?
                                      T(-1) << (size_t_bits - (*indices.begin() % size_t_bits)) :
                                      T(-1) >> *indices.begin() % size_t_bits;

                    auto prev_index = first_index;

                    current_mask = ~current_mask;
                    is_true_mask = !is_true_mask;
                    indices.erase(indices.begin());
                    first_index = indices.empty() ? size + vector_size : *indices.begin() / size_t_bits;

                    while (prev_index == first_index)
                    {
                        prev_index = first_index;
                        auto new_point_mask = is_true_mask ?
                                              T(-1) << (size_t_bits - (*indices.begin() % size_t_bits)) :
                                              T(-1) >> *indices.begin() % size_t_bits;
                        point_mask = is_true_mask ? (point_mask & new_point_mask) : (point_mask | new_point_mask);

                        current_mask = ~current_mask;
                        is_true_mask = !is_true_mask;
                        indices.erase(indices.begin());
                        first_index = indices.empty() ? size + vector_size : *indices.begin() / size_t_bits;
                    }

                    const auto point_mask_v = V(point_mask);
                    mask = select(current_indices > crossover_point, current_mask, select(current_indices == crossover_point, point_mask_v, mask));
                    crossover_point = V(first_index);
                }

                ((first_v & mask) ^ (second_v & ~mask)).store(&result[i]);
            }
        }
        else
        {
            auto current_mask = T(-1);
            for (size_t i = 0; i < size; ++i)
            {
                auto mask = current_mask;
                if(i == first_index)
                {
                    mask =
                            current_mask == T(-1) ?
                            T(-1) << (size_t_bits - (*indices.begin() % size_t_bits)) :
                            T(-1) >> *indices.begin() % size_t_bits;

                    current_mask = ~current_mask;
                    indices.erase(indices.begin());
                    first_index = indices.empty() ? size : *indices.begin() / size_t_bits;

                    while (i == first_index)
                    {
                        auto new_mask = current_mask == T(-1) ?
                                        T(-1) << (size_t_bits - (*indices.begin() % size_t_bits)) :
                                        T(-1) >> *indices.begin() % size_t_bits;

                        mask = current_mask == T(-1) ? (mask & new_mask) : (mask | new_mask);

                        current_mask = ~current_mask;
                        indices.erase(indices.begin());
                        first_index = indices.empty() ? size : *indices.begin() / size_t_bits;
                    }

                }
                result[i] = ((first[i] & mask) ^ (second[i] & ~mask));
            }
        }
    }

    template <typename T, typename V>
    void binary_n_point_crossover<T, V>::produce_two_children(T* first, T* second, size_t size, T* result_first, T* result_second) const
    {
        auto& engine = app::random_engine();
        constexpr auto vector_size = sizeof(V) / sizeof(T);
        constexpr auto size_t_bits = sizeof(T) * 8;

        std::set<uint32_t> indices;
        for (size_t i = 0; i < n_; ++i)
            indices.insert(engine.random1i(0, size * size_t_bits - 1));

        auto first_index = *indices.begin() / size_t_bits;

        if (size >= vector_size)
        {
            auto current_mask = V(T(-1));
            auto crossover_point = V(first_index);
            auto is_true_mask = true;
            for (size_t i = 0; i < size; i += vector_size)
            {
                V first_v;
                V second_v;

                first_v.load(&first[i]);
                second_v.load(&second[i]);

                const auto current_indices = indices_ + i;
                auto mask = select(current_indices < crossover_point, current_mask, ~current_mask);

                while (first_index < i + vector_size)
                {
                    auto point_mask = is_true_mask ?
                                      T(-1) << (size_t_bits - (*indices.begin() % size_t_bits)) :
                                      T(-1) >> *indices.begin() % size_t_bits;

                    auto prev_index = first_index;

                    current_mask = ~current_mask;
                    is_true_mask = !is_true_mask;
                    indices.erase(indices.begin());
                    first_index = indices.empty() ? size + vector_size : *indices.begin() / size_t_bits;

                    while (prev_index == first_index)
                    {
                        prev_index = first_index;
                        auto new_point_mask = is_true_mask ?
                                              T(-1) << (size_t_bits - (*indices.begin() % size_t_bits)) :
                                              T(-1) >> *indices.begin() % size_t_bits;
                        point_mask = is_true_mask ? (point_mask & new_point_mask) : (point_mask | new_point_mask);

                        current_mask = ~current_mask;
                        is_true_mask = !is_true_mask;
                        indices.erase(indices.begin());
                        first_index = indices.empty() ? size + vector_size : *indices.begin() / size_t_bits;
                    }

                    const auto point_mask_v = V(point_mask);
                    mask = select(current_indices > crossover_point, current_mask, select(current_indices == crossover_point, point_mask_v, mask));
                    crossover_point = V(first_index);
                }

                V child = V((first_v & mask) ^ (second_v & ~mask));
                child.store(&result_first[i]);
                (~child).store(&result_second[i]);
            }
        }
        else
        {
            auto current_mask = T(-1);
            for (size_t i = 0; i < size; ++i)
            {
                auto mask = current_mask;
                if (i == first_index)
                {
                    mask =
                            current_mask == T(-1) ?
                            T(-1) << (size_t_bits - (*indices.begin() % size_t_bits)) :
                            T(-1) >> *indices.begin() % size_t_bits;

                    current_mask = ~current_mask;
                    indices.erase(indices.begin());
                    first_index = indices.empty() ? size : *indices.begin() / size_t_bits;

                    while (i == first_index)
                    {
                        auto new_mask = current_mask == T(-1) ?
                                        T(-1) << (size_t_bits - (*indices.begin() % size_t_bits)) :
                                        T(-1) >> *indices.begin() % size_t_bits;

                        mask = current_mask == T(-1) ? (mask & new_mask) : (mask | new_mask);

                        current_mask = ~current_mask;
                        indices.erase(indices.begin());
                        first_index = indices.empty() ? size : *indices.begin() / size_t_bits;
                    }
                }
                result_first[i] = ((first[i] & mask) ^ (second[i] & ~mask));
                result_second[i] = ~result_first[i];
            }
        }
    }

    template <typename T, typename V>
    void binary_n_point_crossover<T, V>::produce_one_children_batch(T* first, T* second,
                                                                    size_t batch_size, size_t size, T* result) const
    {
        for (size_t i = 0; i < batch_size * size; i += size)
            produce_one_children(first + i, second + i, size, result + i);
    }

    template <typename T, typename V>
    void binary_n_point_crossover<T, V>::produce_two_children_batch(T* first, T* second,
                                                                    size_t batch_size, size_t size, T* result_first, T* result_second) const
    {
        for (size_t i = 0; i < batch_size * size; i += size)
            produce_two_children(first + i, second + i, size, result_first + i, result_second + i);
    }

    template <typename T, typename V>
    bool binary_n_point_crossover<T, V>::register_type() noexcept
    {
        return binary_crossover_factory<T, V>::instance().register_creator(crossover_type ::binary_n_point_crossover, [](const crossover_info& info)
        {
            auto n = 1u;
            auto args = static_cast<binary_n_point_crossover_args*>(info.args);
            if(args)
                n = args->n;
            return std::make_unique<binary_n_point_crossover<T, V>>(info.probability, n);
        });
    }
}


#endif //GX_BINARY_N_POINT_CROSSOVER_H
