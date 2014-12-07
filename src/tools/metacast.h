#ifndef METACAST_H
#define METACAST_H

//! Std includes
#include <string>
#include <cstring>
#include <iostream>
#include <limits>

//! Calibri-Library includes
#include "global/global.h"

namespace Calibri {

//! Convert convertible types
template<typename CastType,
         typename DataType,
         typename std::enable_if<std::is_convertible<DataType, CastType>::value>::type... Enabler>
inline auto metaCast(DataType data) noexcept -> CastType
{
    return static_cast<CastType>(data);
}

//! Convert cstring to arithmetic types
template<typename CastType,
         int Base = 10,
         typename std::enable_if<std::is_same<CastType, long>::value>::type... Enabler>
inline auto metaCast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto castedData = std::strtol(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<char>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<char>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         int Base = 10,
         typename std::enable_if<std::is_same<CastType, ulong>::value>::type... Enabler>
inline auto metaCast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto castedData = std::strtoul(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<char>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<char>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         int Base = 10,
         typename std::enable_if<(std::is_same<CastType, int8>::value
                                 || std::is_same<CastType, int16>::value
                                 || std::is_same<CastType, int32>::value)>::type... Enabler>
inline auto metaCast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto castedData = std::strtol(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (castedData > std::numeric_limits<CastType>::max()
                    || castedData < std::numeric_limits<CastType>::min()
                    || !(*ok = metaCast<size_t>(end - data) == std::char_traits<char>::length(data)))
                castedData = 0;
        } else {
            if (castedData > std::numeric_limits<CastType>::max()
                    || castedData < std::numeric_limits<CastType>::min()
                    || metaCast<size_t>(end - data) != std::char_traits<char>::length(data))
                castedData = 0;
        }

        break;
    }

    return metaCast<CastType>(castedData);
}

template<typename CastType,
         int Base = 10,
         typename std::enable_if<(std::is_same<CastType, uint8>::value
                                 || std::is_same<CastType, uint16>::value
                                 || std::is_same<CastType, uint32>::value)>::type... Enabler>
inline auto metaCast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto castedData = std::strtoul(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (castedData > std::numeric_limits<CastType>::max()
                    || !(*ok = metaCast<size_t>(end - data) == std::char_traits<char>::length(data)))
                castedData = 0;
        } else {
            if (castedData > std::numeric_limits<CastType>::max()
                    || metaCast<size_t>(end - data) != std::char_traits<char>::length(data))
                castedData = 0;
        }

        break;
    }

    return metaCast<CastType>(castedData);
}

template<typename CastType,
         int Base = 10,
         typename std::enable_if<std::is_same<CastType, int64>::value>::type... Enabler>
