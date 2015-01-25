#ifndef FILEINFO_H
#define FILEINFO_H

//! Calibri-Library includes
#include "global/global.h"
#include "tools/metacast.h"

//! System includes
#if defined(OS_WINDOWS)
#   include <windows.h>
#elif defined(OS_LINUX) || defined(OS_UNIX)
#   include <sys/stat.h>
#endif

namespace Calibri {

//! Enumerations
enum class FileType : uint8 {
    FileNotFound,
    RegularFile,
    DirectoryFile,
    SymLinkFile,
    UnknownFile
};

namespace Internal {

//! Aliases
#if defined(OS_WINDOWS)
using FileStatus = WIN32_FILE_ATTRIBUTE_DATA;
#elif defined(OS_LINUX) || defined(OS_UNIX)
using FileStatus = _stat;
#endif

inline auto getFileStatus(const std::string &path, FileStatus &fileStatus) noexcept -> bool
{
#if defined(OS_WINDOWS)
#   if defined(UNICODE)
    return ::GetFileAttributesEx(metaCast<std::wstring>(path).data(), GetFileExInfoStandard, &fileStatus);
#   else
    return ::GetFileAttributesEx(path.data(), GetFileExInfoStandard, &fileStatus);
#   endif
#elif defined(OS_LINUX) || defined(OS_UNIX)
    return ::stat(path.data(), &fileStatus) == 0;
#endif
}

inline auto getFileType(const FileStatus &fileStatus) noexcept -> FileType
{
#if defined(OS_WINDOWS)
    // TODO : symlink
    if (fileStatus.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
        return FileType::UnknownFile;

    if (fileStatus.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        return FileType::DirectoryFile;
    else
        return FileType::RegularFile;

    return FileType::UnknownFile;
#elif defined(OS_LINUX) || defined(OS_UNIX)
    switch (fileStatus.st_mode & S_IFMT) {
    case S_IFLNK:
        return FileType::SymLinkFile;

    case S_IFDIR:
        return FileType::DirectoryFile;

    case S_IFREG:
        return FileType::RegularFile;

    default:
        return FileType::UnknownFile;
    }
#endif
}

} // end namespace Internal

/*!
 *  FileInfo class
 */
class FileInfo
{
public:
    FileInfo(const std::string &path) noexcept;

    auto type() const noexcept -> FileType;
    auto exists() const noexcept -> bool;
    auto isDirectory() const noexcept -> bool;
    auto isRegularFile() const noexcept -> bool;
    auto isSymLink() const noexcept -> bool;
    auto isOther() const noexcept -> bool;

private:
    FileType m_fileType {};
};

/*!
 *  FileInfo inline methods
 */
inline FileInfo::FileInfo(const std::string &path) noexcept
{
    Internal::FileStatus fileStatus {};

    if (Internal::getFileStatus(path, fileStatus)) {
        m_fileType = Internal::getFileType(fileStatus);
    } else {
        m_fileType = FileType::FileNotFound;
    }
}

inline auto FileInfo::type() const noexcept -> FileType
{
    return m_fileType;
}

inline auto FileInfo::exists() const noexcept -> bool
{
    return m_fileType != FileType::FileNotFound;
}

inline auto FileInfo::isDirectory() const noexcept -> bool
{
    return m_fileType == FileType::DirectoryFile;
}

inline auto FileInfo::isRegularFile() const noexcept -> bool
{
    return m_fileType == FileType::RegularFile;
}

inline auto FileInfo::isSymLink() const noexcept -> bool
{
    return m_fileType == FileType::SymLinkFile;
}

inline auto FileInfo::isOther() const noexcept -> bool
{
    return !isDirectory() && !isRegularFile() && !isSymLink();
}

} // end namespace Calibri

#endif // FILEINFO_H
