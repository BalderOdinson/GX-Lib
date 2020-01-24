//
// Created by Oshikuru on 14.9.2019..
//

#include "binary_n_point_crossover.h"

//Register types
namespace gx
{
    template<> bool binary_n_point_crossover<uint8_t, Vec32uc>::hreg = register_type();
    template<> bool binary_n_point_crossover<uint16_t, Vec16us>::hreg = register_type();
    template<> bool binary_n_point_crossover<uint32_t, Vec8ui>::hreg = register_type();
    template<> bool binary_n_point_crossover<uint64_t, Vec4uq>::hreg = register_type();

    template<> Vec32uc binary_n_point_crossover<uint8_t, Vec32uc>::indices_ = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
    template<> Vec16us binary_n_point_crossover<uint16_t, Vec16us>::indices_ = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    template<> Vec8ui binary_n_point_crossover<uint32_t, Vec8ui>::indices_ = { 0, 1, 2, 3, 4, 5, 6, 7 };
    template<> Vec4uq binary_n_point_crossover<uint64_t, Vec4uq>::indices_ = { 0, 1, 2, 3 };
}