#ifndef CALIBRI_ALGORITHMS_TRIM_HPP
#define CALIBRI_ALGORITHMS_TRIM_HPP

//! Calibri-Library includes
#include "tools/bytearray.hpp"

namespace Calibri {

namespace Algorithms {

template<typename DataType,
         typename std::enable_if<(std::is_same<DataType, std::string>::value
                                 || std::is_same<DataType, std::wstring>::value
                                 || std::is_same<DataType, ByteArray>::value)>::type ...Enabler>
inline auto trim(DataType &data) noexcept -> bool
{
    try {
        auto it = std::find_if_not(std::begin(data), std::end(data), ::isspace);

        if (it == std::end(data)) {
            data.clear();

            return true;
        }

        data.erase(std::begin(data), it);

        it = std::find_if_not(data.rbegin(), data.rend(), ::isspace).base();

        data.erase(it, std::end(data));

        return true;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        data.clear();

        return false;
    }
}

} // end namespace Algorithms

using Algorithms::trim;

} // end namespace Calibri

#endif // CALIBRI_ALGORITHMS_TRIM_HPP
