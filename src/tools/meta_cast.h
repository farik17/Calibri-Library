#ifndef META_CAST_H
#define META_CAST_H

//! Std Includes
#include <string>
#include <cstring>
#include <iostream>
#include <limits>

//! CalibriLibrary Includes
#include "global/global.h"

namespace Calibri
{

//! Convert convertible types
template<typename CastType, typename DataType, typename std::enable_if<std::is_convertible<DataType, CastType>::value, class Enabler>::type... Enabler>
inline auto meta_cast(DataType data) noexcept -> CastType
{
    return static_cast<CastType>(data);
}

//! Convert cstring to arithmetic types
template<typename CastType, int Base = 10, typename std::enable_if<std::is_same<CastType, long>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto result = std::strtol(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<char>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<char>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, int Base = 10, typename std::enable_if<std::is_same<CastType, ulong>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto result = std::strtoul(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<char>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<char>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, int Base = 10, typename std::enable_if<(std::is_same<CastType, int8>::value
                                                                   || std::is_same<CastType, int16>::value
                                                                   || std::is_same<CastType, int32>::value), class Enabler>::type... Enabler>
inline auto meta_cast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto result = std::strtol(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (result > std::numeric_limits<CastType>::max() || result < std::numeric_limits<CastType>::min() || !(*ok = meta_cast<size_t>(end - data) == std::char_traits<char>::length(data)))
                result = 0;
        } else {
            if (result > std::numeric_limits<CastType>::max() || result < std::numeric_limits<CastType>::min() || meta_cast<size_t>(end - data) != std::char_traits<char>::length(data))
                result = 0;
        }

        break;
    }

    return meta_cast<CastType>(result);
}

template<typename CastType, int Base = 10, typename std::enable_if<(std::is_same<CastType, uint8>::value
                                                                   || std::is_same<CastType, uint16>::value
                                                                   || std::is_same<CastType, uint32>::value), class Enabler>::type... Enabler>
inline auto meta_cast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto result = std::strtoul(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (result > std::numeric_limits<CastType>::max() || !(*ok = meta_cast<size_t>(end - data) == std::char_traits<char>::length(data)))
                result = 0;
        } else {
            if (result > std::numeric_limits<CastType>::max() || meta_cast<size_t>(end - data) != std::char_traits<char>::length(data))
                result = 0;
        }

        break;
    }

    return meta_cast<CastType>(result);
}

