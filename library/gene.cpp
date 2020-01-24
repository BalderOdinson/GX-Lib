//
// Created by Oshikuru on 11.9.2019..
//

#include "gene.h"
#include "../gene/feature_info.h"
#include "error_handler.h"
#include "../crossover/binary_n_point_crossover_args.h"
#include <vector>
#include <numeric>

//int create_floating_point_feature(float precision, float min, float max, void **result)
//{
//    HANDLE_API_CALL_BEGIN
//        *result = new gx::floating_point_feature(precision, min, max);
//    HANDLE_API_CALL_END
//}
//
//int destroy_feature(void *feature)
//{
//    HANDLE_API_CALL_BEGIN
//        auto feature_cast = reinterpret_cast<gx::feature_info *>(feature);
//        delete feature_cast;
//    HANDLE_API_CALL_END
//}
//
//int get_feature_type(void *feature, int *type)
//{
//    HANDLE_API_CALL_BEGIN
//        if (!feature)
//            throw gx::gx_exception(gx::gx_exception_code::null_reference, "");
//        auto feature_cast = reinterpret_cast<gx::feature_info *>(feature);
//        *type = static_cast<int>(feature_cast->type());
//    HANDLE_API_CALL_END
//}

float test_crossover_args(gx::crossover_info info)
{
    return reinterpret_cast<gx::binary_n_point_crossover_args*>(info.args)->n * static_cast<int>(info.type) * info.probability;
}

float test_callback(float_fitness_evaluator_delegate delegate)
{
    std::vector<float> values(100, 5.f);
    auto result = delegate(values.data(), values.size());
    return std::accumulate(values.begin(), values.end(), result);
}

float test_callback_2(fitness_evaluator_delegate delegate)
{
    std::vector<gx::feature> values(100, gx::feature{ .type = gx::data_type::floating_point, .fp_value = 5.f });
    auto result = delegate(values.data(), values.size());
    return std::accumulate(values.begin(), values.end(), result, [](float sum, gx::feature& feature) { return sum + feature.fp_value; });
}
