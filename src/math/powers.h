#ifndef POWERS_H
#define POWERS_H

//! Std Includes
#include <type_traits>
#include <limits>
#include <cmath>

//! Project Includes
#include "global.h"

namespace Calibri
{

namespace Powers
{

namespace Constants
{

CONSTEXPR static longdouble powersOf2[] = {
    2e0l,
    4e0l,
    16e0l,
    256e0l,
    65536e0l,
    4294967296e0l,
    18446744073709551616e0l,
    3.40282366920938463463e38l,
    1.15792089237316195424e77l,
    1.34078079299425970996e154l,
    1.79769313486231590773e308l,
    3.23170060713110073007e616l,
    1.04438888141315250669e1233l,
    1.09074813561941592946e2466l
};

CONSTEXPR static longdouble powersOf8[] = {
    8e0l,
    64e0l,
    4096e0l,
    16777216e0l,
    281474976710656e0l,
    7.92281625142643375935e28l,
    6.27710173538668076384e57l,
    3.94020061963944792123e115l,
    1.55251809230070893515e231l,
    2.41031242692103258858e462l,
    5.80960599536995806286e924l,
    3.37515218214385611849e1849l,
    1.13916522526304337085e3699l
};

CONSTEXPR static longdouble powersOf10[] = {
    1e1l,
    1e2l,
    1e4l,
    1e8l,
    1e16l,
    1e32l,
    1e64l,
    1e128l,
    1e256l,
    1e512l,
    1e1024l,
    1e2048l,
    1e4096l
};

CONSTEXPR static longdouble powersOf16[] = {
    16e0l,
    256e0l,
    65536e0l,
    4294967296e0l,
    18446744073709551616e0l,
    3.40282366920938463463e38l,
    1.15792089237316195424e77l,
    1.34078079299425970996e154l,
    1.79769313486231590773e308l,
    3.23170060713110073007e616l,
    1.04438888141315250669e1233l,
    1.09074813561941592946e2466l
};

}

namespace Internal
{

DECL_CONSTEXPR inline longdouble positive(int16 exponent, const longdouble *powers, longdouble value = 1.0e0l)
{
    return exponent != 0
            ? (exponent & 1)
              ? positive(exponent >> 1, powers + 1, value * *powers)
              : positive(exponent >> 1, powers + 1, value)
              : value < 1.0e0l
                ? std::numeric_limits<longdouble>::infinity()
                : value;
}

DECL_CONSTEXPR inline longdouble negative(int16 exponent, const longdouble *powers, longdouble value = 1.0e0l)
{
    return exponent != 0
            ? (exponent & 1)
              ? negative(exponent >> 1, powers + 1, value / *powers)
              : negative(exponent >> 1, powers + 1, value)
              : value > 1.0e0l
                ? 0
                : value;
}

DECL_CONSTEXPR inline longdouble implementation(int16 exponent, const longdouble *powers)
{
    return exponent >= 0
            ? positive(exponent, powers)
            : negative(std::abs(exponent), powers);
}

}

}

template<uint8 Base>
DECL_CONSTEXPR inline const typename std::enable_if<Base == 2, longdouble>::type powerOf(int16 exponent)
{
    return Powers::Internal::implementation(exponent, Powers::Constants::powersOf2);
}

template<uint8 Base>
DECL_CONSTEXPR inline const typename std::enable_if<Base == 8, longdouble>::type powerOf(int16 exponent)
{
    return Powers::Internal::implementation(exponent, Powers::Constants::powersOf8);
}

template<uint8 Base>
DECL_CONSTEXPR inline const typename std::enable_if<Base == 10, longdouble>::type powerOf(int16 exponent)
{
    return Powers::Internal::implementation(exponent, Powers::Constants::powersOf10);
}

template<uint8 Base>
DECL_CONSTEXPR inline const typename std::enable_if<Base == 16, longdouble>::type powerOf(int16 exponent)
{
    return Powers::Internal::implementation(exponent, Powers::Constants::powersOf16);
}

}

#endif // POWERS_H
