#ifndef IOINTERFACE_H
#define IOINTERFACE_H

//! Std includes
#include <cstddef>
#include <string>

namespace Calibri {

/*!
 *  IOInterface class
 */
class IOInterface
{
public:
    constexpr IOInterface() noexcept;

    auto read(char *data, size_t size, bool *ok = nullptr) noexcept -> size_t;

    auto write(const char *data, size_t size, bool *ok = nullptr) noexcept -> size_t;
    auto write(const char *data, bool *ok = nullptr) noexcept -> size_t;

    auto getChar(char *character) noexcept -> bool;

    auto putChar(char character) noexcept -> bool;

protected:
    virtual auto readData(char *data, size_t size, bool *ok = nullptr) noexcept -> size_t = 0;
    virtual auto writeData(const char *data, size_t size, bool *ok = nullptr) noexcept -> size_t = 0;
};

/*!
 *  IOInterface inline methods
 */
inline constexpr IOInterface::IOInterface() noexcept
{
}

inline auto IOInterface::read(char *data, size_t size, bool *ok) noexcept -> size_t
{
    return readData(data, size, ok);
}

inline auto IOInterface::write(const char *data, size_t size, bool *ok) noexcept -> size_t
{
    return writeData(data, size, ok);
}

inline auto IOInterface::write(const char *data, bool *ok) noexcept -> size_t
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
    constexpr IORandomAccessInterface() noexcept;

    auto pos() const noexcept -> size_t;
    auto seek(size_t pos) noexcept -> bool;
    auto reset() noexcept -> void;

    auto readLine(char *data, size_t size, bool *ok = nullptr) noexcept -> size_t;

    virtual auto canReadLine() const noexcept -> bool = 0;
    virtual auto atEnd() const noexcept -> bool = 0;

protected:
    auto setPos(size_t pos) noexcept -> void;

    virtual auto readLineData(char *data, size_t size, bool *ok = nullptr) noexcept -> size_t = 0;
    virtual auto seekData(size_t pos) noexcept -> bool = 0;

private:
    size_t m_pos {};
};

/*!
 *  IORandomAccessInterface inline methods
 */
inline constexpr IORandomAccessInterface::IORandomAccessInterface() noexcept
{
}

inline auto IORandomAccessInterface::pos() const noexcept -> size_t
{
    return m_pos;
}

inline auto IORandomAccessInterface::seek(size_t pos) noexcept -> bool
{
    return seekData(pos);
}

inline auto IORandomAccessInterface::reset() noexcept -> void
{
    setPos(0);
}

inline auto IORandomAccessInterface::readLine(char *data, size_t size, bool *ok) noexcept -> size_t
{
    return readLineData(data, size, ok);
}

inline auto IORandomAccessInterface::setPos(size_t pos) noexcept -> void
{
    m_pos = pos;
}

} // end namespace Calibri

#endif // IOINTERFACE_H
