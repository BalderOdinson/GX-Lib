//
// Created by Oshikuru on 11.9.2019..
//

#ifndef GX_FEATURE_DECODER_H
#define GX_FEATURE_DECODER_H


#include <cstdint>
#include <limits>
#include "data_type.h"
#include "feature_info.h"

namespace gx
{
    // Used for decoding single binary feature.
    struct feature_decoder
    {
        // Creates decoder for decoding integer feature.
        static feature_decoder create_integer(int32_t min, int32_t max, uint16_t offset) noexcept;
        // Creates decoder for decoding floating point feature.
        static feature_decoder create_floating_point(float precision, float min, float max, uint16_t offset) noexcept;

        static size_t calculate_feature_size(const feature_info& info) noexcept ;

        // Gets amount of bits required to store feature in binary format
        [[nodiscard]] uint8_t bit_length() const noexcept;
        // Gets data type of feature
        [[nodiscard]] data_type type() const noexcept;

        // Decodes floating point feature
        template<typename Bits>
        [[nodiscard]] float decodef(Bits* bits) const;

        // Decodes integer feature
        template<typename Bits>
        [[nodiscard]] int32_t decodei(Bits* bits) const;

    private:
        feature_decoder(float precision, float min, float max, uint16_t offset);
        feature_decoder(int32_t min, int32_t max, uint16_t offset);

    private:
        float minf_{ std::numeric_limits<float>::quiet_NaN() };
        float maxf_{ std::numeric_limits<float>::quiet_NaN() };
        float precision_{ std::numeric_limits<float>::quiet_NaN() };
        float precalculated_shiftf_{ std::numeric_limits<float>::quiet_NaN() };
        int32_t mini_{ -1 };
        int32_t maxi_{ -1 };
        int32_t precalculated_shifti_{ -1 };
        uint8_t bit_length_;
        uint16_t offset_;
        data_type type_;
    };

    template <typename Bits>
    float feature_decoder::decodef(Bits* bits) const
    {
        constexpr uint16_t data_size = (sizeof(Bits) * 8);

        const uint16_t start_index = offset_ / data_size;
        const uint16_t end_index = (offset_ + bit_length_ - 1) / data_size;

        const uint16_t start_bit_index = offset_ - start_index * data_size;

        // Extract bits we need to convert
        auto req_bits = ((bits[start_index] << start_bit_index) >> (data_size - bit_length_));
        if(start_index != end_index)
        {
            const uint16_t bits_left = bit_length_ - (data_size - start_bit_index);
            req_bits |= (bits[end_index] >> (data_size - bits_left));
        }

        // Return decoded value
        return req_bits * precalculated_shiftf_ + minf_;
    }

    template <typename Bits>
    int32_t feature_decoder::decodei(Bits* bits) const
    {
        constexpr uint16_t data_size = (sizeof(Bits) * 8);

        const uint16_t start_index = offset_ / data_size;
        const uint16_t end_index = (offset_ + bit_length_ - 1) / data_size;

        const uint16_t start_bit_index = offset_ - start_index * data_size;

        // Extract bits we need to convert
        auto req_bits = ((bits[start_index] << start_bit_index) >> (data_size - bit_length_));
        if (start_index != end_index)
        {
            const uint16_t bits_left = bit_length_ - (data_size - start_bit_index);
            req_bits |= (bits[end_index] >> (data_size - bits_left));
        }

        // Return decoded value
        req_bits = req_bits > maxi_ - mini_ ? req_bits >> 1 : req_bits;
        return req_bits + mini_;
    }
}


#endif //GX_FEATURE_DECODER_H
