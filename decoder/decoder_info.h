//
// Created by Oshikuru on 15.9.2019..
//

#ifndef GX_DECODER_INFO_H
#define GX_DECODER_INFO_H

#include "decoder_type.h"
#include "../gene/gene_info.h"

namespace gx
{
    // Info for building decoder for binary genetic algorithm.
    struct decoder_info
    {
        // Type of decoder.
        decoder_type type;
        // Info about gene.
        gene_info gene;
        // Additional args for specific implementation.
        void* args;
    };
}


#endif //GX_DECODER_INFO_H
