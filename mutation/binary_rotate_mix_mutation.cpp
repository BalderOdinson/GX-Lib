//
// Created by Oshikuru on 14.9.2019..
//

#include "binary_rotate_mix_mutation.h"

//Register types
namespace gx
{
    template<> bool binary_rotate_mix_mutation<uint8_t, Vec32uc>::hreg = register_type();
    template<> bool binary_rotate_mix_mutation<uint16_t, Vec16us>::hreg = register_type();
    template<> bool binary_rotate_mix_mutation<uint32_t, Vec8ui>::hreg = register_type();
    template<> bool binary_rotate_mix_mutation<uint64_t, Vec4uq>::hreg = register_type();
}