inline auto metaCast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto castedData = std::strtoll(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<char>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<char>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         int Base = 10,
         typename std::enable_if<std::is_same<CastType, uint64>::value>::type... Enabler>
inline auto metaCast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto castedData = std::strtoull(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<char>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<char>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         typename std::enable_if<std::is_same<CastType, float>::value>::type... Enabler>
inline auto metaCast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto castedData = std::strtof(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<char>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<char>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         typename std::enable_if<std::is_same<CastType, double>::value>::type... Enabler>
inline auto metaCast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto castedData = std::strtod(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<char>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<char>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         typename std::enable_if<std::is_same<CastType, longdouble>::value>::type... Enabler>
inline auto metaCast(const char *data, bool *ok = nullptr) noexcept -> CastType
{
    char *end {};
    auto castedData = std::strtold(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<char>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<char>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

//! Convert string to arithmetic types
template<typename CastType,
         int Base = 10,
         typename std::enable_if<std::is_integral<CastType>::value>::type... Enabler>
inline auto metaCast(const std::string &data, bool *ok = nullptr) noexcept -> CastType
{
    return metaCast<CastType, Base>(data.data(), ok);
}

template<typename CastType,
         typename std::enable_if<std::is_floating_point<CastType>::value>::type... Enabler>
inline auto metaCast(const std::string &data, bool *ok = nullptr) noexcept -> CastType
{
    return metaCast<CastType>(data.data(), ok);
}

//! Convert wcstring to arithmetic types
template<typename CastType,
         int Base = 10,
         typename std::enable_if<std::is_same<CastType, long>::value>::type... Enabler>
inline auto metaCast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto castedData = std::wcstol(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         int Base = 10,
         typename std::enable_if<std::is_same<CastType, ulong>::value>::type... Enabler>
inline auto metaCast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto castedData = std::wcstoul(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         int Base = 10,
         typename std::enable_if<(std::is_same<CastType, int8>::value
                                 || std::is_same<CastType, int16>::value
                                 || std::is_same<CastType, int32>::value)>::type... Enabler>
inline auto metaCast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto castedData = std::wcstol(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (castedData > std::numeric_limits<CastType>::max()
                    || castedData < std::numeric_limits<CastType>::min()
                    || !(*ok = metaCast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                castedData = 0;
        } else {
            if (castedData > std::numeric_limits<CastType>::max()
                    || castedData < std::numeric_limits<CastType>::min()
                    || metaCast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                castedData = 0;
        }

        break;
    }

    return metaCast<CastType>(castedData);
}

template<typename CastType,
         int Base = 10,
         typename std::enable_if<(std::is_same<CastType, uint8>::value
                                 || std::is_same<CastType, uint16>::value
                                 || std::is_same<CastType, uint32>::value)>::type... Enabler>
inline auto metaCast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto castedData = std::wcstoul(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (castedData > std::numeric_limits<CastType>::max()
                    || !(*ok = metaCast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                castedData = 0;
        } else {
            if (castedData > std::numeric_limits<CastType>::max()
                    || metaCast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                castedData = 0;
        }

        break;
    }

    return metaCast<CastType>(castedData);
}

template<typename CastType,
         int Base = 10,
         typename std::enable_if<std::is_same<CastType, int64>::value>::type... Enabler>
inline auto metaCast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto castedData = std::wcstoll(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         int Base = 10,
         typename std::enable_if<std::is_same<CastType, uint64>::value>::type... Enabler>
inline auto metaCast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto castedData = std::wcstoull(data, &end, Base);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         typename std::enable_if<std::is_same<CastType, float>::value>::type... Enabler>
inline auto metaCast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto castedData = std::wcstof(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         typename std::enable_if<std::is_same<CastType, double>::value>::type... Enabler>
inline auto metaCast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto castedData = std::wcstod(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

template<typename CastType,
         typename std::enable_if<std::is_same<CastType, longdouble>::value>::type... Enabler>
inline auto metaCast(const wchar_t *data, bool *ok = nullptr) noexcept -> CastType
{
    wchar_t *end {};
    auto castedData = std::wcstold(data, &end);

    switch (errno) {
    case ERANGE:
        std::cerr << __func__ << " : " << std::strerror(errno) << std::endl;

        if (ok)
            *ok = false;

        castedData = 0;

        break;

    default:
        if (ok) {
            if (!(*ok = metaCast<size_t>(end - data) == std::char_traits<wchar_t>::length(data)))
                castedData = 0;
        } else {
            if (metaCast<size_t>(end - data) != std::char_traits<wchar_t>::length(data))
                castedData = 0;
        }

        break;
    }

    return castedData;
}

//! Convert wstring to arithmetic types
template<typename CastType,
         int Base = 10,
         typename std::enable_if<std::is_integral<CastType>::value>::type... Enabler>
inline auto metaCast(const std::wstring &data, bool *ok = nullptr) noexcept -> CastType
{
    return metaCast<CastType, Base>(data.data(), ok);
}

template<typename CastType,
         typename std::enable_if<std::is_floating_point<CastType>::value>::type... Enabler>
inline auto metaCast(const std::wstring &data, bool *ok = nullptr) noexcept -> CastType
{
    return metaCast<CastType>(data.data(), ok);
}

//! Convert arithmetic types to string
template<typename CastType,
         typename DataType,
         typename std::enable_if<(std::is_same<CastType, std::string>::value
                                 && std::is_arithmetic<DataType>::value)>::type... Enabler>
inline auto metaCast(DataType data) noexcept -> CastType
{
    try {
        return std::to_string(data);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return {};
    }
}

//! Convert arithmetic types to wstring
template<typename CastType,
         typename DataType,
         typename std::enable_if<(std::is_same<CastType, std::wstring>::value
                                 && std::is_arithmetic<DataType>::value)>::type... Enabler>
inline auto metaCast(DataType data) noexcept -> CastType
{
    try {
        return std::to_wstring(data);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return {};
    }
}

//! Convert cstring to wstring
template<typename CastType,
         typename std::enable_if<std::is_same<CastType, std::wstring>::value>::type... Enabler>
inline auto metaCast(const char *data) noexcept -> CastType
{
    try {
        std::wstring castedData {};
        castedData.resize(std::mbstowcs(nullptr, data, 0));

        if (std::mbstowcs(&castedData.front(), data, castedData.size()) == metaCast<size_t>(-1))
            return {};

        return castedData;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return {};
    }
}

//! Convert wcstring to string
template<typename CastType,
         typename std::enable_if<std::is_same<CastType, std::string>::value>::type... Enabler>
inline auto metaCast(const wchar_t *data) noexcept -> CastType
{
    try {
        std::string castedData {};
        castedData.resize(std::wcstombs(nullptr, data, 0));

        if (std::wcstombs(&castedData.front(), data, castedData.size()) == metaCast<size_t>(-1))
            return {};

        return castedData;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return {};
    }
}

//! Convert string to wstring
template<typename CastType,
         typename std::enable_if<std::is_same<CastType, std::wstring>::value>::type... Enabler>
inline auto metaCast(const std::string &data) noexcept -> CastType
{
    return metaCast<CastType>(data.data());
}

//! Convert wstring to string
template<typename CastType,
         typename std::enable_if<std::is_same<CastType, std::string>::value>::type... Enabler>
inline auto metaCast(const std::wstring &data) noexcept -> CastType
{
    return metaCast<CastType>(data.data());
}

} // end namespace Calibri

#endif // METACAST_H
