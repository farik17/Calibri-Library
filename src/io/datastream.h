#ifndef DATASTREAM_H
#define DATASTREAM_H

//! Std Includes
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

//! CalibriLibrary Includes
#include "disablecopy.h"
#include "meta_cast.h"

namespace Calibri {

enum class DataStreamStatus : uint8 {
    Ok = 0,
    ReadError,
    WriteError
};

template<typename DeviceType>
class DataStream : private DisableCopy
{
public:
    explicit DataStream(DeviceType *device) noexcept
        : m_device { device }
    {
    }

    auto device() noexcept -> DeviceType *
    {
        return m_device;
    }

    auto pos() const noexcept -> size_t
    {
        return m_pos;
    }

    void seek(size_t pos) noexcept
    {
        m_pos = pos;
    }

    auto status() const noexcept -> DataStreamStatus
    {
        return m_status;
    }

    void setStatus(DataStreamStatus status) noexcept
    {
        m_status = status;
    }

    void resetStatus() noexcept
    {
        m_status = DataStreamStatus::Ok;
    }

private:
    DeviceType *m_device {};

    size_t m_pos {};

    DataStreamStatus m_status { DataStreamStatus::Ok };
};

/*!
 * DataStream write function
 */
inline auto dataStreamWrite(DataStream<buffer> &dataStream, const char *data, size_t size) noexcept -> size_t
{
    try {
        auto overflow = 0;
        auto pos = dataStream.pos() + size;

        if (pos > dataStream.device()->size())
            overflow = pos - dataStream.device()->size();

        dataStream.device()->resize(dataStream.device()->size() + overflow);

        std::copy_n(data, size, std::next(dataStream.device()->begin(), dataStream.pos()));

        dataStream.seek(pos);

        return size;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        return 0;
    }
}

/*!
 * DataStream read function
 */
inline auto dataStreamRead(DataStream<buffer> &dataStream, char *data, size_t size) noexcept -> size_t
{
    try {
        auto overflow = 0;
        auto pos = dataStream.pos() + size;

        if (pos > dataStream.device()->size())
            overflow = pos - dataStream.device()->size();

        size -= overflow;
        pos -= overflow;

        std::copy_n(std::next(dataStream.device()->begin(), dataStream.pos()), size, data);

        dataStream.seek(pos);

        return size;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        return 0;
    }
}

/*!
 * DataStream write operators
 */
template<typename DeviceType, typename DataType, typename std::enable_if<std::is_arithmetic<DataType>::value, class Enabler>::type... Enabler>
inline auto operator <<(DataStream<DeviceType> &dataStream, DataType data) noexcept -> DataStream<DeviceType> &
{
    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStreamWrite(dataStream, reinterpret_cast<const char *>(&data), sizeof(DataType)) != sizeof(DataType))
        dataStream.setStatus(DataStreamStatus::WriteError);

    return dataStream;
}

template<typename DeviceType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const char *data) noexcept -> DataStream<DeviceType> &
{
    auto size = std::char_traits<char>::length(data);

    dataStream << meta_cast<uint32>(size);

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStreamWrite(dataStream, data, size) != size)
        dataStream.setStatus(DataStreamStatus::WriteError);

    return dataStream;
}

template<typename DeviceType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::string &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStreamWrite(dataStream, data.c_str(), data.size()) != data.size())
        dataStream.setStatus(DataStreamStatus::WriteError);

    return dataStream;
}

//! Sequence containers
template<typename DeviceType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::vector<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::deque<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::forward_list<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(std::distance(std::begin(data), std::end(data)));

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::list<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

//! Associative containers
template<typename DeviceType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::set<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::multiset<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::map<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &pair : data) {
        dataStream << pair.first;
        dataStream << pair.second;
    }

    return dataStream;
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::multimap<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &pair : data) {
        dataStream << pair.first;
        dataStream << pair.second;
    }

    return dataStream;
}

//! Unordered associative containers
template<typename DeviceType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::unordered_set<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::unordered_multiset<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &value : data)
        dataStream << value;

    return dataStream;
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::unordered_map<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &pair : data) {
        dataStream << pair.first;
        dataStream << pair.second;
    }

    return dataStream;
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline auto operator <<(DataStream<DeviceType> &dataStream, const std::unordered_multimap<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    dataStream << meta_cast<uint32>(data.size());

    for (const auto &pair : data) {
        dataStream << pair.first;
        dataStream << pair.second;
    }

    return dataStream;
}

/*!
 * DataStream read operators
 */
