#ifndef COMPILERDETECTION_H
#define COMPILERDETECTION_H

//! Defines
/*!
 *  The compiler, must be one of: (CC_x)
 *
 *   GNU        - GNU C++
 *   CLANG      - C++ front-end for the LLVM compiler
 */
#if defined(__GNUC__)
#   define CC_GNU

#   if defined(__MINGW32__)
#       define CC_MINGW
#   elif defined(__clang__)
#       define CC_CLANG
#   endif

#   define FUNC_INFO __PRETTY_FUNCTION__
#   define LIKELY(expr) __builtin_expect(!!(expr), true)
#   define UNLIKELY(expr) __builtin_expect(!!(expr), false)
#else
#   error "Calibri does not support current compiler"
#endif

#endif // COMPILERDETECTION_H
