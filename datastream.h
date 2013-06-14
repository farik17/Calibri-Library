#ifndef DATASTREAM_H
#define DATASTREAM_H

//! Project Includes
#include "defines.h"

//! Std Includes
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <functional>

template<class T>
class CDataStream
{
public:
    CDataStream(T &data)
        : m_data(data)
        , m_pos(0)
        , m_readFunction(nullptr)
        , m_writeFunction(nullptr)
    {

    }

    void setReadFunction(const std::function<void (T &source, char *dest, size_t &pos, size_t len)> &readFunction)
    {
        m_readFunction = readFunction;
    }

    void setWriteFunction(const std::function<void (T &dest, const char *source, size_t &pos, size_t len)> &writeFunction)
    {
        m_writeFunction = writeFunction;
    }

    void unsetReadFunction()
    {
        m_readFunction = nullptr;
    }

    void unsetWriteFunction()
    {
        m_writeFunction = nullptr;
    }

    size_t pos() const
    {
        return m_pos;
    }

    void seek(size_t pos)
    {
        m_pos = pos;
    }

    /*! Write */
    CDataStream<T> &operator <<(c_int8 value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int8));
        return *this;
    }

    CDataStream<T> &operator <<(c_int16 value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int16));
        return *this;
    }

    CDataStream<T> &operator <<(c_int32 value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int32));
        return *this;
    }

    CDataStream<T> &operator <<(c_int64 value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_int64));
        return *this;
    }

    CDataStream<T> &operator <<(c_long value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_long));
        return *this;
    }

    CDataStream<T> &operator <<(c_uint8 value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint8));
        return *this;
    }

    CDataStream<T> &operator <<(c_uint16 value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint16));
        return *this;
    }

    CDataStream<T> &operator <<(c_uint32 value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint32));
        return *this;
    }

    CDataStream<T> &operator <<(c_uint64 value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_uint64));
        return *this;
    }

    CDataStream<T> &operator <<(c_ulong value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(c_ulong));
        return *this;
    }

    CDataStream<T> &operator <<(bool value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(bool));
        return *this;
    }

    CDataStream<T> &operator <<(float value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(float));
        return *this;
    }

    CDataStream<T> &operator <<(double value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(double));
        return *this;
    }

    CDataStream<T> &operator <<(wchar_t value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(wchar_t));
        return *this;
    }

    CDataStream<T> &operator <<(char16_t value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(char16_t));
        return *this;
    }

    CDataStream<T> &operator <<(char32_t value)
    {
        m_writeFunction(m_data, reinterpret_cast<const char *>(&value), m_pos, sizeof(char32_t));
        return *this;
    }

    CDataStream<T> &operator <<(const std::string &value)
    {
        c_uint64 size = value.size();

        if (size == 0)
            return *this;

        m_writeFunction(m_data, reinterpret_cast<const char *>(&size), m_pos, sizeof(c_uint64));
        m_writeFunction(m_data, value.c_str(), m_pos, size);

        return *this;
    }

    CDataStream<T> &operator <<(const std::wstring &value)
    {
        c_uint64 size = value.size();

        if (size == 0)
            return *this;

        m_writeFunction(m_data, reinterpret_cast<const char *>(&size), m_pos, sizeof(c_uint64));
        m_writeFunction(m_data, value.c_str(), m_pos, size);

        return *this;
    }

    CDataStream<T> &operator <<(const std::u16string &value)
    {
        c_uint64 size = value.size();

        if (size == 0)
            return *this;

        m_writeFunction(m_data, reinterpret_cast<const char *>(&size), m_pos, sizeof(c_uint64));
        m_writeFunction(m_data, value.c_str(), m_pos, size);

        return *this;
    }

    CDataStream<T> &operator <<(const std::u32string &value)
    {
        c_uint64 size = value.size();

        if (size == 0)
            return *this;

        m_writeFunction(m_data, reinterpret_cast<const char *>(&size), m_pos, sizeof(c_uint64));
        m_writeFunction(m_data, value.c_str(), m_pos, size);

        return *this;
    }

    CDataStream<T> &operator <<(const char *value)
    {
        c_uint64 size = std::char_traits<char>::length(value);

        if (size == 0)
            return *this;

        m_writeFunction(m_data, reinterpret_cast<const char *>(&size), m_pos, sizeof(c_uint64));
        m_writeFunction(m_data, value, m_pos, size);

        return *this;
    }

    CDataStream<T> &operator <<(const wchar_t *value)
    {
        c_uint64 size = std::char_traits<wchar_t>::length(value);

        if (size == 0)
            return *this;

        m_writeFunction(m_data, reinterpret_cast<const char *>(&size), m_pos, sizeof(c_uint64));
        m_writeFunction(m_data, value, m_pos, size);

        return *this;
    }

    CDataStream<T> &operator <<(const char16_t *value)
    {
        c_uint64 size = std::char_traits<char16_t>::length(value);

        if (size == 0)
            return *this;

        m_writeFunction(m_data, reinterpret_cast<const char *>(&size), m_pos, sizeof(c_uint64));
        m_writeFunction(m_data, value, m_pos, size);

        return *this;
    }

    CDataStream<T> &operator <<(const char32_t *value)
    {
        c_uint64 size = std::char_traits<char32_t>::length(value);

        if (size == 0)
            return *this;

        m_writeFunction(m_data, reinterpret_cast<const char *>(&size), m_pos, sizeof(c_uint64));
        m_writeFunction(m_data, value, m_pos, size);

        return *this;
    }

    /*! Read */
    CDataStream<T> &operator >>(c_int8 &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int8));
        return *this;
    }

    CDataStream<T> &operator >>(c_int16 &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int16));
        return *this;
    }

    CDataStream<T> &operator >>(c_int32 &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int32));
        return *this;
    }

    CDataStream<T> &operator >>(c_int64 &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_int64));
        return *this;
    }

    CDataStream<T> &operator >>(c_long &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_long));
        return *this;
    }

    CDataStream<T> &operator >>(c_uint8 &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint8));
        return *this;
    }

    CDataStream<T> &operator >>(c_uint16 &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint16));
        return *this;
    }

    CDataStream<T> &operator >>(c_uint32 &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint32));
        return *this;
    }

    CDataStream<T> &operator >>(c_uint64 &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_uint64));
        return *this;
    }

    CDataStream<T> &operator >>(c_ulong &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(c_ulong));
        return *this;
    }

    CDataStream<T> &operator >>(bool &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(bool));
        return *this;
    }

    CDataStream<T> &operator >>(float &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(float));
        return *this;
    }

    CDataStream<T> &operator >>(double &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(double));
        return *this;
    }

    CDataStream<T> &operator >>(wchar_t &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(wchar_t));
        return *this;
    }

    CDataStream<T> &operator >>(char16_t &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(char16_t));
        return *this;
    }

    CDataStream<T> &operator >>(char32_t &value)
    {
        m_readFunction(m_data, reinterpret_cast<char *>(&value), m_pos, sizeof(char32_t));
        return *this;
    }

    CDataStream<T> &operator >>(std::string &value)
    {
        c_uint64 size = 0;
        m_readFunction(m_data, reinterpret_cast<char *>(&size), m_pos, sizeof(c_uint64));

        if (size == 0)
            return *this;

        char *data = new char[size];
        m_readFunction(m_data, data, m_pos, size);

        value.reserve(size);
        value.assign(data, size);

        delete[] data;

        return *this;
    }

    CDataStream<T> &operator >>(std::wstring &value)
    {
        c_uint64 size = 0;
        m_readFunction(m_data, reinterpret_cast<char *>(&size), m_pos, sizeof(c_uint64));

        if (size == 0)
            return *this;

        char *data = new char[size];
        m_readFunction(m_data, data, m_pos, size);

        value.reserve(size);
        value.assign(data, size);

        delete[] data;

        return *this;
    }

    CDataStream<T> &operator >>(std::u16string &value)
    {
        c_uint64 size = 0;
        m_readFunction(m_data, reinterpret_cast<char *>(&size), m_pos, sizeof(c_uint64));

        if (size == 0)
            return *this;

        char *data = new char[size];
        m_readFunction(m_data, data, m_pos, size);

        value.reserve(size);
        value.assign(data, size);

        delete[] data;

        return *this;
    }

    CDataStream<T> &operator >>(std::u32string &value)
    {
        c_uint64 size = 0;
        m_readFunction(m_data, reinterpret_cast<char *>(&size), m_pos, sizeof(c_uint64));

        if (size == 0)
            return *this;

        char *data = new char[size];
        m_readFunction(m_data, data, m_pos, size);

        value.reserve(size);
        value.assign(data, size);

        delete[] data;

        return *this;
    }

    CDataStream<T> &operator >>(char *value)
    {
        c_uint64 size = 0;
        m_readFunction(m_data, reinterpret_cast<char *>(&size), m_pos, sizeof(c_uint64));

        if (size == 0)
            return *this;

        m_readFunction(m_data, value, m_pos, size);

        return *this;
    }

    CDataStream<T> &operator >>(wchar_t *value)
    {
        c_uint64 size = 0;
        m_readFunction(m_data, reinterpret_cast<char *>(&size), m_pos, sizeof(c_uint64));

        if (size == 0)
            return *this;

        m_readFunction(m_data, value, m_pos, size);

        return *this;
    }

    CDataStream<T> &operator >>(char16_t *value)
    {
        c_uint64 size = 0;
        m_readFunction(m_data, reinterpret_cast<char *>(&size), m_pos, sizeof(c_uint64));

        if (size == 0)
            return *this;

        m_readFunction(m_data, value, m_pos, size);

        return *this;
    }

    CDataStream<T> &operator >>(char32_t *value)
    {
        c_uint64 size = 0;
        m_readFunction(m_data, reinterpret_cast<char *>(&size), m_pos, sizeof(c_uint64));

        if (size == 0)
            return *this;

        m_readFunction(m_data, value, m_pos, size);

        return *this;
    }

