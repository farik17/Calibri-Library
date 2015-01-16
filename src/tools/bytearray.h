#ifndef BYTEARRAY_H
#define BYTEARRAY_H

//! Std includes
#include <vector>
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
    ByteArray() = default;
    ByteArray(sizeinfo size);
    ByteArray(sizeinfo size, char symbol);
    ByteArray(const char *data, sizeinfo size);
    ByteArray(const char *data);

    operator const char *() const noexcept;
    operator const void *() const noexcept;
    operator char *() noexcept;
    operator void *() noexcept;

    auto trimmed(bool *ok = nullptr) const & noexcept -> ByteArray;
    auto trimmed(bool *ok = nullptr) && noexcept -> ByteArray;
    auto toUpper(bool *ok = nullptr) const & noexcept -> ByteArray;
    auto toUpper(bool *ok = nullptr) && noexcept -> ByteArray &&;
    auto toLower(bool *ok = nullptr) const & noexcept -> ByteArray;
    auto toLower(bool *ok = nullptr) && noexcept -> ByteArray &&;
    auto toHex(bool *ok = nullptr) const noexcept -> ByteArray;
    auto toBase64(bool *ok = nullptr) const noexcept -> ByteArray;

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

inline auto ByteArray::trimmed(bool *ok) const & noexcept -> ByteArray
{
    try {
        auto from = std::find_if(std::begin(*this), std::end(*this), [](char symbol) noexcept {
            return !::isspace(symbol);
        });

        if (from == std::end(*this)) {
            if (ok)
                *ok = false;

            return {};
        }

        auto to = std::find_if(crbegin(), crend(), [](char symbol) noexcept {
            return !::isspace(symbol);
        }).base();

        ByteArray trimmedData {};
        trimmedData.reserve(std::distance(from ,to));

        std::copy(from, to, std::back_inserter(trimmedData));

        if (ok)
            *ok = true;

        return trimmedData;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

inline auto ByteArray::trimmed(bool *ok) && noexcept -> ByteArray
{
    try {
        auto it = std::find_if(std::begin(*this), std::end(*this), [](char symbol) noexcept {
            return !::isspace(symbol);
        });

        if (it == std::end(*this)) {
            if (ok)
                *ok = false;

            clear();

            return std::move(*this);
        }

        erase(std::begin(*this), it);

        it = std::find_if(rbegin(), rend(), [](char symbol) noexcept {
            return !::isspace(symbol);
        }).base();

        erase(it, std::end(*this));

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

#endif // BYTEARRAY_H
