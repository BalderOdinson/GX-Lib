//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_BINARY_GENE_ALGORITHM_FACTORY_H
#define GX_BINARY_GENE_ALGORITHM_FACTORY_H

#include "../core/base_factory.h"
#include "binary_gene_algorithm.h"
#include "algorithm_type.h"
#include "algorithm_args.h"
#include "../decoder/decoder_info.h"
#include "../crossover/crossover_info.h"
#include "../mutation/mutation_info.h"

namespace gx
{
    template<typename T, typename V>
    struct binary_gene_algorithm_factory : base_factory<
            binary_gene_algorithm_factory<T, V>,
            algorithm_type,
            binary_gene_algorithm *,
            const decoder_info &, const std::vector<crossover_info> &,
            const std::vector<mutation_info> &, void*>
    {
    };
}


#endif //GX_BINARY_GENE_ALGORITHM_FACTORY_H
