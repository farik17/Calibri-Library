#ifndef FILEINFO_H
#define FILEINFO_H

//! Std includes
#include <string>

//! System includes
#include <sys/stat.h>

//! Calibri-Library includes
#include "global/global.h"

namespace Calibri {

namespace Internal {

#if defined(OS_WINDOWS)
//! Aliases
using FileStatus = _stat;

inline auto getFileStatus(const std::string &path, FileStatus &fileStatus)
{
    return ::_stat(path.data(), &fileStatus);
}

inline bool isDirectoryStatus(const FileStatus &fileStatus)
{
    return S_ISDIR(fileStatus.st_mode);
}

inline bool isRegularFileStatus(const FileStatus &fileStatus)
{
    return S_ISREG(fileStatus.st_mode);
}

inline bool isSymLinkStatus(const FileStatus &)
{
    return false;
}
#elif defined(OS_LINUX) || defined(OS_UNIX)
//! Aliases
using FileStatus = stat;

inline auto getFileStatus(const std::string &path, FileStatus &fileStatus)
{
    return ::stat(path.data(), &fileStatus);
}

inline bool isDirectoryStatus(const FileStatus &fileStatus)
{
    return S_ISDIR(fileStatus.st_mode);
}

inline bool isRegularFileStatus(const FileStatus &fileStatus)
{
    return S_ISREG(fileStatus.st_mode);
}

inline bool isSymLinkStatus(const FileStatus &)
{
    return S_ISLNK(fileStatus.st_mode);
}
#endif

}

/*!
 *  FileInfo class
 */
class FileInfo
{
public:
    FileInfo(const std::string &path) noexcept;

    auto isExists() const noexcept -> bool;
    auto isDirectory() const noexcept -> bool;
    auto isRegularFile() const noexcept -> bool;
    auto isSymLink() const noexcept -> bool;
    auto isOther() const noexcept -> bool;

private:
    Internal::FileStatus m_fileStatus {};

    bool m_exists {};
};

/*!
 *  FileInfo inline methods
 */
inline FileInfo::FileInfo(const std::string &path) noexcept
{
    m_exists = Internal::getFileStatus(path, &m_fileStatus);
}

inline auto FileInfo::isExists() const noexcept -> bool
{
    return m_exists;
}

inline auto FileInfo::isDirectory() const noexcept -> bool
{
    return Internal::isDirectoryStatus(m_fileStatus);
}

inline auto FileInfo::isRegularFile() const noexcept -> bool
{
    return Internal::isRegularFileStatus(m_fileStatus);
}

inline auto FileInfo::isSymLink() const noexcept -> bool
{
    return Internal::isSymLinkStatus(m_fileStatus);
}

inline auto FileInfo::isOther() const noexcept -> bool
{
    return !isDirectory() && !isRegularFile() && !isSymLink();
}

} // end namespace Calibri

#endif // FILEINFO_H
