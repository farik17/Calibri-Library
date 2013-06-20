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

//! CSocket Includes
#include "ctcpsocket.h"

#if _MSC_VER
#pragma warning(disable:4996)
#endif

inline void cdatastream_write(std::string &dest, const char *source, size_t &pos, size_t len)
{
    size_t length = dest.length();
    dest.insert(pos, source, len);
    pos += dest.length() - length;
}

inline void cdatastream_write(CTcpSocket &dest, const char *source, size_t &pos, size_t len)
{
    C_UNUSED(pos);
    dest.write(source, len);
}

inline void cdatastream_read(std::string &source, char *dest, size_t &pos, size_t len)
{
    pos += source.copy(dest, len, pos);
}

inline void cdatastream_read(CTcpSocket &source, char *dest, size_t &pos, size_t len)
{
    C_UNUSED(pos);
    source.read(dest, len);
}

template<class T>
class CDataStream
{
public:
    CDataStream(T &data)
        : m_data(data)
        , m_pos(0)
    {

    }

    void seek(size_t pos)
    {
        m_pos = pos;
    }

    size_t pos() const
    {
        return m_pos;
    }

    CDataStream<T> &operator <<(c_int8 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int8));
        return *this;
    }

    CDataStream<T> &operator <<(c_int16 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int16));
        return *this;
    }

    CDataStream<T> &operator <<(c_int32 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int32));
        return *this;
    }

    CDataStream<T> &operator <<(c_int64 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int64));
        return *this;
    }

    CDataStream<T> &operator <<(c_long value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_long));
        return *this;
    }

    CDataStream<T> &operator <<(c_uint8 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint8));
        return *this;
    }

    CDataStream<T> &operator <<(c_uint16 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint16));
        return *this;
    }

    CDataStream<T> &operator <<(c_uint32 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint32));
        return *this;
    }

    CDataStream<T> &operator <<(c_uint64 value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint64));
        return *this;
    }

    CDataStream<T> &operator <<(c_ulong value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_ulong));
        return *this;
    }

    CDataStream<T> &operator <<(bool value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(bool));
        return *this;
    }

    CDataStream<T> &operator <<(float value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(float));
        return *this;
    }

    CDataStream<T> &operator <<(double value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(double));
        return *this;
    }

    CDataStream<T> &operator <<(long double value)
    {
        cdatastream_write(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(long double));
        return *this;
    }

    CDataStream<T> &operator <<(const char *value)
    {
        c_uint64 size = std::char_traits<char>::length(value);

        if (size == 0)
            return *this;

        cdatastream_write(m_data, reinterpret_cast<const char *>(&size), m_pos, sizeof(c_uint64));
        cdatastream_write(m_data, value, m_pos, size);

        return *this;
    }

    CDataStream<T> &operator <<(const std::string &value)
    {
        c_uint64 size = value.size();

        if (size == 0)
            return *this;

        cdatastream_write(m_data, reinterpret_cast<const char *>(&size), m_pos, sizeof(c_uint64));
        cdatastream_write(m_data, value.c_str(), m_pos, size);

        return *this;
    }

    CDataStream<T> &operator >>(c_int8 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int8));
        return *this;
    }

    CDataStream<T> &operator >>(c_int16 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int16));
        return *this;
    }

    CDataStream<T> &operator >>(c_int32 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int32));
        return *this;
    }

    CDataStream<T> &operator >>(c_int64 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int64));
        return *this;
    }

    CDataStream<T> &operator >>(c_long &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_long));
        return *this;
    }

    CDataStream<T> &operator >>(c_uint8 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint8));
        return *this;
    }

    CDataStream<T> &operator >>(c_uint16 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint16));
        return *this;
    }

    CDataStream<T> &operator >>(c_uint32 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint32));
        return *this;
    }

    CDataStream<T> &operator >>(c_uint64 &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint64));
        return *this;
    }

    CDataStream<T> &operator >>(c_ulong &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_ulong));
        return *this;
    }

    CDataStream<T> &operator >>(bool &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(bool));
        return *this;
    }

    CDataStream<T> &operator >>(float &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(float));
        return *this;
    }

    CDataStream<T> &operator >>(double &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(double));
        return *this;
    }

    CDataStream<T> &operator >>(long double &value)
    {
        cdatastream_read(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(long double));
        return *this;
    }

    CDataStream<T> &operator >>(char *value)
    {
        c_uint64 size = 0;
        cdatastream_read(m_data, reinterpret_cast<char *>(&size), m_pos, sizeof(c_uint64));

        if (size == 0)
            return *this;

        cdatastream_read(m_data, value, m_pos, size);

        return *this;
    }

    CDataStream<T> &operator >>(std::string &value)
    {
        c_uint64 size = 0;
        cdatastream_read(m_data, reinterpret_cast<char *>(&size), m_pos, sizeof(c_uint64));

        if (size == 0)
            return *this;

        char *data = new char[size];
        cdatastream_read(m_data, data, m_pos, size);

        value.reserve(size);
        value.assign(data, size);

        delete[] data;

        return *this;
    }

private:
    C_DISABLE_COPY(CDataStream)

    T &m_data;

    size_t m_pos;
};

template<class T, typename D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::vector<D> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto it = data.cbegin();
    auto end = data.cend();
    while (it != end) {
        stream << (*it);
        ++it;
    }

    return stream;
}

template<class T, typename D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::list<D> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto it = data.cbegin();
    auto end = data.cend();
    while (it != end) {
        stream << (*it);
        ++it;
    }

    return stream;
}

template<class T, typename D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::set<D> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto it = data.cbegin();
    auto end = data.cend();
    while (it != end) {
        stream << (*it);
        ++it;
    }

    return stream;
}

template<class T, typename D, typename C>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::map<D, C> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto it = data.cbegin();
    auto end = data.cend();
    while (it != end) {
        stream << (*it).first;
        stream << (*it).second;
        ++it;
    }

    return stream;
}

template<class T, typename D, typename C>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::unordered_map<D, C> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto it = data.cbegin();
    auto end = data.cend();
    while (it != end) {
        stream << (*it).first;
        stream << (*it).second;
        ++it;
    }

    return stream;
}

template<class T, typename D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::unordered_set<D> &data)
{
    stream << static_cast<c_uint64>(data.size());

    auto it = data.cbegin();
    auto end = data.cend();
    while (it != end) {
        stream << (*it);
        ++it;
    }

    return stream;
}

template<class T, typename D>
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

template<class T, typename D>
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

template<class T, typename D>
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

template<class T, typename D, typename C>
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

template<class T, typename D, typename C>
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

template<class T, typename D>
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
