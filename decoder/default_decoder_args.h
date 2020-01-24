//
// Created by Oshikuru on 15.9.2019..
//

#ifndef GX_DEFAULT_DECODER_ARGS_H
#define GX_DEFAULT_DECODER_ARGS_H

#include "fitness_evaluator_delegate.h"

namespace gx
{
    // Additional args for default decoder info.
    struct default_decoder_args
    {
        // Callback for calculating fitness.
        fitness_evaluator_delegate fitness_evaluator;
        // Callback for batch calculating fitness.
        batch_fitness_evaluator_delegate batch_fitness_evaluator;
    };
}


#endif //GX_DEFAULT_DECODER_ARGS_H
