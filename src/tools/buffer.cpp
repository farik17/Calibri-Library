//! Self Includes
#include "buffer.h"

namespace Calibri {

namespace Constants {

namespace Hex {

constexpr const std::array<char, 16> encodeTable {
    {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'a', 'b',
        'c', 'd', 'e', 'f'
    }
};

} // namespace Hex

} // namespace Constants

auto Buffer::toHex(bool *ok) const noexcept -> Buffer
{
    try {
        Buffer encodedData {};
        encodedData.reserve(size() * 2);

        for (auto it = std::begin(*this), end = std::end(*this); it != end; ++it) {
            encodedData.push_back(Constants::Hex::encodeTable[*it >> 4 & 0xf]);
            encodedData.push_back(Constants::Hex::encodeTable[*it & 0xf]);
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

            if (std::isdigit(*it)) {
                symbol = (*it - '0') << 4;
            } else if (std::islower(*it)) {
                symbol = (*it - 'a' + 10) << 4;
            } else if (std::isupper(*it)) {
                symbol = (*it - 'A' + 10) << 4;
            } else {
                if (ok)
                    *ok = false;

                return {};
            }

            ++it;

            if (std::isdigit(*it)) {
                symbol |= (*it - '0');
            } else if (std::islower(*it)) {
                symbol |= (*it - 'a' + 10);
            } else if (std::isupper(*it)) {
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
