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

namespace Internal
{

DECL_CONSTEXPR inline longdouble positive(int64 exponent, longdouble base, longdouble value = 1.0e0l)
{
    return exponent != 0
            ? positive(exponent >> 1, base * base, (exponent & 1) != 0 ? value * base : value)
            : value;
}

DECL_CONSTEXPR inline longdouble negative(int64 exponent, longdouble base, longdouble value = 1.0e0l)
{
    return exponent != 0
            ? negative(exponent >> 1, base * base, (exponent & 1) != 0 ? value / base : value)
            : value;
}

DECL_CONSTEXPR inline longdouble implementation(int64 exponent, longdouble base)
{
    return exponent >= 0
            ? Powers::Internal::positive(exponent, base)
            : Powers::Internal::negative(std::abs(exponent), base);
}

}

}

DECL_CONSTEXPR inline longdouble powerOf(int64 exponent, longdouble base)
{
    return Powers::Internal::implementation(exponent, base);
}

}

#endif // POWERS_H
