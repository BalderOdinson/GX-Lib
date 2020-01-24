//
// Created by Oshikuru on 15.9.2019..
//

#ifndef GX_DECODER_H
#define GX_DECODER_H

#include <memory>
#include "../gene/feature.h"

namespace gx
{
    // Used for decoding genes and calculating fitness function.
    template <typename T, typename V>
    struct decoder
    {
        virtual ~decoder() = default;

        // Calculate fitness value from gene.
        virtual float fitness_value(T* gene, feature* decoded_features) const = 0;
        // Batch calculate fitness value from genes.
        virtual void batch_fitness_value(T* gene, size_t batch_size, float* result, feature* decoded_features) const = 0;

        // Decode binary gene.
        virtual void decode(T* gene,  feature* result) const = 0;

        // Gets size of gene in bits.
        [[nodiscard]] virtual size_t total_bit_count() const noexcept = 0;
        //Gets number of features.
        [[nodiscard]] virtual size_t feature_count() const noexcept = 0;
    };

    template <typename T, typename V>
    using decoder_ptr = std::unique_ptr<decoder<T, V>>;
}


#endif //GX_DECODER_H