private:
    C_DISABLE_COPY(CDataStream)

    T &m_data;

    size_t m_pos;

    std::function<void (T &source, char *dest, size_t &pos, size_t len)> m_readFunction;
    std::function<void (T &dest, const char *source, size_t &pos, size_t len)> m_writeFunction;
};

template<class T, typename D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::vector<D> &vec)
{
    c_uint64 size = vec.size();

    stream << size;

    auto it = vec.cbegin();
    auto end = vec.cend();

    while (it != end) {
        stream << (*it);
        ++it;
    }

    return stream;
}

template<class T, typename D>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::vector<D> &vec)
{
    c_uint64 size = 0;

    stream >> size;

    if (size == 0)
        return stream;

    vec.reserve(size);

    c_uint64 ix = 0;
    while (ix < size) {
        D value;
        stream >> value;
        vec.push_back(value);

        ++ix;
    }

    return stream;
}

template<class T, typename D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::list<D> &list)
{
    c_uint64 size = list.size();

    stream << size;

    auto it = list.cbegin();
    auto end = list.cend();

    while (it != end) {
        stream << (*it);
        ++it;
    }

    return stream;
}

template<class T, typename D>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::list<D> &list)
{
    c_uint64 size = 0;

    stream >> size;

    if (size == 0)
        return stream;

    c_uint64 ix = 0;
    while (ix < size) {
        D value;
        stream >> value;
        list.push_back(value);

        ++ix;
    }

    return stream;
}

