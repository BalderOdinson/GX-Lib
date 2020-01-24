//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_BINARY_GENE_ALGORITHM_H
#define GX_BINARY_GENE_ALGORITHM_H

#include <cstdint>
#include "../gene/feature.h"
#include <vector>

namespace gx
{
    // Base class for binary genetic algorithm.
    struct binary_gene_algorithm
    {
        virtual ~binary_gene_algorithm() = default;

        // Initialize population of given size to random values.
        virtual void init_population(size_t population_size) = 0;
        // Runs the algorithm.
        virtual void run(size_t epochs) = 0;
        // Gets the current best gene in population.
        [[nodiscard]] virtual const std::vector<feature>& best() const noexcept = 0;
        // Gets the current best fitness.
        [[nodiscard]] virtual float best_fitness() const noexcept = 0;
        [[nodiscard]] virtual size_t epoch() const noexcept = 0;
        // Extracts best fitness values collected through epochs from last function call.
        virtual std::vector<float> extract_plot_data() = 0;
    };
}


#endif //GX_BINARY_GENE_ALGORITHM_H
