//
// Created by Oshikuru on 14.9.2019..
//

#include "app.h"

namespace gx
{
    void app::init(int seed)
    {
        random_engine().init(seed);
    }

    Ranvec1& app::random_engine() noexcept
    {
        static Ranvec1 engine(1);
        return engine;
    }
}