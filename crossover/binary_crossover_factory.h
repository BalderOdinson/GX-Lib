//
// Created by Oshikuru on 12.9.2019..
//

#ifndef GX_BINARY_CROSSOVER_FACTORY_H
#define GX_BINARY_CROSSOVER_FACTORY_H

#include "../core/base_factory.h"
#include "crossover_info.h"
#include "binary_crossover.h"

namespace gx
{
    // Factory for creating binary crossover algorithms.
    template<typename T, typename V>
    struct binary_crossover_factory : base_factory<
            binary_crossover_factory<T, V>,
            crossover_type,
            binary_crossover_ptr<T, V>,
            const crossover_info&>
    {
    };
}


#endif //GX_BINARY_CROSSOVER_FACTORY_H
