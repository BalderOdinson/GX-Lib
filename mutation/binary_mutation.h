//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_BINARY_MUTATION_H
#define GX_BINARY_MUTATION_H

#include <memory>

namespace gx
{
    // Base class for binary mutation algorithm
    template <typename T, typename V>
    struct binary_mutation
    {
        explicit binary_mutation(float probability) noexcept;
        virtual ~binary_mutation() = default;

        // Mutates given gene.
        virtual void mutate(T* value, size_t size, T* result) = 0;
        // Mutates given batch of genes.
        virtual void batch_mutate(T* batch, size_t batch_size, size_t size, T* result) = 0;

        // Probability of drawing this mutation in genetic algorithm execution (has effect only if there are provided more then one mutation).
        float probability = 0.f;
    };

    template <typename T, typename V>
    binary_mutation<T, V>::binary_mutation(float probability) noexcept : probability(probability)
    {
    }

    template <typename T, typename V>
    using binary_mutation_ptr = std::unique_ptr<binary_mutation<T, V>>;
}


#endif //GX_BINARY_MUTATION_H
