//
// Created by Oshikuru on 12.9.2019..
//

#ifndef GX_ERROR_HANDLER_H
#define GX_ERROR_HANDLER_H

#include "../core/gx_exception.h"

#define HANDLE_API_CALL_BEGIN                           \
try                                                     \
{

#define HANDLE_API_CALL_END                             \
    return int(gx::gx_exception_code::successful);      \
}                                                       \
catch(const gx::gx_exception& exc)                      \
{                                                       \
    return exc.get_code_as_int();                       \
}                                                       \
catch(...)                                              \
{                                                       \
    return int(gx::gx_exception_code::unknown_error);   \
}

#endif //GX_ERROR_HANDLER_H
