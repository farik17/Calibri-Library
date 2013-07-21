/****************************************************************************
**
** Copyright (c) 2013 Calibri-Software <calibrisoftware@gmail.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
**
****************************************************************************/

#ifndef CDATASTREAM_H
#define CDATASTREAM_H

//! Std Includes
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

//! CSocket Includes
#include "ctcpsocket.h"

#if _MSC_VER
#pragma warning(disable:4996)
#endif

inline const size_t cdatastream_write(std::string &dest, const char *source, size_t &pos, const size_t len)
{
    dest.replace(pos, len, source, len);
    pos += len;

    return len;
}

inline const size_t cdatastream_write(CTcpSocket &dest, const char *source, size_t &pos, const size_t len)
{
    C_UNUSED(pos);

    return dest.write(source, len);
}

inline const size_t cdatastream_read(std::string &source, char *dest, size_t &pos, const size_t len)
{
    size_t bytes = source.copy(dest, len, pos);
    pos += bytes;

    return bytes;
}

inline const size_t cdatastream_read(CTcpSocket &source, char *dest, size_t &pos, const size_t len)
{
    C_UNUSED(pos);

    return source.read(dest, len);
}

template<class T>
class CDataStream
{
public:
    explicit CDataStream(T &data)
        : m_data(data)
        , m_pos(0)
    {

    }

    inline void seek(const size_t pos)
    {
        m_pos = pos;
    }

    inline const size_t pos() const
    {
        return m_pos;
    }

    inline CDataStream<T> &operator <<(const c_int8 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int8));

        return *this;
    }

    inline CDataStream<T> &operator <<(const c_int16 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int16));

        return *this;
    }

    inline CDataStream<T> &operator <<(const c_int32 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int32));

        return *this;
    }

    inline CDataStream<T> &operator <<(const c_int64 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int64));

        return *this;
    }

    inline CDataStream<T> &operator <<(const c_long value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_long));

        return *this;
    }

    inline CDataStream<T> &operator <<(const c_uint8 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint8));

        return *this;
    }

    inline CDataStream<T> &operator <<(const c_uint16 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint16));

        return *this;
    }

    inline CDataStream<T> &operator <<(const c_uint32 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint32));

        return *this;
    }

    inline CDataStream<T> &operator <<(const c_uint64 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint64));

        return *this;
    }

    inline CDataStream<T> &operator <<(const c_ulong value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_ulong));

        return *this;
    }

    inline CDataStream<T> &operator <<(const bool value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(bool));

        return *this;
    }

    inline CDataStream<T> &operator <<(const float value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(float));

        return *this;
    }

    inline CDataStream<T> &operator <<(const double value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(double));

        return *this;
    }

    inline CDataStream<T> &operator <<(const long double value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(long double));

        return *this;
    }

    inline CDataStream<T> &operator <<(const char *value)
    {
        c_uint64 size = std::char_traits<char>::length(value);

        if (size == 0)
            return *this;

        *this << size;

        cdatastream_write(m_data, value, m_pos, size);

        return *this;
    }

    inline CDataStream<T> &operator <<(const std::string &value)
    {
        c_uint64 size = value.size();

        if (size == 0)
            return *this;

        *this << size;

        cdatastream_write(m_data, value.c_str(), m_pos, size);

        return *this;
    }

    inline CDataStream<T> &operator >>(c_int8 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int8));

        return *this;
    }

    inline CDataStream<T> &operator >>(c_int16 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int16));

        return *this;
    }

    inline CDataStream<T> &operator >>(c_int32 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int32));

        return *this;
    }

    inline CDataStream<T> &operator >>(c_int64 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int64));

        return *this;
    }

    inline CDataStream<T> &operator >>(c_long &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_long));

        return *this;
    }

    inline CDataStream<T> &operator >>(c_uint8 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint8));

        return *this;
    }

    inline CDataStream<T> &operator >>(c_uint16 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint16));

        return *this;
    }

    inline CDataStream<T> &operator >>(c_uint32 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint32));

        return *this;
    }

    inline CDataStream<T> &operator >>(c_uint64 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint64));

        return *this;
    }

    inline CDataStream<T> &operator >>(c_ulong &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_ulong));

        return *this;
    }

    inline CDataStream<T> &operator >>(bool &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(bool));

        return *this;
    }

    inline CDataStream<T> &operator >>(float &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(float));

        return *this;
    }

    inline CDataStream<T> &operator >>(double &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(double));

        return *this;
    }

    inline CDataStream<T> &operator >>(long double &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(long double));

        return *this;
    }

    inline CDataStream<T> &operator >>(char *value)
    {
        c_uint64 size = 0;
        *this >> size;

        if (size == 0)
            return *this;

        cdatastream_read(m_data, value, m_pos, size);

        return *this;
    }

    inline CDataStream<T> &operator >>(std::string &value)
    {
        c_uint64 size = 0;
        *this >> size;

        if (size == 0)
            return *this;

        char data[1024];
        size_t bytes = 0;

        do {
            bytes = cdatastream_read(m_data, data, m_pos, std::min<c_uint64>(size, 1024));
            if (bytes == 0)
                break;

            size -= bytes;

            value.append(data, bytes);
        } while (size > 0);

        return *this;
    }

