#ifndef CALIBRI_IO_IOINTERFACE_HPP
#define CALIBRI_IO_IOINTERFACE_HPP

//! Std includes
#include <string>

//! Calibri-Library includes
#include "global/type.hpp"

namespace Calibri {

namespace Io {

/*!
 *  IOInterface class
 */
class IOInterface
{
public:
    constexpr IOInterface() noexcept = default;

    auto read(char *data, sizeinfo size, bool *ok = nullptr) noexcept -> sizeinfo;

    auto write(const char *data, sizeinfo size, bool *ok = nullptr) noexcept -> sizeinfo;
    auto write(const char *data, bool *ok = nullptr) noexcept -> sizeinfo;

    auto getChar(char *character) noexcept -> bool;

    auto putChar(char character) noexcept -> bool;

protected:
    virtual auto readData(char *data, sizeinfo size, bool *ok = nullptr) noexcept -> sizeinfo = 0;
    virtual auto writeData(const char *data, sizeinfo size, bool *ok = nullptr) noexcept -> sizeinfo = 0;
};

/*!
 *  IOInterface inline methods
 */
inline auto IOInterface::read(char *data, sizeinfo size, bool *ok) noexcept -> sizeinfo
{
    return readData(data, size, ok);
}

inline auto IOInterface::write(const char *data, sizeinfo size, bool *ok) noexcept -> sizeinfo
{
    return writeData(data, size, ok);
}

inline auto IOInterface::write(const char *data, bool *ok) noexcept -> sizeinfo
{
    return write(data, std::char_traits<char>::length(data), ok);
}

inline auto IOInterface::getChar(char *character) noexcept -> bool
{
    if (read(character, 1) != 1)
        return false;

    return true;
}

inline auto IOInterface::putChar(char character) noexcept -> bool
{
    if (write(&character, 1) != 1)
        return false;

    return true;
}

} // end namespace Io

using Io::IOInterface;

} // end namespace Calibri

#endif // CALIBRI_IO_IOINTERFACE_HPP
