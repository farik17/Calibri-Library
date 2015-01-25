#ifndef SPLIT_H
#define SPLIT_H

//! Std includes
#include <deque>
#include <forward_list>
#include <list>

//! Calibri-Library includes
#include "tools/bytearray.h"

namespace Calibri {

template<typename ContainerType,
         typename DataType = typename ContainerType::value_type,
         typename PredicateType,
         typename std::enable_if<((std::is_same<ContainerType, std::vector<DataType>>::value
                                 || std::is_same<ContainerType, std::deque<DataType>>::value
                                 || std::is_same<ContainerType, std::list<DataType>>::value)
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)
                                 && std::is_same<typename std::result_of<PredicateType(typename DataType::value_type)>::type, bool>::value)>::type ...Enabler>
inline auto split(ContainerType &container, const DataType &data, PredicateType predicate) noexcept -> bool
{
    try {
        container.clear();

        auto from = std::find_if_not(std::begin(data), std::end(data), predicate);
        auto to = std::find_if(from, std::end(data), predicate);

        if (to == std::end(data)) {
            container.emplace_back(data);

            return true;
        }

        DataType chunk;
        chunk.reserve(std::distance(from, to));

        std::copy(from, to, std::back_inserter(chunk));

        container.emplace_back(std::move(chunk));

        do {
            from = std::find_if_not(to, std::end(data), predicate);

            if (from == std::end(data))
                break;

            to = std::find_if(from, std::end(data), predicate);

            chunk.reserve(std::distance(from ,to));

            std::copy(from, to, std::back_inserter(chunk));

            container.emplace_back(std::move(chunk));

            if (to == std::end(data))
                break;
        } while (true);

        return true;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        container.clear();

        return false;
    }
}

template<typename ContainerType,
         typename DataType = typename ContainerType::value_type,
         typename PredicateType,
         typename std::enable_if<(std::is_same<ContainerType, std::forward_list<DataType>>::value
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)
                                 && std::is_same<typename std::result_of<PredicateType(typename DataType::value_type)>::type, bool>::value)>::type ...Enabler>
inline auto split(ContainerType &container, const DataType &data, PredicateType predicate) noexcept -> bool
{
    try {
        container.clear();

        auto from = std::find_if_not(std::begin(data), std::end(data), predicate);
        auto to = std::find_if(from, std::end(data), predicate);

        if (to == std::end(data)) {
            container.emplace_after(container.cbefore_begin(), data);

            return true;
        }

        DataType chunk;
        chunk.reserve(std::distance(from, to));

        std::copy(from, to, std::back_inserter(chunk));

        auto it = container.emplace_after(container.cbefore_begin(), std::move(chunk));

        do {
            from = std::find_if_not(to, std::end(data), predicate);

            if (from == std::end(data))
                break;

            to = std::find_if(from, std::end(data), predicate);

            chunk.reserve(std::distance(from ,to));

            std::copy(from, to, std::back_inserter(chunk));

            it = container.emplace_after(it, std::move(chunk));

            if (to == std::end(data))
                break;
        } while (true);

        return true;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        container.clear();

        return false;
    }
}

template<typename ContainerType,
         typename DataType = typename ContainerType::value_type,
         typename SeparatorType = typename DataType::value_type,
         typename std::enable_if<((std::is_same<ContainerType, std::vector<DataType>>::value
                                 || std::is_same<ContainerType, std::deque<DataType>>::value
                                 || std::is_same<ContainerType, std::forward_list<DataType>>::value
                                 || std::is_same<ContainerType, std::list<DataType>>::value)
                                 && (std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)
                                 && std::is_same<SeparatorType, typename DataType::value_type>::value)>::type ...Enabler>
inline auto split(ContainerType &container, const DataType &data, SeparatorType separator) noexcept -> bool
{
    return split(container, data, [ separator ](decltype(separator) symbol) noexcept {
        return symbol == separator;
    });
}

template<typename ContainerType,
         typename DataType,
         typename std::enable_if<((std::is_same<ContainerType, std::vector<typename std::decay<DataType>::type>>::value
                                 || std::is_same<ContainerType, std::deque<typename std::decay<DataType>::type>>::value
                                 || std::is_same<ContainerType, std::list<typename std::decay<DataType>::type>>::value)
                                 && (std::is_same<typename std::decay<DataType>::type, std::string>::value
                                 || std::is_same<typename std::decay<DataType>::type, std::wstring>::value
                                 || std::is_same<typename std::decay<DataType>::type, ByteArray>::value))>::type ...Enabler>
inline auto split(ContainerType &container, const DataType &data, DataType &&separator) noexcept -> bool
{
    try {
        container.clear();

        auto from = std::begin(data);
        auto to = std::search(from, std::end(data), std::begin(separator), std::end(separator));

        if (to == std::end(data)) {
            container.emplace_back(data);

            return true;
        }

        sizeinfo size = std::distance(from, to);

        DataType chunk;

        if (size != 0) {
            chunk.reserve(size);

            std::copy(from, to, std::back_inserter(chunk));

            container.emplace_back(std::move(chunk));
        }

        do {
            from = std::next(to, separator.size());

            if (from == std::end(data))
                break;

            to = std::search(from, std::end(data), std::begin(separator), std::end(separator));

            size = std::distance(from ,to);

            if (size != 0) {
                chunk.reserve(size);

                std::copy(from, to, std::back_inserter(chunk));

                container.emplace_back(std::move(chunk));
            }

            if (to == std::end(data))
                break;
        } while (true);

        return true;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        container.clear();

        return false;
    }
}

template<typename ContainerType,
         typename DataType,
         typename std::enable_if<(std::is_same<ContainerType, std::forward_list<typename std::decay<DataType>::type>>::value
                                 && (std::is_same<typename std::decay<DataType>::type, std::string>::value
                                 || std::is_same<typename std::decay<DataType>::type, std::wstring>::value
                                 || std::is_same<typename std::decay<DataType>::type, ByteArray>::value))>::type ...Enabler>
inline auto split(ContainerType &container, const DataType &data, DataType &&separator) noexcept -> bool
{
    try {
        container.clear();

        auto from = std::begin(data);
        auto to = std::search(from, std::end(data), std::begin(separator), std::end(separator));

        if (to == std::end(data)) {
            container.emplace_after(container.cbefore_begin(), data);

            return true;
        }

        sizeinfo size = std::distance(from, to);

        DataType chunk;

        auto it = container.cbefore_begin();

        if (size != 0) {
            chunk.reserve(size);

            std::copy(from, to, std::back_inserter(chunk));

            it = container.emplace_after(it, std::move(chunk));
        }

        do {
            from = std::next(to, separator.size());

            if (from == std::end(data))
                break;

            to = std::search(from, std::end(data), std::begin(separator), std::end(separator));

            size = std::distance(from ,to);

            if (size != 0) {
                chunk.reserve(size);

                std::copy(from, to, std::back_inserter(chunk));

                it = container.emplace_after(it, std::move(chunk));
            }

            if (to == std::end(data))
                break;
        } while (true);

        return true;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        container.clear();

        return false;
    }
}

} // end namespace Calibri

#endif // SPLIT_H
