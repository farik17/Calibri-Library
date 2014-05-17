#ifndef STRING_CAST_H
#define STRING_CAST_H

//! Std Includes
#include <string>
#include <cmath>
#include <limits>

//! Project Includes
#include "repeater.h"

namespace Calibri
{

namespace StringCast
{

namespace Constants
{

CONSTEXPR static size_t unrollCount = 4;

template<typename DataType>
class Exponent
{
private:
    DISABLE_COPY(Exponent)

    Exponent() DECL_NOEXCEPT {}
};

template<>
class Exponent<float>
{
public:
    CONSTEXPR static size_t base = 10;
    CONSTEXPR static size_t digits = 2;

private:
    DISABLE_COPY(Exponent<float>)

    Exponent<float>() DECL_NOEXCEPT {}
};

template<>
class Exponent<double>
{
public:
    CONSTEXPR static size_t base = 10;
    CONSTEXPR static size_t digits = 3;

private:
    DISABLE_COPY(Exponent<double>)

    Exponent<double>() DECL_NOEXCEPT {}
};

template<>
class Exponent<longdouble>
{
public:
    CONSTEXPR static size_t base = 10;
    CONSTEXPR static size_t digits = 4;

private:
    DISABLE_COPY(Exponent<longdouble>)

    Exponent<longdouble>() DECL_NOEXCEPT {}
};

}

namespace Internal
{

template<typename DataType>
inline typename std::enable_if<std::is_integral<DataType>::value, DataType>::type implementation(const char *data)
{
    if (!data)
        return 0;

    while (std::isspace(*data))
        ++data;

    int8 sign = 1;

    switch (*data) {
    case '-':
        sign = -1;

    case '+':
        ++data;

        break;

    default:
        break;
    }

    DataType result = 0;

    bool abort = false;

    do {
        Repeater<Constants::unrollCount>::run([&data, &abort, &result]() {
            if (data == '\0' || !std::isdigit(*data)) {
                abort = true;
                return;
            }

            result *= 10;
            result += *(data++) - '0';
        });
    } while (!abort);

    result *= sign;

    return result;
}

template<typename DataType>
inline typename std::enable_if<std::is_floating_point<DataType>::value, DataType>::type implementation(const char *data)
{
    if (!data)
        return 0;

    while (std::isspace(*data))
        ++data;

    int8 sign = 1;

    switch (*data) {
    case '-':
        sign = -1;

    case '+':
        ++data;

        break;

    default:
        break;
    }

    DataType result = 0;

    bool abort = false;

    do {
        Repeater<Constants::unrollCount>::run([&data, &abort, &result]() {
            if (data == '\0' || !std::isdigit(*data)) {
                abort = true;
                return;
            }

            result *= 10;
            result += *(data++) - '0';
        });
    } while (!abort);

    result *= sign;

    if (*data == '.') {
        ++data;

        DataType fraction = 0;

        int16 decimals = 0;

        abort = false;

        do {
            Repeater<Constants::unrollCount>::run([&data, &abort, &fraction, &decimals]() {
                if (data == '\0' || !std::isdigit(*data)) {
                    abort = true;
                    return;
                }

                fraction *= 10;
                fraction += *(data++) - '0';

                ++decimals;
            });

            if (decimals >= std::numeric_limits<DataType>::digits10)
                abort = true;
        } while (!abort);

        result += sign * fraction / std::pow(Constants::Exponent<DataType>::base, decimals);
    }

    if (*data == 'e' || *data == 'E') {
        ++data;

        sign = 1;

        switch (*data) {
        case '-':
            sign = -1;

        case '+':
            ++data;

            break;

        default:
            break;
        }

        int16 exponent = 0;

        Repeater<Constants::Exponent<DataType>::digits>::run([&data, &exponent]() {
            if (data == '\0' || !std::isdigit(*data))
                return;

            exponent *= 10;
            exponent += *(data++) - '0';
        });

        exponent *= sign;

        switch (sign) {
        case 1:
            exponent = exponent > std::numeric_limits<DataType>::max_exponent10 ? std::numeric_limits<DataType>::max_exponent10 : exponent;

            break;

        case -1:
            exponent = exponent < std::numeric_limits<DataType>::min_exponent10 ? std::numeric_limits<DataType>::min_exponent10 : exponent;

            break;

        default:
            break;
        }

        result *= std::pow(Constants::Exponent<DataType>::base, exponent);
    }

    return result;
}

}

}

template<typename DataType>
inline DataType string_cast(const std::string &data)
{
    return StringCast::Internal::implementation<DataType>(data.c_str());
}

}

#endif // STRING_CAST_H
