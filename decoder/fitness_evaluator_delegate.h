//
// Created by Oshikuru on 15.9.2019..
//

#ifndef GX_FITNESS_EVALUATOR_DELEGATE_H
#define GX_FITNESS_EVALUATOR_DELEGATE_H

#include <cstdio>
#include "../gene/feature.h"

// Callbacks for evaluating fitness functions.
extern "C"
{
    typedef float (*fitness_evaluator_delegate)(gx::feature* features, size_t features_size);
    typedef float (*int_fitness_evaluator_delegate)(int* features, size_t features_size);
    typedef float (*float_fitness_evaluator_delegate)(float* features, size_t features_size);
    typedef void (*batch_fitness_evaluator_delegate)(gx::feature* features, size_t features_size, size_t batch_size, float* result);
    typedef void (*int_batch_fitness_evaluator_delegate)(int* features, size_t features_size, size_t batch_size, float* result);
    typedef void (*float_batch_fitness_evaluator_delegate)(float* features, size_t features_size, size_t batch_size, float* result);
};


#endif //GX_FITNESS_EVALUATOR_DELEGATE_H
