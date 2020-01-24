//
// Created by Oshikuru on 15.9.2019..
//

#ifndef GX_FLOATING_POINT_DECODER_ARGS_H
#define GX_FLOATING_POINT_DECODER_ARGS_H


#include "fitness_evaluator_delegate.h"

namespace gx
{
    // Additional args for floating-point decoder info.
    struct floating_point_decoder_args
    {
        // Callback for calculating fitness.
        float_fitness_evaluator_delegate fitness_evaluator;
        // Callback for batch calculating fitness.
        float_batch_fitness_evaluator_delegate batch_fitness_evaluator;
    };
}


#endif //GX_FLOATING_POINT_DECODER_ARGS_H
