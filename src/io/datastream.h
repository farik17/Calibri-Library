#ifndef DATASTREAM_H
#define DATASTREAM_H

//! Std Includes
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>

//! Project Includes
#include "global.h"

#if defined(CC_MSVC)
#   pragma warning(disable:4996)
#endif

namespace Calibri {

enum class DataStreamStatus : uint8 {
    Ok = 0,
    ReadError,
    WriteError
};

template<typename DeviceType>
class DataStream
{
public:
    explicit DataStream(DeviceType &device) DECL_NOEXCEPT
        : m_device(device)
        , m_pos(0)
        , m_status(DataStreamStatus::Ok)
    {
    }

    DeviceType &device() DECL_NOEXCEPT
    {
        return m_device;
    }

    size_t pos() const DECL_NOEXCEPT
    {
        return m_pos;
    }

    void seek(const size_t pos) DECL_NOEXCEPT
    {
        m_pos = pos;
    }

    DataStreamStatus status() const DECL_NOEXCEPT
    {
        return m_status;
    }

    void setStatus(DataStreamStatus status) DECL_NOEXCEPT
    {
        m_status = status;
    }

    void resetStatus() DECL_NOEXCEPT
    {
        m_status = DataStreamStatus::Ok;
    }

private:
    DISABLE_COPY(DataStream)

    DeviceType &m_device;

    size_t m_pos;

    DataStreamStatus m_status;
};

/*!
 * DataStream write function
 */
inline size_t dataStreamWrite(DataStream<std::string> &dataStream, const char *data, size_t size)
{
    try {
        dataStream.device().replace(dataStream.pos(), size, data, size);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        return 0;
    }

    dataStream.seek(dataStream.pos() + size);

    return size;
}

/*!
 * DataStream read function
 */
inline size_t dataStreamRead(DataStream<std::string> &dataStream, char *data, size_t size)
{
    size_t bytes = 0;

    try {
        bytes = dataStream.device().copy(data, size, dataStream.pos());
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        return 0;
    }

    dataStream.seek(dataStream.pos() + bytes);

    return bytes;
}

/*!
 * DataStream write operators
 */
template<typename DeviceType, typename ValueType>
inline typename std::enable_if<std::is_arithmetic<ValueType>::value, DataStream<DeviceType> >::type &operator <<(DataStream<DeviceType> &dataStream, ValueType value)
{
    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStreamWrite(dataStream, reinterpret_cast<const char *>(&value), sizeof(ValueType)) != sizeof(ValueType))
        dataStream.setStatus(DataStreamStatus::WriteError);

    return dataStream;
}

template<typename DeviceType>
inline DataStream<DeviceType> &operator <<(DataStream<DeviceType> &dataStream, const char *value)
{
    size_t size = std::char_traits<char>::length(value);

    dataStream << static_cast<uint32>(size);

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStreamWrite(dataStream, value, size) != size)
        dataStream.setStatus(DataStreamStatus::WriteError);

    return dataStream;
}

