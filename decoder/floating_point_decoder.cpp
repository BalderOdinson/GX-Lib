//
// Created by Oshikuru on 15.9.2019..
//

#include "floating_point_decoder.h"
#include "../vectorclass/vectorclass.h"

//Register types
namespace gx
{
    template<> bool floating_point_decoder<uint8_t, Vec32uc>::hreg = register_type();
    template<> bool floating_point_decoder<uint16_t, Vec16us>::hreg = register_type();
    template<> bool floating_point_decoder<uint32_t, Vec8ui>::hreg = register_type();
    template<> bool floating_point_decoder<uint64_t, Vec4uq>::hreg = register_type();
}