template<class T, typename D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::set<D> &set)
{
    c_uint64 size = set.size();

    stream << size;

    auto it = set.cbegin();
    auto end = set.cend();

    while (it != end) {
        stream << (*it);
        ++it;
    }

    return stream;
}

template<class T, typename D>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::set<D> &set)
{
    c_uint64 size = 0;

    stream >> size;

    if (size == 0)
        return stream;

    c_uint64 ix = 0;
    while (ix < size) {
        D value;
        stream >> value;
        set.insert(value);

        ++ix;
    }

    return stream;
}

template<class T, typename D, typename C>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::map<D, C> &map)
{
    c_uint64 size = map.size();

    stream << size;

    auto it = map.cbegin();
    auto end = map.cend();

    while (it != end) {
        stream << (*it).first;
        stream << (*it).second;
        ++it;
    }

    return stream;
}

template<class T, typename D, typename C>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::map<D, C> &map)
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

        map[key] = value;

        ++ix;
    }

    return stream;
}


template<class T, typename D, typename C>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::unordered_map<D, C> &unordered_map)
{
    c_uint64 size = unordered_map.size();

    stream << size;

    auto it = unordered_map.cbegin();
    auto end = unordered_map.cend();

    while (it != end) {
        stream << (*it).first;
        stream << (*it).second;
        ++it;
    }

    return stream;
}

