//
// Created by Oshikuru on 14.9.2019..
//

#ifndef GX_APP_H
#define GX_APP_H

#include "../vectorclass/ranvec1.h"

namespace gx
{
    struct app
    {
        app() = default;
        static void init(int seed = 100);
        static Ranvec1& random_engine() noexcept;
    };
}


#endif //GX_APP_H
