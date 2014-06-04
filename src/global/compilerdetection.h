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
#   define CC_GNU_VERSION_VALUE(major, minor, patch) ((major * 10000) + (minor * 100) + patch)
#   define CC_GNU_VERSION CC_GNU_VERSION_VALUE(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#   define CC_GNU_VERSION_CHECK(major, minor, patch) (CC_GNU_VERSION >= CC_GNU_VERSION_VALUE(major, minor, patch))

#   if CC_GNU_VERSION_CHECK(4, 8, 0)
#       define COMPILER_CXX11_NORETURN
#   endif

#   if CC_GNU_VERSION_CHECK(4, 7, 0)
#       define COMPILER_CXX11_EXPLICIT_OVERRIDES
#   endif

#   if CC_GNU_VERSION_CHECK(4, 6, 0)
#       define COMPILER_CXX11_NOEXCEPT
#       define COMPILER_CXX11_CONSTEXPR
#   endif

#   if CC_GNU_VERSION_CHECK(4, 4, 0)
#       define COMPILER_CXX11_DEFAULT_MEMBERS
#       define COMPILER_CXX11_DELETE_MEMBERS
#   endif

#   define FUNC_INFO __PRETTY_FUNCTION__
#   define LIKELY(expr) __builtin_expect(!!(expr), true)
#   define UNLIKELY(expr) __builtin_expect(!!(expr), false)
#elif defined(CC_MSVC)
#   define CC_MSVC_VERSION _MSC_VER
#   define CC_MSVC_VERSION_CHECK(version) (CC_MSVC_VERSION >= version)

#   if CC_MSVC_VERSION_CHECK(1800)
#       define COMPILER_CXX11_CONSTEXPR
#       define COMPILER_CXX11_DEFAULT_MEMBERS
#       define COMPILER_CXX11_DELETE_MEMBERS
#   endif

#   if CC_MSVC_VERSION_CHECK(1700)
#       define COMPILER_CXX11_EXPLICIT_OVERRIDES
#   endif

#   define FUNC_INFO __FUNCSIG__
#   define LIKELY(expr) (expr)
#   define UNLIKELY(expr) (expr)
#else
#   error "Calibri can not detect features supported by current compiler"
#endif

#if defined(COMPILER_CXX11_NORETURN)
#   define DECL_NORETURN [[noreturn]]
#else
#   define DECL_NORETURN
#endif

#if defined(COMPILER_CXX11_NOEXCEPT)
#   define DECL_NOEXCEPT noexcept
#   define DECL_NOEXCEPT_EXPR(expr) noexcept(expr)
#else
#   define DECL_NOEXCEPT
#   define DECL_NOEXCEPT_EXPR(expr)
#endif

#if defined(COMPILER_CXX11_EXPLICIT_OVERRIDES)
#   define DECL_OVERRIDE override
#   define DECL_FINAL final
#else
#   define DECL_OVERRIDE
#   define DECL_FINAL
#endif

#if defined(COMPILER_CXX11_CONSTEXPR)
#   define DECL_CONSTEXPR constexpr
#   define CONSTEXPR constexpr
#else
#   define DECL_CONSTEXPR
#   define CONSTEXPR const
#endif

#if defined(COMPILER_CXX11_DEFAULT_MEMBERS)
#   define DECL_DEFAULT = default
#else
#   define DECL_DEFAULT
#endif

#if defined(COMPILER_CXX11_DELETE_MEMBERS)
#   define DECL_DELETE = delete
#else
#   define DECL_DELETE
#endif

#define UNUSED(expr) (void)expr;

#endif // COMPILERDETECTION_H
