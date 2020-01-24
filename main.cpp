//
// Created by Oshikuru on 11.9.2019..
//

#include <iostream>
#include "vectorclass/vectorclass.h"
#include "vectorclass/ranvec1.h"
#include "crossover/binary_one_point_crossover.h"
#include "crossover/binary_n_point_crossover_args.h"
#include "mutation/binary_mutation_factory.h"
#include "mutation/binary_simple_mutation_args.h"
#include "decoder/fitness_evaluator_delegate.h"
#include "decoder/default_decoder.h"

float eval(gx::feature* features, size_t size)
{
    return 1.f;
}

void eval_batch(gx::feature* features, size_t size, size_t batch_size, float* result)
{
    return;
}

int main()
{
    gx::app::init();

    gx::binary_n_point_crossover_args args{5};

    auto crossover = gx::binary_crossover_factory<uint16_t, Vec16us>::instance().create(
            gx::crossover_type::binary_uniform_crossover,
            gx::crossover_info{1.f, gx::crossover_type::binary_uniform_crossover, &args});

    uint16_t first[1]{0};
    uint16_t second[1]{uint16_t(-1)};
    uint16_t result[1];

    crossover->produce_one_children(first, second, 1, result);

    gx::binary_simple_mutation_args m_args{0.2f};

    auto mutation = gx::binary_mutation_factory<uint16_t, Vec16us>::instance().create(
            gx::mutation_type::binary_simple,
            gx::mutation_info{1.0f,gx::mutation_type::binary_simple, &m_args});

    mutation->mutate(result, 1, result);

    std::cout << result[0] << std::endl;

    std::vector<gx::feature_info> features
    {
        gx::feature_info
                {
                        .type = gx::data_type::floating_point,
                        .precision_f = 1e-4,
                        .min_f = -1.f,
                        .max_f = 1.f
                },
        gx::feature_info
                {
                        .type = gx::data_type::floating_point,
                        .precision_f = 1e-4,
                        .min_f = -1.f,
                        .max_f = 1.f
                },
        gx::feature_info
                {
                        .type = gx::data_type::floating_point,
                        .precision_f = 1e-4,
                        .min_f = -1.f,
                        .max_f = 1.f
                }
    };

    gx::default_decoder_args d_args {};
    d_args.fitness_evaluator = &eval;
    d_args.batch_fitness_evaluator = &eval_batch;

    gx::decoder_info info {};
    info.type = gx::decoder_type::default_decoder;
    info.gene.type = gx::gene_type::binary;
    info.gene.features_size = features.size();
    info.gene.features = features.data();
    info.args = &d_args;

    try
    {
        auto decoder = gx::decoder_factory<uint16_t, Vec16us>::instance().create(gx::decoder_type::default_decoder, info);
    }
    catch(std::exception const& exc)
    {

    }
    catch (...)
    {

    }
}