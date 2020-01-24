//
// Created by Oshikuru on 12.9.2019..
//

#ifndef GX_CORE_H
#define GX_CORE_H

#ifdef GXLIB
#define GXLIB_API __declspec(dllexport)
#else
#define GXLIB_API //__declspec(dllimport)
#endif

#endif //GX_CORE_H
