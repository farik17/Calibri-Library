#ifndef META_CAST_H
#define META_CAST_H

//! Std Includes
#include <string>

//! Project Includes
#include "global.h"

namespace Calibri
{

//! Convert convertible types
template<typename CastType, typename DataType>
inline typename std::enable_if<std::is_convertible<DataType, CastType>::value, CastType>::type meta_cast(DataType data) DECL_NOEXCEPT
{
    return static_cast<CastType>(data);
}

//! Convert cstring to arithmetic types
template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, long>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return std::strtol(data, nullptr, 10);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, ulong>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return std::strtoul(data, nullptr, 10);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, int8>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::strtol(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, uint8>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::strtoul(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, int16>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::strtol(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, uint16>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::strtoul(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, int32>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::strtol(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, uint32>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::strtoul(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, int64>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return std::strtoll(data, nullptr, 10);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, uint64>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return std::strtoull(data, nullptr, 10);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, float>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return std::strtof(data, nullptr);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, double>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return std::strtod(data, nullptr);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, longdouble>::value, CastType>::type meta_cast(const char *data) DECL_NOEXCEPT
{
    return std::strtold(data, nullptr);
}

//! Convert string to arithmetic types
template<typename CastType>
inline typename std::enable_if<std::is_arithmetic<CastType>::value, CastType>::type meta_cast(const std::string &data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(data.c_str());
}

template<typename CastType>
inline typename std::enable_if<std::is_arithmetic<CastType>::value, CastType>::type meta_cast(std::string &&data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(data.c_str());
}

//! Convert wcstring to arithmetic types
template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, long>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return std::wcstol(data, nullptr, 10);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, ulong>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return std::wcstoul(data, nullptr, 10);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, int8>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::wcstol(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, uint8>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::wcstoul(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, int16>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::wcstol(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, uint16>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::wcstoul(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, int32>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::wcstol(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, uint32>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(std::wcstoul(data, nullptr, 10));
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, int64>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return std::wcstoll(data, nullptr, 10);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, uint64>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return std::wcstoull(data, nullptr, 10);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, float>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return std::wcstof(data, nullptr);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, double>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return std::wcstod(data, nullptr);
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, longdouble>::value, CastType>::type meta_cast(const wchar_t *data) DECL_NOEXCEPT
{
    return std::wcstold(data, nullptr);
}

//! Convert wstring to arithmetic types
template<typename CastType>
inline typename std::enable_if<std::is_arithmetic<CastType>::value, CastType>::type meta_cast(const std::wstring &data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(data.c_str());
}

template<typename CastType>
inline typename std::enable_if<std::is_arithmetic<CastType>::value, CastType>::type meta_cast(std::wstring &&data) DECL_NOEXCEPT
{
    return meta_cast<CastType>(data.c_str());
}

//! Convert arithmetic types to string
template<typename CastType, typename DataType>
inline typename std::enable_if<std::is_same<CastType, std::string>::value && std::is_arithmetic<DataType>::value, CastType>::type meta_cast(DataType data)
{
    try {
        return std::to_string(data);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        return std::string();
    }
}

//! Convert arithmetic types to wstring
template<typename CastType, typename DataType>
inline typename std::enable_if<std::is_same<CastType, std::wstring>::value && std::is_arithmetic<DataType>::value, CastType>::type meta_cast(DataType data)
{
    try {
        return std::to_wstring(data);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        return std::wstring();
    }
}

//! Convert cstring to wstring
template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, std::wstring>::value, CastType>::type meta_cast(const char *data)
{
    auto length = std::mbstowcs(nullptr, data, 0);

    if (length == meta_cast<size_t>(-1))
        return std::wstring();

    std::wstring result;

    try {
        result.resize(length);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        return std::wstring();
    }

    if (std::mbstowcs(&result.front(), data, length) == meta_cast<size_t>(-1))
        return std::wstring();

    return result;
}

//! Convert wcstring to string
template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, std::string>::value, CastType>::type meta_cast(const wchar_t *data)
{
    auto length = std::wcstombs(nullptr, data, 0);

    if (length == meta_cast<size_t>(-1))
        return std::string();

    std::string result;

    try {
        result.resize(length);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        return std::string();
    }

    if (std::wcstombs(&result.front(), data, length) == meta_cast<size_t>(-1))
        return std::string();

    return result;
}

//! Convert string to wstring
template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, std::wstring>::value, CastType>::type meta_cast(const std::string &data)
{
    return meta_cast<CastType>(data.c_str());
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, std::wstring>::value, CastType>::type meta_cast(std::string &&data)
{
    return meta_cast<CastType>(data.c_str());
}

//! Convert wstring to string
template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, std::string>::value, CastType>::type meta_cast(const std::wstring &data)
{
    return meta_cast<CastType>(data.c_str());
}

template<typename CastType>
inline typename std::enable_if<std::is_same<CastType, std::string>::value, CastType>::type meta_cast(std::wstring &&data)
{
    return meta_cast<CastType>(data.c_str());
}

}

#endif // META_CAST_H
