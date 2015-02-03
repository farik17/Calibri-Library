#ifndef CALIBRI_ALGORITHMS_SIMPLIFY_HPP
#define CALIBRI_ALGORITHMS_SIMPLIFY_HPP

//! Calibri-Library includes
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Constants {

constexpr char space { ' ' };

} // end namespace Constants

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

        it = std::next(data.insert(data.erase(from, to), Constants::space));

        do {
            from = std::find_if(it, std::end(data), ::isspace);

            if (from == std::end(data))
                break;

            to = std::find_if_not(from, std::end(data), ::isspace);

            it = std::next(data.insert(data.erase(from, to), Constants::space));
        } while (true);

        return true;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        data.clear();

        return false;
    }
}

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_SIMPLIFY_HPP