template<typename DeviceType>
inline DataStream<DeviceType> &operator <<(DataStream<DeviceType> &dataStream, const std::string &value)
{
    dataStream << static_cast<uint32>(value.size());

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStreamWrite(dataStream, value.c_str(), value.size()) != value.size())
        dataStream.setStatus(DataStreamStatus::WriteError);

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline DataStream<DeviceType> &operator <<(DataStream<DeviceType> &dataStream, const std::vector<ValueType> &data)
{
    dataStream << static_cast<uint32>(data.size());

    for (auto dataIt = data.cbegin(), dataEnd = data.cend(); dataIt != dataEnd; ++dataIt)
        dataStream << (*dataIt);

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline DataStream<DeviceType> &operator <<(DataStream<DeviceType> &dataStream, const std::list<ValueType> &data)
{
    dataStream << static_cast<uint32>(data.size());

    for (auto dataIt = data.cbegin(), dataEnd = data.cend(); dataIt != dataEnd; ++dataIt)
        dataStream << (*dataIt);

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline DataStream<DeviceType> &operator <<(DataStream<DeviceType> &dataStream, const std::forward_list<ValueType> &data)
{
    dataStream << static_cast<uint32>(std::distance(data.cbegin(), data.cend()));

    for (auto dataIt = data.cbegin(), dataEnd = data.cend(); dataIt != dataEnd; ++dataIt)
        dataStream << (*dataIt);

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline DataStream<DeviceType> &operator <<(DataStream<DeviceType> &dataStream, const std::set<ValueType> &data)
{
    dataStream << static_cast<uint32>(data.size());

    for (auto dataIt = data.cbegin(), dataEnd = data.cend(); dataIt != dataEnd; ++dataIt)
        dataStream << (*dataIt);

    return dataStream;
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline DataStream<DeviceType> &operator <<(DataStream<DeviceType> &dataStream, const std::map<KeyType, ValueType> &data)
{
    dataStream << static_cast<uint32>(data.size());

    for (auto dataIt = data.cbegin(), dataEnd = data.cend(); dataIt != dataEnd; ++dataIt) {
        dataStream << (*dataIt).first;
        dataStream << (*dataIt).second;
    }

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline DataStream<DeviceType> &operator <<(DataStream<DeviceType> &dataStream, const std::unordered_set<ValueType> &data)
{
    dataStream << static_cast<uint32>(data.size());

    for (auto dataIt = data.cbegin(), dataEnd = data.cend(); dataIt != dataEnd; ++dataIt)
        dataStream << (*dataIt);

    return dataStream;
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline DataStream<DeviceType> &operator <<(DataStream<DeviceType> &dataStream, const std::unordered_map<KeyType, ValueType> &data)
{
    dataStream << static_cast<uint32>(data.size());

    for (auto dataIt = data.cbegin(), dataEnd = data.cend(); dataIt != dataEnd; ++dataIt) {
        dataStream << (*dataIt).first;
        dataStream << (*dataIt).second;
    }

    return dataStream;
}

/*!
 * DataStream read operators
 */
template<typename DeviceType, typename ValueType>
inline typename std::enable_if<std::is_arithmetic<ValueType>::value, DataStream<DeviceType> >::type &operator >>(DataStream<DeviceType> &dataStream, ValueType &value)
{
    value = 0;

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStreamRead(dataStream, reinterpret_cast<char *>(&value), sizeof(ValueType)) != sizeof(ValueType)) {
        dataStream.setStatus(DataStreamStatus::ReadError);

        value = 0;
    }

    return dataStream;
}

template<typename DeviceType>
inline DataStream<DeviceType> &operator >>(DataStream<DeviceType> &dataStream, char *&value)
{
    value = nullptr;

    uint32 size = 0;
    dataStream >> size;

    if (size == 0)
        return dataStream;

    try {
        value = new char[static_cast<size_t>(size + 1)];
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        dataStream.setStatus(DataStreamStatus::ReadError);

        return dataStream;
    }

    if (dataStreamRead(dataStream, value, static_cast<size_t>(size)) != static_cast<size_t>(size)) {
        dataStream.setStatus(DataStreamStatus::ReadError);

        delete[] value;
        value = nullptr;
    }

    value[size] = '\0';

    return dataStream;
}

template<typename DeviceType>
inline DataStream<DeviceType> &operator >>(DataStream<DeviceType> &dataStream, std::string &value)
{
    value.clear();

    uint32 size = 0;
    dataStream >> size;

    if (size == 0)
        return dataStream;

    try {
        value.resize(static_cast<size_t>(size));
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        dataStream.setStatus(DataStreamStatus::ReadError);

        return dataStream;
    }

    if (dataStreamRead(dataStream, &value.front(), static_cast<size_t>(size)) != static_cast<size_t>(size)) {
        dataStream.setStatus(DataStreamStatus::ReadError);

        value.clear();
    }

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline DataStream<DeviceType> &operator >>(DataStream<DeviceType> &dataStream, std::vector<ValueType> &data)
{
    data.clear();

    uint32 size = 0;
    dataStream >> size;

    try {
        data.reserve(static_cast<size_t>(size));
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        dataStream.setStatus(DataStreamStatus::ReadError);

        return dataStream;
    }

    for (uint32 ix = 0; ix < size; ++ix) {
        ValueType value;
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        try {
            data.push_back(std::move(value));
        } catch (const std::exception &ex) {
            std::cerr << FUNC_INFO << ex.what();

            dataStream.setStatus(DataStreamStatus::ReadError);

            data.clear();

            break;
        }
    }

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline DataStream<DeviceType> &operator >>(DataStream<DeviceType> &dataStream, std::list<ValueType> &data)
{
    data.clear();

    uint32 size = 0;
    dataStream >> size;

    for (uint32 ix = 0; ix < size; ++ix) {
        ValueType value;
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        try {
            data.push_back(std::move(value));
        } catch (const std::exception &ex) {
            std::cerr << FUNC_INFO << ex.what();

            dataStream.setStatus(DataStreamStatus::ReadError);

            data.clear();

            break;
        }
    }

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline DataStream<DeviceType> &operator >>(DataStream<DeviceType> &dataStream, std::forward_list<ValueType> &data)
{
    data.clear();

    uint32 size = 0;
    dataStream >> size;

    auto it = data.before_begin();

    for (uint32 ix = 0; ix < size; ++ix) {
        ValueType value;
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        try {
            it = data.insert_after(it, std::move(value));
        } catch (const std::exception &ex) {
            std::cerr << FUNC_INFO << ex.what();

            dataStream.setStatus(DataStreamStatus::ReadError);

            data.clear();

            break;
        }
    }

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline DataStream<DeviceType> &operator >>(DataStream<DeviceType> &dataStream, std::set<ValueType> &data)
{
    data.clear();

    uint32 size = 0;
    dataStream >> size;

    for (uint32 ix = 0; ix < size; ++ix) {
        ValueType value;
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        try {
            data.insert(std::move(value));
        } catch (const std::exception &ex) {
            std::cerr << FUNC_INFO << ex.what();

            dataStream.setStatus(DataStreamStatus::ReadError);

            data.clear();

            break;
        }
    }

    return dataStream;
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline DataStream<DeviceType> &operator >>(DataStream<DeviceType> &dataStream, std::map<KeyType, ValueType> &data)
{
    data.clear();

    uint32 size = 0;
    dataStream >> size;

    for (uint32 ix = 0; ix < size; ++ix) {
        KeyType key;
        ValueType value;
        dataStream >> key;
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        try {
            data.insert(std::make_pair(std::move(key), std::move(value)));
        } catch (const std::exception &ex) {
            std::cerr << FUNC_INFO << ex.what();

            dataStream.setStatus(DataStreamStatus::ReadError);

            data.clear();

            break;
        }
    }

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline DataStream<DeviceType> &operator >>(DataStream<DeviceType> &dataStream, std::unordered_set<ValueType> &data)
{
    data.clear();

    uint32 size = 0;
    dataStream >> size;

    try {
        data.reserve(static_cast<size_t>(size));
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        dataStream.setStatus(DataStreamStatus::ReadError);

        return dataStream;
    }

    for (uint32 ix = 0; ix < size; ++ix) {
        ValueType value;
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        try {
            data.insert(std::move(value));
        } catch (const std::exception &ex) {
            std::cerr << FUNC_INFO << ex.what();

            dataStream.setStatus(DataStreamStatus::ReadError);

            data.clear();

            break;
        }
    }

    return dataStream;
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline DataStream<DeviceType> &operator >>(DataStream<DeviceType> &dataStream, std::unordered_map<KeyType, ValueType> &data)
{
    data.clear();

    uint32 size = 0;
    dataStream >> size;

    try {
        data.reserve(static_cast<size_t>(size));
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what();

        dataStream.setStatus(DataStreamStatus::ReadError);

        return dataStream;
    }

    for (uint32 ix = 0; ix < size; ++ix) {
        KeyType key;
        ValueType value;
        dataStream >> key;
        dataStream >> value;

        if (dataStream.status() != DataStreamStatus::Ok) {
            data.clear();

            break;
        }

        try {
            data.insert(std::make_pair(std::move(key), std::move(value)));
        } catch (const std::exception &ex) {
            std::cerr << FUNC_INFO << ex.what();

            dataStream.setStatus(DataStreamStatus::ReadError);

            data.clear();

            break;
        }
    }

    return dataStream;
}

}

#endif // DATASTREAM_H
