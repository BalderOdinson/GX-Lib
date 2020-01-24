//
// Created by Oshikuru on 15.9.2019..
//

#include "gx.h"
#include "../core/app.h"
#include "error_handler.h"
#include "../gene/feature_decoder.h"
#include "../algorithm/binary_gene_algorithm_factory.h"

int gx_init(int seed)
{
    HANDLE_API_CALL_BEGIN
        gx::app::init(seed);
    HANDLE_API_CALL_END
}

int gx_bga_create(gx::algorithm_type type, gx::decoder_info decoder_info, gx::crossover_info *crossover_info,
                  size_t crossover_info_size,
                  gx::mutation_info *mutation_info, size_t mutation_info_size, void* args, void **algorithm)
{
    HANDLE_API_CALL_BEGIN
        size_t total_bits = 0;
        for (size_t i = 0; i < decoder_info.gene.features_size; ++i)
            total_bits += gx::feature_decoder::calculate_feature_size(decoder_info.gene.features[i]);

        std::vector<gx::crossover_info> crossovers(crossover_info, crossover_info + crossover_info_size);
        std::vector<gx::mutation_info> mutations(mutation_info, mutation_info + mutation_info_size);

        if (total_bits <= sizeof(uint8_t) * 8)
            *algorithm = gx::binary_gene_algorithm_factory<uint8_t, Vec32uc>::instance().create(type, decoder_info,
                                                                                                crossovers, mutations, args);
        else if (total_bits <= sizeof(uint16_t) * 8)
            *algorithm = gx::binary_gene_algorithm_factory<uint16_t, Vec16us>::instance().create(type, decoder_info,
                                                                                                 crossovers, mutations, args);
        else if (total_bits <= sizeof(uint32_t) * 8)
            *algorithm = gx::binary_gene_algorithm_factory<uint32_t, Vec8ui>::instance().create(type, decoder_info,
                                                                                                crossovers, mutations, args);
        else if (total_bits <= sizeof(uint64_t) * 8)
            *algorithm = gx::binary_gene_algorithm_factory<uint64_t, Vec4uq>::instance().create(type, decoder_info,
                                                                                                crossovers, mutations, args);
        else
            *algorithm = gx::binary_gene_algorithm_factory<uint32_t, Vec8ui>::instance().create(type, decoder_info,
                                                                                                crossovers, mutations, args);
    HANDLE_API_CALL_END
}

int gx_bga_destroy(void *algorithm)
{
    HANDLE_API_CALL_BEGIN
        delete static_cast<gx::binary_gene_algorithm*>(algorithm);
    HANDLE_API_CALL_END
}

int gx_bga_init_population(void *algorithm, size_t population_size)
{
    HANDLE_API_CALL_BEGIN
        auto alg = static_cast<gx::binary_gene_algorithm*>(algorithm);
        if(!alg)
            throw gx::gx_exception(gx::gx_exception_code::null_reference, "Algorithm provided was null");
        alg->init_population(population_size);
    HANDLE_API_CALL_END
}

int gx_bga_run(void *algorithm, size_t epochs)
{
    HANDLE_API_CALL_BEGIN
        auto alg = static_cast<gx::binary_gene_algorithm*>(algorithm);
        if(!alg)
            throw gx::gx_exception(gx::gx_exception_code::null_reference, "Algorithm provided was null");
        alg->run(epochs);
    HANDLE_API_CALL_END
}

int gx_bga_get_best(void *algorithm, size_t* features_size, gx::feature *best)
{
    HANDLE_API_CALL_BEGIN
        auto alg = static_cast<gx::binary_gene_algorithm*>(algorithm);
        if(!alg)
            throw gx::gx_exception(gx::gx_exception_code::null_reference, "Algorithm provided was null");
        const auto b = alg->best();
        *features_size = b.size();
        memcpy(best, b.data(), sizeof(gx::feature) * b.size());
    HANDLE_API_CALL_END
}

int gx_bga_get_best_fitness(void *algorithm, float *best)
{
    HANDLE_API_CALL_BEGIN
        auto alg = static_cast<gx::binary_gene_algorithm*>(algorithm);
        if(!alg)
            throw gx::gx_exception(gx::gx_exception_code::null_reference, "Algorithm provided was null");
        *best = alg->best_fitness();
    HANDLE_API_CALL_END
}

int gx_bga_get_epoch(void *algorithm, size_t *epoch)
{
    HANDLE_API_CALL_BEGIN
        auto alg = static_cast<gx::binary_gene_algorithm*>(algorithm);
        if(!alg)
            throw gx::gx_exception(gx::gx_exception_code::null_reference, "Algorithm provided was null");
        *epoch = alg->epoch();
    HANDLE_API_CALL_END
}

int gx_bga_extract_plot_data(void *algorithm, size_t* data_size, float *data)
{
    HANDLE_API_CALL_BEGIN
        auto alg = static_cast<gx::binary_gene_algorithm*>(algorithm);
        if(!alg)
            throw gx::gx_exception(gx::gx_exception_code::null_reference, "Algorithm provided was null");
        const auto d = alg->extract_plot_data();
        *data_size = d.size();
        memcpy(data, d.data(), sizeof(float) * d.size());
    HANDLE_API_CALL_END
}
