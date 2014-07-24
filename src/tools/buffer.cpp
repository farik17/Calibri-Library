//! Self Includes
#include "buffer.h"

//! Std Includes
#include <array>

//! Calibri-Library Includes
#include "global/global.h"

namespace Calibri {

namespace Constants {

constexpr const std::array<char, 16> hexAlphabet { { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' } };

} // namespace Constants

auto Buffer::toHex(bool *ok) const noexcept -> Buffer
{
    try {
        Buffer encodedData {};
        encodedData.reserve(size() * 2);

        for (auto it = std::begin(*this), end = std::end(*this); it != end; ++it) {
            encodedData.push_back(Constants::hexAlphabet[*it >> 4 & 0xF]);
            encodedData.push_back(Constants::hexAlphabet[*it & 0xF]);
        }

        if (ok)
            *ok = true;

        return encodedData;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

auto Buffer::fromHex(const Buffer &buffer, bool *ok) noexcept -> Buffer
{
    try {
        if (buffer.size() % 2 != 0) {
            if (ok)
                *ok = false;

            return {};
        }

        Buffer decodedData {};
        decodedData.reserve(buffer.size() / 2);

        for (auto it = std::begin(buffer), end = std::end(buffer); it != end; ++it) {
            char symbol {};

            if (*it >= '0' && *it <= '9') {
                symbol = (*it - '0') << 4;
            } else if (*it >= 'a' && *it <= 'f') {
                symbol = (*it - 'a' + 10) << 4;
            } else if (*it >= 'A' && *it <= 'F') {
                symbol = (*it - 'A' + 10) << 4;
            } else {
                if (ok)
                    *ok = false;

                return {};
            }

            ++it;

            if (*it >= '0' && *it <= '9') {
                symbol |= (*it - '0');
            } else if (*it >= 'a' && *it <= 'f') {
                symbol |= (*it - 'a' + 10);
            } else if (*it >= 'A' && *it <= 'F') {
                symbol |= (*it - 'A' + 10);
            } else {
                if (ok)
                    *ok = false;

                return {};
            }

            decodedData.push_back(symbol);
        }

        if (ok)
            *ok = true;

        return decodedData;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

} // namespace Calibri
