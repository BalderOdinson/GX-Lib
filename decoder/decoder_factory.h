//
// Created by Oshikuru on 15.9.2019..
//

#ifndef GX_DECODER_FACTORY_H
#define GX_DECODER_FACTORY_H

#include "../core/base_factory.h"
#include "decoder_type.h"
#include "decoder.h"
#include "decoder_info.h"

namespace gx
{
    // Factory for creating decoder for binary genetic algorithm
    template<typename T, typename V>
    struct decoder_factory : base_factory<
            decoder_factory<T, V>,
            decoder_type,
            decoder_ptr<T, V>,
            const decoder_info &>
    {
    };
}


#endif //GX_DECODER_FACTORY_H
