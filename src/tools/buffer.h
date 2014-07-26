#ifndef BUFFER_H
#define BUFFER_H

//! Std Includes
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

//! Calibri-Library Includes
#include "global/global.h"

namespace Calibri {

class Buffer : public std::vector<char>
{
public:
    Buffer() noexcept;
    Buffer(size_t size) noexcept;
    Buffer(size_t size, char data) noexcept;
    Buffer(const char *ptr, size_t size) noexcept;
    Buffer(const char *ptr) noexcept;

    operator const char *() const noexcept;
    operator const void *() const noexcept;

    auto toUpper() const noexcept -> Buffer;
    auto toLower() const noexcept -> Buffer;
    auto toHex(bool *ok = nullptr) const noexcept -> Buffer;

    static auto fromHex(const Buffer &buffer, bool *ok = nullptr) noexcept -> Buffer;
};

/*!
 *  Buffer inline methods
 */
inline Buffer::Buffer() noexcept
    : std::vector<char>()
{
}

inline Buffer::Buffer(size_t size) noexcept
    : std::vector<char>(size)
{
}

inline Buffer::Buffer(size_t size, char data) noexcept
    : std::vector<char>(size, data)
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

inline auto Buffer::toUpper() const noexcept -> Buffer
{
    Buffer transformedData {};
    transformedData.reserve(size());

    std::transform(std::begin(*this), std::end(*this), std::back_inserter(transformedData), std::ptr_fun<int32, int32>(std::toupper));

    return transformedData;
}

inline auto Buffer::toLower() const noexcept -> Buffer
{
    Buffer transformedData {};
    transformedData.reserve(size());

    std::transform(std::begin(*this), std::end(*this), std::back_inserter(transformedData), std::ptr_fun<int32, int32>(std::tolower));

    return transformedData;
}

/*!
 *  ostream operators
 */
inline std::ostream &operator <<(std::ostream &stream, const Buffer &buffer)
{
    std::copy(std::begin(buffer), std::end(buffer), std::ostreambuf_iterator<char>(stream));

    return stream;
}

} // namespace Calibri

#endif // BUFFER_H
