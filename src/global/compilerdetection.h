#ifndef COMPILERDETECTION_H
#define COMPILERDETECTION_H

//! Defines
/*!
 *  The compiler, must be one of: (CC_x)
 *
 *   MSVC       - Microsoft Visual C/C++
 *   GNU        - GNU C++
 */
#if defined(__GNUC__)
#   define CC_GNU
#elif defined(_MSC_VER)
#   define CC_MSVC
#else
#   error "Calibri does not support current compiler"
#endif

#if defined(CC_GNU)
#   define FUNC_INFO __PRETTY_FUNCTION__
#   define LIKELY(expr) __builtin_expect(!!(expr), true)
#   define UNLIKELY(expr) __builtin_expect(!!(expr), false)
#elif defined(CC_MSVC)
#   define FUNC_INFO __FUNCSIG__
#   define LIKELY(expr) (expr)
#   define UNLIKELY(expr) (expr)
#else
#   error "Calibri can not detect features supported by current compiler"
#endif

#endif // COMPILERDETECTION_H
