#ifndef CALIBRI_FILESYSTEM_FILESYSTEMENGINE_HPP
#define CALIBRI_FILESYSTEM_FILESYSTEMENGINE_HPP

//! Calibri-Library includes
#include "fileinfo.hpp"
#include "algorithms/split.hpp"

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
#   if defined(UNICODE)
    return ::CreateDirectory(metaCast<std::wstring>(path).data(), nullptr);
#   else
    return ::CreateDirectory(path.data(), nullptr);
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::mkdir(path.data(), S_IRWXU | S_IRWXG | S_IRWXO) == 0;
#endif
}

inline auto removeDirectory(const std::string &path) noexcept -> bool
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    return ::RemoveDirectory(metaCast<std::wstring>(path).data());
#   else
    return ::RemoveDirectory(path.data());
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::rmdir(path.data()) == 0;
#endif
}

inline auto createDirectories(const std::string &path) noexcept -> bool
{
    try {
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
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return false;
    }
}

} // end namespace Calibri

#endif // CALIBRI_FILESYSTEM_FILESYSTEMENGINE_HPP
