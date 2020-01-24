//
// Created by Oshikuru on 11.9.2019..
//

#include "gx_exception.h"

gx::gx_exception::gx_exception(gx::gx_exception_code code, const char *message) : code_(code), msg_(message)
{

}

const char *gx::gx_exception::what() const noexcept
{
    return msg_;
}

int gx::gx_exception::get_code_as_int() const noexcept
{
    return static_cast<int>(code_);
}

gx::gx_exception_code gx::gx_exception::get_code() const noexcept
{
    return code_;
}
