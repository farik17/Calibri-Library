#ifndef BUFFER_H
#define BUFFER_H

//! Std Includes
#include <vector>
#include <string>
#include <ostream>

namespace Calibri {

class Buffer : public std::vector<char>
{
public:
    Buffer() noexcept;
    Buffer(const char *ptr, size_t size) noexcept;
    Buffer(const char *ptr) noexcept;

    operator const char *() const noexcept;
    operator const void *() const noexcept;

    auto toHex(const Buffer &buffer) const noexcept -> Buffer;
};

/*!
 * Buffer inline methods
 */
inline Buffer::Buffer() noexcept
    : std::vector<char>()
{
}

inline Buffer::Buffer(const char *ptr, size_t size) noexcept
    : std::vector<char>(ptr, std::next(ptr, size))
{
}

inline Buffer::Buffer(const char *ptr) noexcept
    : Buffer(ptr, std::char_traits<char>::length(ptr))
{
}

inline Buffer::operator const char *() const noexcept
{
    return data();
}

inline Buffer::operator const void *() const noexcept
{
    return data();
}

/*!
 * ostream operators
 */
inline std::ostream &operator <<(std::ostream &stream, const Buffer &buffer)
{
    return stream << buffer.data() << std::flush;
}

} // namespace Calibri

#endif // BUFFER_H
