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
    std::vector<std::string> entries {};

    if (!split(entries, path, &Internal::isSeparator))
        return false;

#if defined(OS_WINDOWS)
    std::string currentEntry {};
#elif defined(OS_LINUX) || defined(OS_UNIX)
    std::string current { nativeSeparator() };
#endif

    for (auto &entry : entries) {
        std::string nextEntry { currentEntry + entry + nativeSeparator() };

        FileInfo fileInfo(nextEntry);

        if (fileInfo.isDirectory()) {
            currentEntry = std::move(nextEntry);

            continue;
        }

        if (!createDirectory(nextEntry))
            return false;

        currentEntry = std::move(nextEntry);
    }

    return true;
}

inline auto removeDirectory(const std::string &path) noexcept -> bool
{
#if defined(OS_WINDOWS)
    return ::_rmdir(path.data()) == 0;
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::rmdir(path.data()) == 0;
#endif
}

} // end namespace Calibri

#endif // FILESYSTEM_H
