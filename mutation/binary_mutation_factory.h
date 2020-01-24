//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_BINARY_MUTATION_FACTORY_H
#define GX_BINARY_MUTATION_FACTORY_H

#include "../core/base_factory.h"
#include "mutation_info.h"
#include "binary_mutation.h"

namespace gx
{
    // Factory for creating binary mutation algorithms.
    template<typename T, typename V>
    struct binary_mutation_factory : base_factory<
            binary_mutation_factory<T, V>,
            mutation_type,
            binary_mutation_ptr<T, V>,
            const mutation_info &>
    {
    };
}


#endif //GX_BINARY_MUTATION_FACTORY_H
