//
// Created by Oshikuru on 12.9.2019..
//

#ifndef GX_CROSSOVER_INFO_H
#define GX_CROSSOVER_INFO_H

namespace gx
{
    enum class crossover_type
    {
        binary_one_point_crossover,
        binary_n_point_crossover,
        binary_uniform_crossover,
        real_simple_arithmetic_recombination,
        real_discrete_recombination,
        real_whole_arithmetic_recombination,
        real_simulated_binary_recombination
    };

    // Used for building genetic crossover options
    struct crossover_info
    {
        // Probability of selecting this crossover (used only if there are produced more then one crossover).
        float probability;
        // Type of crossover algorithm
        crossover_type type;
        // Additional arguments needed for specific algorithm
        void* args;
    };
}


#endif //GX_CROSSOVER_INFO_H
