//! Self includes
#include "bytearray.h"

//! Std includes
#include <array>

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

} // end namespace Hex

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

} // end namespace Base64

constexpr char whitespace { ' ' };

} // end namespace Constants

auto ByteArray::simplified(bool *ok) const & noexcept -> ByteArray
{
    try {
        auto from = std::find_if(std::begin(*this), std::end(*this), [](char symbol) noexcept {
            return !::isspace(symbol);
        });

        if (from == std::end(*this)) {
            if (ok)
                *ok = false;

            return {};
        }

        auto to = std::find_if(crbegin(), crend(), [](char symbol) noexcept {
            return !::isspace(symbol);
        }).base();

        auto spacesFrom = std::find_if(from, to, [](char symbol) noexcept {
            return ::isspace(symbol);
        });

        if (spacesFrom == to) {
            if (ok)
                *ok = true;

            return { from, to };
        }

        ByteArray simplifiedData {};
        simplifiedData.reserve(size());

        std::copy(from, spacesFrom, std::back_inserter(simplifiedData));

        simplifiedData.emplace_back(Constants::whitespace);

        auto spacesTo = std::find_if(spacesFrom, to, [](char symbol) noexcept {
            return !::isspace(symbol);
        });

        do {
            spacesFrom = std::find_if(spacesTo, to, [](char symbol) noexcept {
                return ::isspace(symbol);
            });

            if (spacesFrom == to) {
                std::copy(spacesTo, to, std::back_inserter(simplifiedData));

                break;
            }

            std::copy(spacesTo, spacesFrom, std::back_inserter(simplifiedData));

            spacesTo = std::find_if(spacesFrom, to, [](char symbol) noexcept {
                return !::isspace(symbol);
            });

            simplifiedData.emplace_back(Constants::whitespace);
        } while (true);

        if (ok)
            *ok = true;

        return simplifiedData;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

auto ByteArray::simplified(bool *ok) && noexcept -> ByteArray &&
{
    try {
        auto it = std::find_if(rbegin(), rend(), [](char symbol) noexcept {
            return !::isspace(symbol);
        }).base();

        if (it == std::begin(*this)) {
            if (ok)
                *ok = false;

            clear();

            return std::move(*this);
        }

        erase(it, std::end(*this));

        it = std::find_if(std::begin(*this), std::end(*this), [](char symbol) noexcept {
            return !::isspace(symbol);
        });

        erase(std::begin(*this), it);

        auto spacesFrom = std::find_if(std::begin(*this), std::end(*this), [](char symbol) noexcept {
            return ::isspace(symbol);
        });

        if (spacesFrom == std::end(*this)) {
            if (ok)
                *ok = true;

            return std::move(*this);
        }

        auto spacesTo = std::find_if(spacesFrom, std::end(*this), [](char symbol) noexcept {
            return !::isspace(symbol);
        });

        it = std::next(emplace(erase(spacesFrom, spacesTo), Constants::whitespace));

        do {
            spacesFrom = std::find_if(it, std::end(*this), [](char symbol) noexcept {
                return ::isspace(symbol);
            });

            if (spacesFrom == std::end(*this))
                break;

            spacesTo = std::find_if(spacesFrom, std::end(*this), [](char symbol) noexcept {
                return !::isspace(symbol);
            });

            it = std::next(emplace(erase(spacesFrom, spacesTo), Constants::whitespace));
        } while (true);

        if (ok)
            *ok = true;

        return std::move(*this);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        clear();

        return std::move(*this);
    }
}

auto ByteArray::toHex(bool *ok) const noexcept -> ByteArray
{
    try {
        ByteArray encodedData {};
        encodedData.reserve(size() * 2);

        for (auto it = std::begin(*this), end = std::end(*this); it != end; ++it) {
            encodedData.emplace_back(Constants::Hex::alphabet[*it >> 4 & 0x0f]);
            encodedData.emplace_back(Constants::Hex::alphabet[*it & 0x0f]);
        }

        if (ok)
            *ok = true;

        return encodedData;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

auto ByteArray::toBase64(bool *ok) const noexcept -> ByteArray
{
    try {
        auto moduloSize = size() % 3;
        auto paddingSize = 3 - moduloSize;

        ByteArray encodedData {};
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

            encodedData.emplace_back(Constants::Base64::alphabet[(block[0] & 0xfc) >> 2]);
            encodedData.emplace_back(Constants::Base64::alphabet[((block[0] & 0x03) << 4) + ((block[1] & 0xf0) >> 4)]);
            encodedData.emplace_back(Constants::Base64::alphabet[((block[1] & 0x0f) << 2) + ((block[2] & 0xc0) >> 6)]);
            encodedData.emplace_back(Constants::Base64::alphabet[(block[2] & 0x3f)]);
        }

        switch (paddingSize) {
        case 1:
            block[0] = *it;
            block[1] = *++it;
            block[2] = *++it;

            encodedData.emplace_back(Constants::Base64::alphabet[(block[0] & 0xfc) >> 2]);
            encodedData.emplace_back(Constants::Base64::alphabet[((block[0] & 0x03) << 4) + ((block[1] & 0xf0) >> 4)]);
            encodedData.emplace_back(Constants::Base64::alphabet[((block[1] & 0x0f) << 2) + ((block[2] & 0xc0) >> 6)]);
            encodedData.emplace_back('=');

            break;

        case 2:
            block[0] = *it;
            block[1] = *++it;

            encodedData.emplace_back(Constants::Base64::alphabet[(block[0] & 0xfc) >> 2]);
            encodedData.emplace_back(Constants::Base64::alphabet[((block[0] & 0x03) << 4) + ((block[1] & 0xf0) >> 4)]);
            encodedData.emplace_back('=');
            encodedData.emplace_back('=');

            break;

        default:
            break;
        }

        if (ok)
            *ok = true;

        return encodedData;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

auto ByteArray::fromHex(const ByteArray &data, bool *ok) noexcept -> ByteArray
{
    try {
        if (data.size() % 2 != 0) {
            if (ok)
                *ok = false;

            return {};
        }

        ByteArray decodedData {};
        decodedData.reserve(data.size() / 2);

        for (auto it = std::begin(data), end = std::end(data); it != end; ++it) {
            char symbol {};

            if (::isdigit(*it)) {
                symbol = (*it - '0') << 4;
            } else if (::islower(*it)) {
                symbol = (*it - 'a' + 10) << 4;
            } else if (::isupper(*it)) {
                symbol = (*it - 'A' + 10) << 4;
            } else {
                if (ok)
                    *ok = false;

                return {};
            }

            ++it;

            if (::isdigit(*it)) {
                symbol |= (*it - '0');
            } else if (::islower(*it)) {
                symbol |= (*it - 'a' + 10);
            } else if (::isupper(*it)) {
                symbol |= (*it - 'A' + 10);
            } else {
                if (ok)
                    *ok = false;

                return {};
            }

            decodedData.emplace_back(symbol);
        }

        if (ok)
            *ok = true;

        return decodedData;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

auto ByteArray::fromBase64(const ByteArray &data, bool *ok) noexcept -> ByteArray
{
    try {
        if (data.size() % 4 != 0) {
            if (ok)
                *ok = false;

            return {};
        }

        auto paddingSize = *data.rbegin() == '='
                ? (*std::next(data.rbegin()) == '='
                   ? 2
                   : 1)
                : 0;

        ByteArray decodedData {};
        decodedData.reserve((data.size() / 4) * 3 - paddingSize);

        std::array<char, 4> block;

        auto it = std::begin(data);
        auto end = paddingSize != 0
                ? std::prev(std::end(data), 4)
                : std::end(data);

        while (it != end) {
            for (auto i = 0; i < 4; ++i, ++it) {
                if (::isupper(*it)) {
                    block[i] = *it - 'A';
                } else if (::islower(*it)) {
                    block[i] = *it - 'a' + 26;
                } else if (::isdigit(*it)) {
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

            decodedData.emplace_back((block[0] << 2) + ((block[1] & 0x30) >> 4));
            decodedData.emplace_back(((block[1] & 0xf) << 4) + ((block[2] & 0x3c) >> 2));
            decodedData.emplace_back(((block[2] & 0x3) << 6) + block[3]);
        }

        switch (paddingSize) {
        case 1:
            for (auto i = 0; i < 3; ++i, ++it) {
                if (::isupper(*it)) {
                    block[i] = *it - 'A';
                } else if (::islower(*it)) {
                    block[i] = *it - 'a' + 26;
                } else if (::isdigit(*it)) {
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

            decodedData.emplace_back((block[0] << 2) + ((block[1] & 0x30) >> 4));
            decodedData.emplace_back(((block[1] & 0xf) << 4) + ((block[2] & 0x3c) >> 2));

            break;

        case 2:
            for (auto i = 0; i < 2; ++i, ++it) {
                if (::isupper(*it)) {
                    block[i] = *it - 'A';
                } else if (::islower(*it)) {
                    block[i] = *it - 'a' + 26;
                } else if (::isdigit(*it)) {
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

            decodedData.emplace_back((block[0] << 2) + ((block[1] & 0x30) >> 4));

            break;

        default:
            break;
        }

        if (ok)
            *ok = true;

        return decodedData;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

} // end namespace Calibri
