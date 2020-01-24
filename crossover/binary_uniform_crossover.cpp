//
// Created by Oshikuru on 14.9.2019..
//

#include "binary_uniform_crossover.h"

//Register types
namespace gx
{
    template<> bool binary_uniform_crossover<uint8_t, Vec32uc>::hreg = register_type();
    template<> bool binary_uniform_crossover<uint16_t, Vec16us>::hreg = register_type();
    template<> bool binary_uniform_crossover<uint32_t, Vec8ui>::hreg = register_type();
    template<> bool binary_uniform_crossover<uint64_t, Vec4uq>::hreg = register_type();
}