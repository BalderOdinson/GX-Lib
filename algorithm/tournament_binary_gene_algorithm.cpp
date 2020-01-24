//
// Created by Oshikuru on 15.9.2019..
//

#include "tournament_binary_gene_algorithm.h"

// Register types
namespace gx
{
    template<> bool tournament_binary_gene_algorithm<uint8_t, Vec32uc>::hreg = register_type();
    template<> bool tournament_binary_gene_algorithm<uint16_t, Vec16us>::hreg = register_type();
    template<> bool tournament_binary_gene_algorithm<uint32_t, Vec8ui>::hreg = register_type();
    template<> bool tournament_binary_gene_algorithm<uint64_t, Vec4uq>::hreg = register_type();
}