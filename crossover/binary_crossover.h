//
// Created by Oshikuru on 12.9.2019..
//

#ifndef GX_BINARY_CROSSOVER_H
#define GX_BINARY_CROSSOVER_H

#include <memory>

namespace gx
{
    // Base class for binary crossover algorithm
    template <typename T, typename V>
    struct binary_crossover
    {
        explicit binary_crossover(float probability) noexcept;
        virtual ~binary_crossover() = default;

        // Cross two genes and produce one children.
        virtual void produce_one_children(T* first, T* second, size_t size, T* result) const = 0;
        // Cross two genes and produce two children.
        virtual void produce_two_children(T* first, T* second, size_t size, T* result_first, T* result_second) const = 0;

        // Cross batch of two genes and produce batch of one children.
        virtual void produce_one_children_batch(T* first, T* second, size_t batch_size, size_t size, T* result) const = 0;
        // Cross batch of two genes and produce batch of two children.
        virtual void produce_two_children_batch(T* first, T* second, size_t batch_size, size_t size, T* result_first, T* result_second) const = 0;

        // Probability of drawing this crossover in genetic algorithm execution (has effect only if there are provided more then one crossover).
        float probability = 0.f;
    };

    template <typename T, typename V>
    binary_crossover<T, V>::binary_crossover(float probability) noexcept : probability(probability)
    {
    }

    template <typename T, typename V>
    using binary_crossover_ptr = std::unique_ptr<binary_crossover<T, V>>;
}


#endif //GX_BINARY_CROSSOVER_H
