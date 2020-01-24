//
// Created by Oshikuru on 12.9.2019..
//

#ifndef GX_BINARY_N_POINT_CROSSOVER_ARGS_H
#define GX_BINARY_N_POINT_CROSSOVER_ARGS_H

#include <cstdint>
#include "crossover_info.h"

namespace gx
{
    // Args for binary n point crossover info
    struct binary_n_point_crossover_args
    {
        // Maximum number of crossing points.
        uint32_t n;
    };
}


#endif //GX_BINARY_N_POINT_CROSSOVER_ARGS_H
