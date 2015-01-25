#ifndef FILEINFO_H
#define FILEINFO_H

//! Std includes
#include <string>

//! System includes
#include <sys/stat.h>

//! Calibri-Library includes
#include "global/global.h"

namespace Calibri {

//! Aliases
using FileStatus = _stat;

/*!
 *  FileInfo class
 */
class FileInfo
{
public:
    FileInfo(const std::string &path) noexcept;

    auto exists() const noexcept -> bool;
    auto isDirectory() const noexcept -> bool;
    auto isRegularFile() const noexcept -> bool;
    auto isOther() const noexcept -> bool;

private:
    FileStatus m_fileStatus {};

    bool m_exists {};
};

/*!
 *  FileInfo inline methods
 */
inline FileInfo::FileInfo(const std::string &path) noexcept
{
#if defined(OS_WINDOWS)
    m_exists = ::_stat(path.data(), &m_fileStatus) == 0;
#elif defined(OS_LINUX) || defined(OS_UNIX)
    m_exists = ::stat(path.data(), &m_fileStatus) == 0;
#endif
}

inline auto FileInfo::exists() const noexcept -> bool
{
    return m_exists;
}

inline auto FileInfo::isDirectory() const noexcept -> bool
{
    return S_ISDIR(m_fileStatus.st_mode);
}

inline auto FileInfo::isRegularFile() const noexcept -> bool
{
    return S_ISREG(m_fileStatus.st_mode);
}

inline auto FileInfo::isOther() const noexcept -> bool
{
    return !isDirectory() && !isRegularFile();
}

} // end namespace Calibri

#endif // FILEINFO_H
