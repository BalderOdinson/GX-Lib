cmake_minimum_required(VERSION 3.14)
project(gx)

set(CMAKE_CXX_STANDARD 17)

file(GLOB VECTORCLASS_LIB
        "vectorclass/*.h"
        "vectorclass/*.cpp")

set(GXINCLUDE_LIB library/gene.cpp library/gene.h gene/feature_decoder.cpp gene/feature_decoder.h gene/gene_info.cpp gene/gene_info.h core/gx_exception.cpp core/gx_exception.h core/base_factory.h gene/feature.cpp gene/feature.h core/permutation_iterator.h crossover/binary_crossover.cpp crossover/binary_crossover.h crossover/binary_crossover_factory.cpp crossover/binary_crossover_factory.h crossover/crossover_info.cpp crossover/crossover_info.h gene/data_type.h gene/feature_info.cpp gene/feature_info.h crossover/binary_n_point_crossover_args.cpp crossover/binary_n_point_crossover_args.h library/error_handler.h library/core.h crossover/binary_one_point_crossover.cpp crossover/binary_one_point_crossover.h core/app.cpp core/app.h crossover/binary_n_point_crossover.cpp crossover/binary_n_point_crossover.h crossover/binary_uniform_crossover.cpp crossover/binary_uniform_crossover.h mutation/mutation_info.cpp mutation/mutation_info.h mutation/binary_mutation.cpp mutation/binary_mutation.h mutation/binary_mutation_factory.cpp mutation/binary_mutation_factory.h mutation/binary_simple_mutation.cpp mutation/binary_simple_mutation.h mutation/binary_simple_mutation_args.cpp mutation/binary_simple_mutation_args.h mutation/binary_rotate_mix_mutation.cpp mutation/binary_rotate_mix_mutation.h algorithm/binary_gene_algorithm.cpp algorithm/binary_gene_algorithm.h algorithm/binary_gene_algorithm_factory.cpp algorithm/binary_gene_algorithm_factory.h algorithm/algorithm_type.h algorithm/algorithm_args.cpp algorithm/algorithm_args.h decoder/fitness_evaluator_delegate.cpp decoder/fitness_evaluator_delegate.h decoder/decoder.cpp decoder/decoder.h decoder/default_decoder.cpp decoder/default_decoder.h decoder/decoder_type.h decoder/decoder_factory.cpp decoder/decoder_factory.h decoder/decoder_info.cpp decoder/decoder_info.h decoder/default_decoder_args.cpp decoder/default_decoder_args.h decoder/floating_point_decoder.cpp decoder/floating_point_decoder.h decoder/floating_point_decoder_args.cpp decoder/floating_point_decoder_args.h decoder/integer_decoder.cpp decoder/integer_decoder.h decoder/integer_decoder_args.cpp decoder/integer_decoder_args.h algorithm/tournament_binary_gene_algorithm.cpp algorithm/tournament_binary_gene_algorithm.h library/gx.cpp library/gx.h)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_executable(gx main.cpp ${GXINCLUDE_LIB} ${VECTORCLASS_LIB})
else()
    add_compile_definitions(GXLIB)
    add_library(gx SHARED ${GXINCLUDE_LIB} ${VECTORCLASS_LIB})
endif()
