//
// Created by Oshikuru on 15.9.2019..
//

#ifndef GX_INTEGER_DECODER_ARGS_H
#define GX_INTEGER_DECODER_ARGS_H


#include "fitness_evaluator_delegate.h"

namespace gx
{
    // Additional args for integer decoder info.
    struct integer_decoder_args
    {
        // Callback for calculating fitness.
        int_fitness_evaluator_delegate fitness_evaluator;
        // Callback for batch calculating fitness.
        int_batch_fitness_evaluator_delegate batch_fitness_evaluator;
    };
}


#endif //GX_INTEGER_DECODER_ARGS_H
