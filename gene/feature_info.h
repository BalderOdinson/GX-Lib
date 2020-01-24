//
// Created by Oshikuru on 12.9.2019..
//

#ifndef GX_FEATURE_INFO_H
#define GX_FEATURE_INFO_H

#include "data_type.h"

namespace gx
{
    // Used for building features
    struct feature_info
    {
        // Feature type (used for binary gene).
        data_type type;
        // Represents distance between 2 nearest floating point numbers (used for binary gene).
        float precision_f;
        // Minimal value for floating point type.
        float min_f;
        // Maximal value for floating point type.
        float max_f;
        // Minimal value for integer type.
        int min_i;
        // Maximal value for integer type.
        int max_i;
    };
}

#endif //GX_FEATURE_INFO_H
