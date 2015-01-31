#ifndef CALIBRI_TOOL_BYTEARRAY_HPP
#define CALIBRI_TOOL_BYTEARRAY_HPP

//! Std includes
#include <vector>
#include <iostream>
#include <algorithm>

//! Calibri-Library includes
#include "global/type.hpp"

namespace Calibri {

/*!
 *  ByteArray class
 */
class ByteArray : public std::vector<char>
{
public:
    ByteArray() = default;
    ByteArray(sizeinfo size);
    ByteArray(sizeinfo size, char symbol);
    ByteArray(const char *data, sizeinfo size);
    ByteArray(const char *data);
    ByteArray(ByteArray::const_iterator from, ByteArray::const_iterator to);

    operator const char *() const noexcept;
    operator const void *() const noexcept;
    operator char *() noexcept;
    operator void *() noexcept;

    auto toUpper(bool *ok = nullptr) const & noexcept -> ByteArray;
    auto toUpper(bool *ok = nullptr) && noexcept -> ByteArray &&;
    auto toLower(bool *ok = nullptr) const & noexcept -> ByteArray;
    auto toLower(bool *ok = nullptr) && noexcept -> ByteArray &&;

    auto toHex(bool *ok = nullptr) const noexcept -> ByteArray;
    auto toBase64(bool *ok = nullptr) const noexcept -> ByteArray;

    auto startsWith(const ByteArray &data) const noexcept -> bool;
    auto endsWith(const ByteArray &data) const noexcept -> bool;

    static auto fromHex(const ByteArray &data, bool *ok = nullptr) noexcept -> ByteArray;
    static auto fromBase64(const ByteArray &data, bool *ok = nullptr) noexcept -> ByteArray;
};

/*!
 *  ByteArray inline methods
 */
inline ByteArray::ByteArray(sizeinfo size) :
    std::vector<char>(size)
{
}

inline ByteArray::ByteArray(sizeinfo size, char symbol) :
    std::vector<char>(size, symbol)
{
}

inline ByteArray::ByteArray(const char *data, sizeinfo size) :
    std::vector<char>(data, std::next(data, size))
{
}

inline ByteArray::ByteArray(const char *data) :
    ByteArray(data, std::char_traits<char>::length(data))
{
}

inline ByteArray::ByteArray(ByteArray::const_iterator from, ByteArray::const_iterator to) :
    std::vector<char>(from ,to)
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

inline auto ByteArray::toUpper(bool *ok) const & noexcept -> ByteArray
{
    try {
        ByteArray transformedData {};
        transformedData.reserve(size());

        std::transform(std::begin(*this), std::end(*this), std::back_inserter(transformedData), ::toupper);

        if (ok)
            *ok = true;

        return transformedData;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

inline auto ByteArray::toUpper(bool *ok) && noexcept -> ByteArray &&
{
    try {
        std::transform(std::begin(*this), std::end(*this), std::begin(*this), ::toupper);

        if (ok)
            *ok = true;

        return std::move(*this);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        clear();

        return std::move(*this);
    }
}

inline auto ByteArray::toLower(bool *ok) const & noexcept -> ByteArray
{
    try {
        ByteArray transformedData {};
        transformedData.reserve(size());

        std::transform(std::begin(*this), std::end(*this), std::back_inserter(transformedData), ::tolower);

        if (ok)
            *ok = true;

        return transformedData;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

inline auto ByteArray::toLower(bool *ok) && noexcept -> ByteArray &&
{
    try {
        std::transform(std::begin(*this), std::end(*this), std::begin(*this), ::tolower);

        if (ok)
            *ok = true;

        return std::move(*this);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        clear();

        return std::move(*this);
    }
}

inline auto ByteArray::startsWith(const ByteArray &data) const noexcept -> bool
{
    try {
        if (data.size() > size())
            return false;

        return std::equal(std::begin(*this), std::next(std::begin(*this), data.size()), std::begin(data));
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return false;
    }
}

inline auto ByteArray::endsWith(const ByteArray &data) const noexcept -> bool
{
    try {
        if (data.size() > size())
            return false;

        return std::equal(crbegin(), std::next(crbegin(), data.size()), data.crbegin());
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return false;
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
        std::cerr << __func__ << " : " << ex.what() << std::endl;
    }

    return stream;
}

} // end namespace Calibri

#endif // CALIBRI_TOOL_BYTEARRAY_HPP
