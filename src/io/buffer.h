#ifndef BUFFER_H
#define BUFFER_H

//! Calibri-Library includes
#include "iointerface.h"
#include "tools/bytearray.h"

namespace Calibri {

/*!
 *  Buffer class
 */
class Buffer : public IORandomAccessInterface
{
public:
    Buffer() noexcept = default;
    Buffer(const ByteArray &data) noexcept;
    Buffer(const char *data, sizeinfo size) noexcept;
    Buffer(const char *data) noexcept;
    Buffer(Buffer &&other) noexcept;

    auto operator =(Buffer &&other) noexcept -> Buffer &;

    auto data() const noexcept -> const ByteArray &;
    auto size() const noexcept -> sizeinfo;

    using IORandomAccessInterface::read;
    auto read(sizeinfo size, bool *ok = nullptr) noexcept -> ByteArray;

    using IORandomAccessInterface::write;
    auto write(const ByteArray &data, bool *ok = nullptr) noexcept -> sizeinfo;

    virtual auto canReadLine() const noexcept -> bool override;
    virtual auto atEnd() const noexcept -> bool override;

protected:
    virtual auto readData(char *data, sizeinfo size, bool *ok = nullptr) noexcept -> sizeinfo override;
    virtual auto writeData(const char *data, sizeinfo size, bool *ok = nullptr) noexcept -> sizeinfo override;
    virtual auto readLineData(char *data, sizeinfo size, bool *ok = nullptr) noexcept -> sizeinfo override;
    virtual auto seekData(sizeinfo pos) noexcept -> bool override;

private:
    ByteArray m_byteArray {};
};

/*!
 *  Buffer inline methods
 */
inline Buffer::Buffer(const ByteArray &data) noexcept :
    m_byteArray { data }
{
}

inline Buffer::Buffer(const char *data, sizeinfo size) noexcept :
    m_byteArray { data, size }
{
}

inline Buffer::Buffer(const char *data) noexcept :
    m_byteArray { data }
{
}

inline Buffer::Buffer(Buffer &&other) noexcept :
    m_byteArray { std::move(other.m_byteArray) }
{
    setPos(other.pos());

    other.reset();
}

inline auto Buffer::operator =(Buffer &&other) noexcept -> Buffer &
{
    m_byteArray = std::move(other.m_byteArray);

    setPos(other.pos());

    other.reset();

    return *this;
}

inline auto Buffer::data() const noexcept -> const ByteArray &
{
    return m_byteArray;
}

inline auto Buffer::size() const noexcept -> sizeinfo
{
    return m_byteArray.size();
}

/*!
 *  ostream operators
 */
inline auto operator <<(std::ostream &stream, const Buffer &buffer) noexcept -> std::ostream &
{
    return stream << buffer.data();
}

} // end namespace Calibri

#endif // BUFFER_H
