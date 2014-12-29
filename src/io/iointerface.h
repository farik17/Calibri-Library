#ifndef IOINTERFACE_H
#define IOINTERFACE_H

//! Std includes
#include <cstddef>
#include <string>

//! Calibri-Library includes
#include "global/global.h"

namespace Calibri {

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

/*!
 *  IORandomAccessInterface class
 */
class IORandomAccessInterface : public IOInterface
{
public:
    constexpr IORandomAccessInterface() noexcept = default;

    auto pos() const noexcept -> sizeinfo;
    auto seek(sizeinfo pos) noexcept -> bool;
    auto reset() noexcept -> void;

    auto readLine(char *data, sizeinfo size, bool *ok = nullptr) noexcept -> sizeinfo;

    virtual auto canReadLine() const noexcept -> bool = 0;
    virtual auto atEnd() const noexcept -> bool = 0;

protected:
    auto setPos(sizeinfo pos) noexcept -> void;

    virtual auto readLineData(char *data, sizeinfo size, bool *ok = nullptr) noexcept -> sizeinfo = 0;
    virtual auto seekData(sizeinfo pos) noexcept -> bool = 0;

private:
    sizeinfo m_pos {};
};

/*!
 *  IORandomAccessInterface inline methods
 */
inline auto IORandomAccessInterface::pos() const noexcept -> sizeinfo
{
    return m_pos;
}

inline auto IORandomAccessInterface::seek(sizeinfo pos) noexcept -> bool
{
    return seekData(pos);
}

inline auto IORandomAccessInterface::reset() noexcept -> void
{
    setPos(0);
}

inline auto IORandomAccessInterface::readLine(char *data, sizeinfo size, bool *ok) noexcept -> sizeinfo
{
    return readLineData(data, size, ok);
}

inline auto IORandomAccessInterface::setPos(sizeinfo pos) noexcept -> void
{
    m_pos = pos;
}

} // end namespace Calibri

#endif // IOINTERFACE_H
