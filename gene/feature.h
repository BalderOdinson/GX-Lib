//
// Created by Oshikuru on 12.9.2019..
//

#ifndef GX_FEATURE_H
#define GX_FEATURE_H

#include "data_type.h"

namespace gx
{
    // Contains feature value and type for binary algorithm.
    struct feature
    {
        // Type of feature.
        data_type type;
        // Value for feature of type integer.
        int int_value;
        // Value for feature of type floating point.
        float fp_value;
    };
}


#endif //GX_FEATURE_H
