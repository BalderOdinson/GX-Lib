//
// Created by Oshikuru on 11.9.2019..
//

#include <cmath>
#include "feature_decoder.h"

gx::feature_decoder::feature_decoder(float precision, float min, float max, uint16_t offset) :
        minf_(min), maxf_(max), precision_(precision), offset_(offset), type_(data_type::floating_point)
{
    bit_length_ = static_cast<uint8_t>(ceilf(log2f((max - min) / precision + 1)));
    precalculated_shiftf_ = (maxf_ - minf_) / (static_cast<float>(1u << bit_length_) - 1.f);
}

gx::feature_decoder::feature_decoder(int32_t min, int32_t max, uint16_t offset) :
        mini_(min), maxi_(max), offset_(offset), type_(data_type::integer)
{
    bit_length_ = static_cast<uint8_t>(31 - __builtin_clz(max - min) + 1ul);
    precalculated_shifti_ = ((1u << (bit_length_ + 1)) - 1) - max;
}

uint8_t gx::feature_decoder::bit_length() const noexcept
{
    return bit_length_;
}

gx::data_type gx::feature_decoder::type() const noexcept
{
    return type_;
}

gx::feature_decoder gx::feature_decoder::create_integer(int32_t min, int32_t max, uint16_t offset) noexcept
{
    return gx::feature_decoder(min, max, offset);
}

gx::feature_decoder gx::feature_decoder::create_floating_point(float precision, float min, float max, uint16_t offset) noexcept
{
    return gx::feature_decoder(precision, min, max, offset);
}

size_t gx::feature_decoder::calculate_feature_size(const gx::feature_info& info) noexcept
{
    if(info.type == data_type::floating_point)
        return static_cast<size_t>(ceilf(log2f((info.max_f - info.min_f) / info.precision_f + 1)));
    else
        return static_cast<uint8_t>(31 - __builtin_clz(info.max_i - info.min_i) + 1ul);
}
