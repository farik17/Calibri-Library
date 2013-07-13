/****************************************************************************
**
** Copyright (c) 2013 Calibri-Software <calibrisoftware@gmail.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
**
****************************************************************************/

#ifndef CDEFINES_H
#define CDEFINES_H

//! Std Includes
#include <cstdlib>
#include <cstdint>

//! Typedefs
typedef char                            c_int8;
typedef short                           c_int16;
typedef int                             c_int32;
typedef long long                       c_int64;
typedef long                            c_long;
typedef intptr_t                        c_intptr;
typedef unsigned char                   c_uint8;
typedef unsigned short                  c_uint16;
typedef unsigned int                    c_uint32;
typedef unsigned long long              c_uint64;
typedef unsigned long                   c_ulong;
typedef uintptr_t                       c_uintptr;

#if defined(_WIN32)
typedef c_intptr                        c_fdptr;
#elif defined(__unix__) || defined(__linux__)
typedef c_int32                         c_fdptr;
#endif

//! Defines
#define C_UNUSED(expr)                  (void)expr
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 4 || (__GNUC_MINOR__ == 4 && (__GNUC_PATCHLEVEL__ == 0 || __GNUC_PATCHLEVEL__ > 0))))
#   if __GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && (__GNUC_PATCHLEVEL__ == 0 || __GNUC_PATCHLEVEL__ > 0))
#       define C_CONSTEXPR              constexpr
#   else
#       define C_CONSTEXPR
#   endif
#   define C_DEBUG(expr)                std::cout  << __FILE__ << '(' << __LINE__ << ')' << " " << __PRETTY_FUNCTION__ << " : " << expr << std::endl
#   define C_DISABLE_COPY(expr)         expr(const expr &other) = delete;\
    expr &operator =(const expr &other) = delete;
#else
#   define C_CONSTEXPR
#   define C_DEBUG(expr)                std::cout  << __FILE__ << '(' << __LINE__ << ')' << " " << __FUNCTION__ << " : " << expr << std::endl
#   define C_DISABLE_COPY(expr)         expr(const expr &other) { C_UNUSED(other); }\
    expr &operator =(const expr &other) { C_UNUSED(other); return *this; }
#endif

#endif // CDEFINES_H
