#ifndef FILESYSTEM_H
#define FILESYSTEM_H

//! Calibri-Library includes
#include "fileinfo.h"
#include "algorithm/split.h"

#if defined(OS_WINDOWS)
//! System includes
#   include <direct.h>
#endif

namespace Calibri {

inline constexpr auto isCaseSensitive() noexcept -> bool
{
#if defined(OS_WINDOWS)
    return false;
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return true;
#endif
}

inline bool isSeparator(char symbol) noexcept
{
    switch (symbol) {
    case '\\':
    case '/':
        return true;

    default:
        return false;
    }
}

inline constexpr auto nativeSeparator() noexcept -> char
{
#if defined(OS_WINDOWS)
    return '\\';
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return '/';
#endif
}

inline auto createDirectory(const std::string &path) noexcept -> bool
{
#if defined(OS_WINDOWS)
    return ::_mkdir(path.data()) == 0;
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::mkdir(path.data(), S_IRWXU | S_IRWXG | S_IRWXO) == 0;
#endif
}

inline auto createDirectories(const std::string &path) noexcept -> bool
{
    std::vector<std::string> directories {};

    if (!split(directories, path, &Internal::isSeparator))
        return false;

    return true;
}

} // end namespace Calibri

#endif // FILESYSTEM_H
