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

CONSTEXPR static auto multiplier = [](longdouble base, longdouble value) -> longdouble { return value * base; };
CONSTEXPR static auto divisor = [](longdouble base, longdouble value) -> longdouble { return value / base; };

}

namespace Internal
{

template<typename Predicate>
DECL_CONSTEXPR inline longdouble implementation(Predicate predicate, int64 exponent, longdouble base, longdouble value = 1.0e0l)
{
    return exponent != 0
            ? implementation(predicate, exponent >> 1, base * base, (exponent & 1) != 0 ? predicate(base, value) : value)
            : value;
}

DECL_CONSTEXPR inline longdouble implementation(int64 exponent, longdouble base)
{
    return exponent >= 0
            ? implementation(Constants::multiplier, exponent, base)
            : implementation(Constants::divisor, std::abs(exponent), base);
}

}

}

DECL_CONSTEXPR inline longdouble powerOf(int64 exponent, longdouble base)
{
    return Powers::Internal::implementation(exponent, base);
}

}

#endif // POWERS_H
