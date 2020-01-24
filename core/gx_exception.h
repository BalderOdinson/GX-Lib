//
// Created by Oshikuru on 11.9.2019..
//

#ifndef GX_GX_EXCEPTION_H
#define GX_GX_EXCEPTION_H

#include <exception>

namespace gx
{
    enum class gx_exception_code
    {
        successful,
        unknown_error,
        not_implemented,
        invalid_argument,
        null_reference,
        invalid_operation
    };

    struct gx_exception : std::exception
    {
        gx_exception(gx_exception_code code, const char* message);

        [[nodiscard]] const char* what() const noexcept override;

        [[nodiscard]] virtual int get_code_as_int() const noexcept;

        [[nodiscard]] virtual gx_exception_code get_code() const noexcept;
    private:
        gx_exception_code code_;
        const char* msg_;
     };
}


#endif //GX_GX_E{}XCEPTION_H
