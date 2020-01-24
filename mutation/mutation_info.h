//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_MUTATION_INFO_H
#define GX_MUTATION_INFO_H

namespace gx
{
    enum class mutation_type
    {
        binary_simple,
        binary_rotate_mix,
        real_simple,
        real_normal_distribution_identity,
        real_normal_distribution_addition
    };

    // Used for building genetic mutation options
    struct mutation_info
    {
        // Probability of selecting this mutation (used only if there are produced more then one mutation).
        float probability;
        // Type of mutation algorithm
        mutation_type type;
        // Additional arguments needed for specific algorithm
        void* args;
    };
}


#endif //GX_MUTATION_INFO_H
