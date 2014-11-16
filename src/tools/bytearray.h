#ifndef BYTEARRAY_H
#define BYTEARRAY_H

//! Std includes
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

//! Calibri-Library includes
#include "global/global.h"

namespace Calibri {

/*!
 *  ByteArray class
 */
class ByteArray : public std::vector<char>
{
public:
    ByteArray() noexcept;
    ByteArray(size_t size) noexcept;
    ByteArray(size_t size, char data) noexcept;
    ByteArray(const char *ptr, size_t size) noexcept;
    ByteArray(const char *ptr) noexcept;

    operator const char *() const noexcept;
    operator const void *() const noexcept;
    operator char *() noexcept;
    operator void *() noexcept;

    auto toUpper(bool *ok = nullptr) const noexcept -> ByteArray;
    auto toLower(bool *ok = nullptr) const noexcept -> ByteArray;
    auto toHex(bool *ok = nullptr) const noexcept -> ByteArray;
    auto toBase64(bool *ok = nullptr) const noexcept -> ByteArray;

    static auto fromHex(const ByteArray &data, bool *ok = nullptr) noexcept -> ByteArray;
    static auto fromBase64(const ByteArray &data, bool *ok = nullptr) noexcept -> ByteArray;
};

/*!
 *  ByteArray inline methods
 */
inline ByteArray::ByteArray() noexcept
    : std::vector<char>()
{
}

inline ByteArray::ByteArray(size_t size) noexcept
    : std::vector<char>(size)
{
}

inline ByteArray::ByteArray(size_t size, char data) noexcept
    : std::vector<char>(size, data)
{
}

inline ByteArray::ByteArray(const char *ptr, size_t size) noexcept
    : std::vector<char>(ptr, std::next(ptr, size))
{
}

inline ByteArray::ByteArray(const char *ptr) noexcept
    : ByteArray(ptr, std::char_traits<char>::length(ptr))
{
}

inline ByteArray::operator const char *() const noexcept
{
    return data();
}

inline ByteArray::operator const void *() const noexcept
{
    return data();
}

inline ByteArray::operator char *() noexcept
{
    return data();
}

inline ByteArray::operator void *() noexcept
{
    return data();
}

inline auto ByteArray::toUpper(bool *ok) const noexcept -> ByteArray
{
    try {
        ByteArray transformedData {};
        transformedData.reserve(size());

        std::transform(std::begin(*this), std::end(*this), std::back_inserter(transformedData), std::ptr_fun<int32, int32>(std::toupper));

        if (ok)
            *ok = true;

        return transformedData;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

inline auto ByteArray::toLower(bool *ok) const noexcept -> ByteArray
{
    try {
        ByteArray transformedData {};
        transformedData.reserve(size());

        std::transform(std::begin(*this), std::end(*this), std::back_inserter(transformedData), std::ptr_fun<int32, int32>(std::tolower));

        if (ok)
            *ok = true;

        return transformedData;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

/*!
 *  ostream operators
 */
inline auto operator <<(std::ostream &stream, const ByteArray &byteArray) noexcept -> std::ostream &
{
    try {
        std::copy(std::begin(byteArray), std::end(byteArray), std::ostreambuf_iterator<char>(stream));
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;
    }

    return stream;
}

} // end namespace Calibri

#endif // BYTEARRAY_H