template<typename CastType, int Base = 10, typename std::enable_if<std::is_same<CastType, int64>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto result = std::strtoll(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<char>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<char>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, int Base = 10, typename std::enable_if<std::is_same<CastType, uint64>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto result = std::strtoull(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<char>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<char>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, typename std::enable_if<std::is_same<CastType, float>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto result = std::strtof(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<char>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<char>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, typename std::enable_if<std::is_same<CastType, double>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto result = std::strtod(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<char>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<char>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, typename std::enable_if<std::is_same<CastType, longdouble>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto result = std::strtold(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<char>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<char>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

//! Convert string to arithmetic types
template<typename CastType, int Base = 10, typename std::enable_if<std::is_integral<CastType>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const std::string &data, bool *ok = nullptr) noexcept -> CastType
{
    return meta_cast<CastType, Base>(data.c_str(), ok);
}

template<typename CastType, typename std::enable_if<std::is_floating_point<CastType>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const std::string &data, bool *ok = nullptr) noexcept -> CastType
{
    return meta_cast<CastType>(data.c_str(), ok);
}

//! Convert wcstring to arithmetic types
template<typename CastType, int Base = 10, typename std::enable_if<std::is_same<CastType, long>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto result = std::wcstol(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, int Base = 10, typename std::enable_if<std::is_same<CastType, ulong>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto result = std::wcstoul(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, int Base = 10, typename std::enable_if<(std::is_same<CastType, int8>::value
                                                                   || std::is_same<CastType, int16>::value
                                                                   || std::is_same<CastType, int32>::value), class Enabler>::type... Enabler>
inline auto meta_cast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto result = std::wcstol(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (result > std::numeric_limits<CastType>::max() || result < std::numeric_limits<CastType>::min() || !(*ok = meta_cast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                result = 0;
        } else {
            if (result > std::numeric_limits<CastType>::max() || result < std::numeric_limits<CastType>::min() || meta_cast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                result = 0;
        }

        break;
    }

    return meta_cast<CastType>(result);
}

template<typename CastType, int Base = 10, typename std::enable_if<(std::is_same<CastType, uint8>::value
                                                                   || std::is_same<CastType, uint16>::value
                                                                   || std::is_same<CastType, uint32>::value), class Enabler>::type... Enabler>
inline auto meta_cast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto result = std::wcstoul(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (result > std::numeric_limits<CastType>::max() || !(*ok = meta_cast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                result = 0;
        } else {
            if (result > std::numeric_limits<CastType>::max() || meta_cast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                result = 0;
        }

        break;
    }

    return meta_cast<CastType>(result);
}

template<typename CastType, int Base = 10, typename std::enable_if<std::is_same<CastType, int64>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto result = std::wcstoll(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, int Base = 10, typename std::enable_if<std::is_same<CastType, uint64>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto result = std::wcstoull(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, typename std::enable_if<std::is_same<CastType, float>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto result = std::wcstof(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, typename std::enable_if<std::is_same<CastType, double>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto result = std::wcstod(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

template<typename CastType, typename std::enable_if<std::is_same<CastType, longdouble>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto result = std::wcstold(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << FUNC_INFO << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        result = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = meta_cast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                result = 0;
        } else {
            if (meta_cast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                result = 0;
        }

        break;
    }

    return result;
}

//! Convert wstring to arithmetic types
template<typename CastType, int Base = 10, typename std::enable_if<std::is_integral<CastType>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const std::wstring &data, bool *ok = nullptr) noexcept -> CastType
{
    return meta_cast<CastType, Base>(data.c_str(), ok);
}

template<typename CastType, typename std::enable_if<std::is_floating_point<CastType>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const std::wstring &data, bool *ok = nullptr) noexcept -> CastType
{
    return meta_cast<CastType>(data.c_str(), ok);
}

//! Convert arithmetic types to string
template<typename CastType, typename DataType, typename std::enable_if<(std::is_same<CastType, std::string>::value
                                                                       && std::is_arithmetic<DataType>::value), class Enabler>::type... Enabler>
inline auto meta_cast(DataType data) noexcept -> CastType
{
    try {
        return std::to_string(data);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        return {};
    }
}

//! Convert arithmetic types to wstring
template<typename CastType, typename DataType, typename std::enable_if<(std::is_same<CastType, std::wstring>::value
                                                                       && std::is_arithmetic<DataType>::value), class Enabler>::type... Enabler>
inline auto meta_cast(DataType data) noexcept -> CastType
{
    try {
        return std::to_wstring(data);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        return {};
    }
}

//! Convert cstring to wstring
template<typename CastType, typename std::enable_if<std::is_same<CastType, std::wstring>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const char *data) noexcept -> CastType
{
    std::wstring result {};

    try {
        result.resize(std::mbstowcs(nullptr, data, 0));
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        return {};
    }

    if (std::mbstowcs(&result.front(), data, result.size()) == meta_cast<size_t>(-1))
        return {};

    return result;
}

//! Convert wcstring to string
template<typename CastType, typename std::enable_if<std::is_same<CastType, std::string>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const wchar_t *data) noexcept -> CastType
{
    std::string result {};

    try {
        result.resize(std::wcstombs(nullptr, data, 0));
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        return {};
    }

    if (std::wcstombs(&result.front(), data, result.size()) == meta_cast<size_t>(-1))
        return {};

    return result;
}

//! Convert string to wstring
template<typename CastType, typename std::enable_if<std::is_same<CastType, std::wstring>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const std::string &data) noexcept -> CastType
{
    return meta_cast<CastType>(data.c_str());
}

//! Convert wstring to string
template<typename CastType, typename std::enable_if<std::is_same<CastType, std::string>::value, class Enabler>::type... Enabler>
inline auto meta_cast(const std::wstring &data) noexcept -> CastType
{
    return meta_cast<CastType>(data.c_str());
}

} // namespace Calibri

#endif // META_CAST_H