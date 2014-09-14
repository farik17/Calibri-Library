//! Self Includes
#include "buffer.h"

namespace Calibri {

namespace Constants {

namespace Hex {

constexpr std::array<char, 16> alphabet {
    {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'a', 'b',
        'c', 'd', 'e', 'f'
    }
};

} // namespace Hex

namespace Base64 {

constexpr std::array<char, 64> alphabet {
    {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
    }
};

} // namespace Base64

} // namespace Constants

auto Buffer::toHex(bool *ok) const noexcept -> Buffer
{
    try {
        Buffer encodedData {};
        encodedData.reserve(size() * 2);

        for (auto it = std::begin(*this), end = std::end(*this); it != end; ++it) {
            encodedData.push_back(Constants::Hex::alphabet[*it >> 4 & 0x0f]);
            encodedData.push_back(Constants::Hex::alphabet[*it & 0x0f]);
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

auto Buffer::toBase64(bool *ok) const noexcept -> Buffer
{
    try {
        auto moduloSize = size() % 3;
        auto paddingSize = 3 - moduloSize;

        Buffer encodedData {};
        encodedData.reserve((size() / 3 + (paddingSize != 0
                ? 1
                : 0)) * 4);

        std::array<char, 3> block;

        auto it = std::begin(*this);
        auto end = std::prev(std::end(*this), moduloSize);

        while (it != end) {
            block[0] = *it;
            block[1] = *++it;
            block[2] = *++it;

            ++it;

            encodedData.push_back(Constants::Base64::alphabet[(block[0] & 0xfc) >> 2]);
            encodedData.push_back(Constants::Base64::alphabet[((block[0] & 0x03) << 4) + ((block[1] & 0xf0) >> 4)]);
            encodedData.push_back(Constants::Base64::alphabet[((block[1] & 0x0f) << 2) + ((block[2] & 0xc0) >> 6)]);
            encodedData.push_back(Constants::Base64::alphabet[(block[2] & 0x3f)]);
        }

        switch (paddingSize) {
        case 1:
            block[0] = *it;
            block[1] = *++it;
            block[2] = *++it;

            encodedData.push_back(Constants::Base64::alphabet[(block[0] & 0xfc) >> 2]);
            encodedData.push_back(Constants::Base64::alphabet[((block[0] & 0x03) << 4) + ((block[1] & 0xf0) >> 4)]);
            encodedData.push_back(Constants::Base64::alphabet[((block[1] & 0x0f) << 2) + ((block[2] & 0xc0) >> 6)]);
            encodedData.push_back('=');

            break;

        case 2:
            block[0] = *it;
            block[1] = *++it;

            encodedData.push_back(Constants::Base64::alphabet[(block[0] & 0xfc) >> 2]);
            encodedData.push_back(Constants::Base64::alphabet[((block[0] & 0x03) << 4) + ((block[1] & 0xf0) >> 4)]);
            encodedData.push_back('=');
            encodedData.push_back('=');

            break;

        default:
            break;
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

auto Buffer::fromBase64(const Buffer &buffer, bool *ok) noexcept -> Buffer
{
    try {
        if (buffer.size() % 4 != 0) {
            if (ok)
                *ok = false;

            return {};
        }

        auto paddingSize = *buffer.rbegin() == '='
                ? (*std::next(buffer.rbegin()) == '='
                   ? 2
                   : 1)
                : 0;

        Buffer decodedData {};
        decodedData.reserve((buffer.size() / 4) * 3 - paddingSize);

        std::array<char, 4> block;

        auto it = std::begin(buffer);
        auto end = paddingSize != 0
                ? std::prev(std::end(buffer), 4)
                : std::end(buffer);

        while (it != end) {
            for (auto i = 0; i < 4; ++i, ++it) {
                if (std::isupper(*it)) {
                    block[i] = *it - 'A';
                } else if (std::islower(*it)) {
                    block[i] = *it - 'a' + 26;
                } else if (std::isdigit(*it)) {
                    block[i] = *it - '0' + 52;
                } else if (*it == '+') {
                    block[i] = 62;
                } else if (*it == '/') {
                    block[i] = 63;
                } else {
                    if (ok)
                        *ok = false;

                    return {};
                }
            }

            decodedData.push_back((block[0] << 2) + ((block[1] & 0x30) >> 4));
            decodedData.push_back(((block[1] & 0xf) << 4) + ((block[2] & 0x3c) >> 2));
            decodedData.push_back(((block[2] & 0x3) << 6) + block[3]);
        }

        switch (paddingSize) {
        case 1:
            for (auto i = 0; i < 3; ++i, ++it) {
                if (std::isupper(*it)) {
                    block[i] = *it - 'A';
                } else if (std::islower(*it)) {
                    block[i] = *it - 'a' + 26;
                } else if (std::isdigit(*it)) {
                    block[i] = *it - '0' + 52;
                } else if (*it == '+') {
                    block[i] = 62;
                } else if (*it == '/') {
                    block[i] = 63;
                } else {
                    if (ok)
                        *ok = false;

                    return {};
                }
            }

            decodedData.push_back((block[0] << 2) + ((block[1] & 0x30) >> 4));
            decodedData.push_back(((block[1] & 0xf) << 4) + ((block[2] & 0x3c) >> 2));

            break;

        case 2:
            for (auto i = 0; i < 2; ++i, ++it) {
                if (std::isupper(*it)) {
                    block[i] = *it - 'A';
                } else if (std::islower(*it)) {
                    block[i] = *it - 'a' + 26;
                } else if (std::isdigit(*it)) {
                    block[i] = *it - '0' + 52;
                } else if (*it == '+') {
                    block[i] = 62;
                } else if (*it == '/') {
                    block[i] = 63;
                } else {
                    if (ok)
                        *ok = false;

                    return {};
                }
            }

            decodedData.push_back((block[0] << 2) + ((block[1] & 0x30) >> 4));

            break;

        default:
            break;
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