template<class T, typename D, typename C>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::unordered_map<D, C> &unordered_map)
{
    c_uint64 size = 0;

    stream >> size;

    if (size == 0)
        return stream;

    unordered_map.reserve(size);

    c_uint64 ix = 0;
    while (ix < size) {
        D key;
        C value;
        stream >> key;
        stream >> value;

        unordered_map[key] = value;

        ++ix;
    }

    return stream;
}

template<class T, typename D>
inline CDataStream<T> &operator <<(CDataStream<T> &stream, const std::unordered_set<D> &unordered_set)
{
    c_uint64 size = unordered_set.size();

    stream << size;

    auto it = unordered_set.cbegin();
    auto end = unordered_set.cend();

    while (it != end) {
        stream << (*it);
        ++it;
    }

    return stream;
}

template<class T, typename D>
inline CDataStream<T> &operator >>(CDataStream<T> &stream, std::unordered_set<D> &unordered_set)
{
    c_uint64 size = 0;

    stream >> size;

    if (size == 0)
        return stream;

    unordered_set.reserve(size);

    c_uint64 ix = 0;
    while (ix < size) {
        D value;
        stream >> value;
        unordered_set.insert(value);

        ++ix;
    }

    return stream;
}

#define c_string_read_function              std::bind([](std::string &source, char *dest, size_t &pos, size_t len) -> void {\
    pos += source.copy(dest, len, pos);\
    }, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define c_string_write_function             std::bind([](std::string &dest, const char *source, size_t &pos, size_t len) -> void {\
    size_t length = dest.length();\
    dest.insert(pos, source, len);\
    pos += dest.length() - length;\
    }, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define c_wstring_read_function             std::bind([](std::wstring &source, char *dest, size_t &pos, size_t len) -> void {\
    pos += source.copy(dest, len, pos);\
    }, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define c_wstring_write_function            std::bind([](std::wstring &dest, const char *source, size_t &pos, size_t len) -> void {\
    size_t length = dest.length();\
    dest.insert(pos, source, len);\
    pos += dest.length() - length;\
    }, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define c_u16string_read_function           std::bind([](std::u16string &source, char *dest, size_t &pos, size_t len) -> void {\
    pos += source.copy(dest, len, pos);\
    }, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define c_u16string_write_function          std::bind([](std::u16string &dest, const char *source, size_t &pos, size_t len) -> void {\
    size_t length = dest.length();\
    dest.insert(pos, source, len);\
    pos += dest.length() - length;\
    }, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define c_u32string_read_function           std::bind([](std::u32string &source, char *dest, size_t &pos, size_t len) -> void {\
    pos += source.copy(dest, len, pos);\
    }, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define c_u32string_write_function          std::bind([](std::u32string &dest, const char *source, size_t &pos, size_t len) -> void {\
    size_t length = dest.length();\
    dest.insert(pos, source, len);\
    pos += dest.length() - length;\
    }, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define c_socket_read_function              std::bind([](CTcpSocket &source, char *dest, size_t &pos, size_t len) -> void {\
    C_UNUSED(pos);\
    source.read(dest, len);\
    }, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define c_socket_write_function             std::bind([](CTcpSocket &dest, const char *source, size_t &pos, size_t len) -> void {\
    C_UNUSED(pos);\
    dest.write(source, len);\
    }, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#endif // DATASTREAM_H

