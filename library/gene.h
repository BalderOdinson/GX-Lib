//
// Created by Oshikuru on 11.9.2019..
//
#ifndef GX_GENE_H
#define GX_GENE_H

#include <cstdint>
#include "../crossover/crossover_info.h"
#include "core.h"
#include "../decoder/fitness_evaluator_delegate.h"

//extern "C" GXLIB_API int create_floating_point_feature(float precision, float min, float max, void **result);
//extern "C" GXLIB_API int get_feature_type(void *feature, int *type);
//extern "C" GXLIB_API int destroy_feature(void *feature);
extern "C" GXLIB_API float test_crossover_args(gx::crossover_info info);
extern "C" GXLIB_API float test_callback(float_fitness_evaluator_delegate delegate);
extern "C" GXLIB_API float test_callback_2(fitness_evaluator_delegate delegate);

#endif //GX_GENE_H
