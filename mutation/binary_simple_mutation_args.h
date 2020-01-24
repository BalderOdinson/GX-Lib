//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_BINARY_SIMPLE_MUTATION_ARGS_H
#define GX_BINARY_SIMPLE_MUTATION_ARGS_H

namespace gx
{
    // Args for binary simple mutation info
    struct binary_simple_mutation_args
    {
        // Probability of mutating one bit (It will be rounded closest to power of 0.5).
        float probability;
    };
}


#endif //GX_BINARY_SIMPLE_MUTATION_ARGS_H