private:
    C_DISABLE_COPY(CDataStream)

    T &m_data;

    size_t m_pos;
};

template<class T, class D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::vector<D> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto dataIt = data.cbegin();
    auto dataEnd = data.cend();
    while (dataIt != dataEnd) {
        stream << (*dataIt);
        ++dataIt;
    }

    return stream;
}

template<class T, class D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::list<D> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto dataIt = data.cbegin();
    auto dataEnd = data.cend();
    while (dataIt != dataEnd) {
        stream << (*dataIt);
        ++dataIt;
    }

    return stream;
}

template<class T, class D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::set<D> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto dataIt = data.cbegin();
    auto dataEnd = data.cend();
    while (dataIt != dataEnd) {
        stream << (*dataIt);
        ++dataIt;
    }

    return stream;
}

template<class T, class D, class C>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::map<D, C> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto dataIt = data.cbegin();
    auto dataEnd = data.cend();
    while (dataIt != dataEnd) {
        stream << (*dataIt).first;
        stream << (*dataIt).second;
        ++dataIt;
    }

    return stream;
}

template<class T, class D, class C>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::unordered_map<D, C> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto dataIt = data.cbegin();
    auto dataEnd = data.cend();
    while (dataIt != dataEnd) {
        stream << (*dataIt).first;
        stream << (*dataIt).second;
        ++dataIt;
    }

    return stream;
}

template<class T, class D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::unordered_set<D> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto dataIt = data.cbegin();
    auto dataEnd = data.cend();
    while (dataIt != dataEnd) {
        stream << (*dataIt);
        ++dataIt;
    }

    return stream;
}

template<class T, class D>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::vector<D> &data)
{
    c_uint64 size = 0;
    stream >> size;

    if (size == 0)
        return stream;

    data.reserve(size);

    c_uint64 ix = 0;
    while (ix < size) {
        D value;
        stream >> value;

        data.push_back(value);

        ++ix;
    }

    return stream;
}

template<class T, class D>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::list<D> &data)
{
    c_uint64 size = 0;
    stream >> size;

    if (size == 0)
        return stream;

    c_uint64 ix = 0;
    while (ix < size) {
        D value;
        stream >> value;

        data.push_back(value);

        ++ix;
    }

    return stream;
}

template<class T, class D>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::set<D> &data)
{
    c_uint64 size = 0;
    stream >> size;

    if (size == 0)
        return stream;

    c_uint64 ix = 0;
    while (ix < size) {
        D value;
        stream >> value;

        data.insert(value);

        ++ix;
    }

    return stream;
}

template<class T, class D, class C>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::map<D, C> &data)
{
    c_uint64 size = 0;
    stream >> size;

    if (size == 0)
        return stream;

    c_uint64 ix = 0;
    while (ix < size) {
        D key;
        C value;
        stream >> key;
        stream >> value;

        data[key] = value;

        ++ix;
    }

    return stream;
}

template<class T, class D, class C>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::unordered_map<D, C> &data)
{
    c_uint64 size = 0;
    stream >> size;

    if (size == 0)
        return stream;

    data.reserve(size);

    c_uint64 ix = 0;
    while (ix < size) {
        D key;
        C value;
        stream >> key;
        stream >> value;

        data[key] = value;

        ++ix;
    }

    return stream;
}

template<class T, class D>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::unordered_set<D> &data)
{
    c_uint64 size = 0;
    stream >> size;

    if (size == 0)
        return stream;

    data.reserve(size);

    c_uint64 ix = 0;
    while (ix < size) {
        D value;
        stream >> value;

        data.insert(value);

        ++ix;
    }

    return stream;
}

#endif // CDATASTREAM_H
