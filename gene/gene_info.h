//
// Created by Oshikuru on 11.9.2019..
//

#ifndef GX_GENE_INFO_H
#define GX_GENE_INFO_H

#include <cstdint>
#include <memory>
#include "feature_info.h"

namespace gx
{
    enum class gene_type
    {
        binary,
        real
    };

    // Used for extracting info about gene used in algorithm.
    struct gene_info
    {
        // Features to optimize with genetic algorithm.
        feature_info* features;
        // Amount of features.
        size_t features_size;
        // Type of gene.
        gene_type type;
    };
}


#endif //GX_GENE_INFO_H