template<typename DeviceType, typename DataType, typename std::enable_if<std::is_arithmetic<DataType>::value, class Enabler>::type... Enabler>
inline auto operator >>(DataStream<DeviceType> &dataStream, DataType &data) noexcept -> DataStream<DeviceType> &
{
    data = 0;

    if (dataStream.status() != DataStreamStatus::Ok)
        return dataStream;

    if (dataStreamRead(dataStream, reinterpret_cast<char *>(&data), sizeof(DataType)) != sizeof(DataType)) {
        dataStream.setStatus(DataStreamStatus::ReadError);

        data = 0;
    }

    return dataStream;
}

template<typename DeviceType>
inline auto operator >>(DataStream<DeviceType> &dataStream, char *&data) noexcept -> DataStream<DeviceType> &
{
    try {
        data = nullptr;

        uint32 size {};
        dataStream >> size;

        if (dataStream.status() != DataStreamStatus::Ok)
            return dataStream;

        data = new char[meta_cast<size_t>(size + 1)] {};

        if (dataStreamRead(dataStream, data, meta_cast<size_t>(size)) != meta_cast<size_t>(size)) {
            dataStream.setStatus(DataStreamStatus::ReadError);

            delete[] data;
            data = nullptr;
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        return dataStream;
    }
}

template<typename DeviceType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::string &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        if (dataStream.status() != DataStreamStatus::Ok)
            return dataStream;

        data.resize(meta_cast<size_t>(size));

        if (dataStreamRead(dataStream, &data.front(), meta_cast<size_t>(size)) != meta_cast<size_t>(size)) {
            dataStream.setStatus(DataStreamStatus::ReadError);

            data.clear();
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        return dataStream;
    }
}

//! Sequence containers
template<typename DeviceType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::vector<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        data.reserve(meta_cast<size_t>(size));

        for (auto i = 0; i < size; ++i) {
            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.push_back(std::move(value));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

template<typename DeviceType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::deque<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        for (auto i = 0; i < size; ++i) {
            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.push_back(std::move(value));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

template<typename DeviceType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::forward_list<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        auto it = data.cbefore_begin();

        for (auto i = 0; i < size; ++i) {
            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            it = data.insert_after(it, std::move(value));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

template<typename DeviceType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::list<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        for (auto i = 0; i < size; ++i) {
            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.push_back(std::move(value));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

//! Associative containers
template<typename DeviceType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::set<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        for (auto i = 0; i < size; ++i) {
            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.insert(std::move(value));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

template<typename DeviceType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::multiset<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        for (auto i = 0; i < size; ++i) {
            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.insert(std::move(value));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::map<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        for (auto i = 0; i < size; ++i) {
            KeyType key {};
            dataStream >> key;

            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.insert(std::make_pair(std::move(key), std::move(value)));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::multimap<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        for (auto i = 0; i < size; ++i) {
            KeyType key {};
            dataStream >> key;

            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.insert(std::make_pair(std::move(key), std::move(value)));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

//! Unordered associative containers
template<typename DeviceType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::unordered_set<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        data.reserve(meta_cast<size_t>(size));

        for (auto i = 0; i < size; ++i) {
            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.insert(std::move(value));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

template<typename DeviceType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::unordered_multiset<ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        data.reserve(meta_cast<size_t>(size));

        for (auto i = 0; i < size; ++i) {
            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.insert(std::move(value));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::unordered_map<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        data.reserve(meta_cast<size_t>(size));

        for (auto i = 0; i < size; ++i) {
            KeyType key {};
            dataStream >> key;

            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.insert(std::make_pair(std::move(key), std::move(value)));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

template<typename DeviceType, typename KeyType, typename ValueType>
inline auto operator >>(DataStream<DeviceType> &dataStream, std::unordered_multimap<KeyType, ValueType> &data) noexcept -> DataStream<DeviceType> &
{
    try {
        data.clear();

        uint32 size {};
        dataStream >> size;

        data.reserve(meta_cast<size_t>(size));

        for (auto i = 0; i < size; ++i) {
            KeyType key {};
            dataStream >> key;

            ValueType value {};
            dataStream >> value;

            if (dataStream.status() != DataStreamStatus::Ok) {
                data.clear();

                break;
            }

            data.insert(std::make_pair(std::move(key), std::move(value)));
        }

        return dataStream;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << ex.what() << std::endl;

        dataStream.setStatus(DataStreamStatus::ReadError);

        data.clear();

        return dataStream;
    }
}

} // namespace Calibri

#endif // DATASTREAM_H
