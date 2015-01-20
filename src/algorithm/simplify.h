#ifndef SIMPLIFY_H
#define SIMPLIFY_H

//! Calibri-Library includes
#include "tools/bytearray.h"

namespace Calibri {

namespace Constants {

constexpr char whitespace { ' ' };

} // end namespace Constants

namespace Internal {

template<typename DataType,
         typename InputIteratorType = typename DataType::iterator,
         typename ValueType = typename DataType::value_type,
         typename std::enable_if<(std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value)>::type ...Enabler>
inline auto insert(DataType &data, InputIteratorType inputIterator, ValueType value) noexcept -> InputIteratorType
{
    try {
        return data.insert(inputIterator, value);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return std::end(data);
    }
}

template<typename DataType,
         typename InputIteratorType = typename DataType::iterator,
         typename ValueType = typename DataType::value_type,
         typename std::enable_if<std::is_same<DataType, ByteArray>::value>::type ...Enabler>
inline auto insert(DataType &data, InputIteratorType inputIterator, ValueType value) noexcept -> InputIteratorType
{
    try {
        return data.emplace(inputIterator, value);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return std::end(data);
    }
}

} // end namespace Internal

template<typename DataType,
         typename std::enable_if<(std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)>::type ...Enabler>
inline auto simplify(DataType &data) noexcept -> bool
{
    try {
        auto it = std::find_if_not(data.rbegin(), data.rend(), ::isspace).base();

        if (it == std::begin(data)) {
            data.clear();

            return true;
        }

        data.erase(it, std::end(data));

        it = std::find_if_not(std::begin(data), std::end(data), ::isspace);

        data.erase(std::begin(data), it);

        auto from = std::find_if(std::begin(data), std::end(data), ::isspace);

        if (from == std::end(data))
            return true;

        auto to = std::find_if_not(from, std::end(data), ::isspace);

        it = std::next(Internal::insert(data, data.erase(from, to), Constants::whitespace));

        do {
            from = std::find_if(it, std::end(data), ::isspace);

            if (from == std::end(data))
                break;

            to = std::find_if_not(from, std::end(data), ::isspace);

            it = std::next(Internal::insert(data, data.erase(from, to), Constants::whitespace));
        } while (true);

        return true;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        data.clear();

        return false;
    }
}

} // end namespace Calibri

#endif // SIMPLIFY_H
