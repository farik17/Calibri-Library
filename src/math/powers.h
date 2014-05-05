#ifndef POWERS_H
#define POWERS_H

//! Std Includes
#include <cmath>

//! Project Includes
#include "global.h"

namespace Calibri
{

namespace Powers
{

namespace Internal
{

DECL_CONSTEXPR inline longdouble implementation(int64 exponent, longdouble base, longdouble value)
{
    return exponent != 0
            ? implementation(exponent >> 1, base * base, (exponent & 1) != 0 ? base * value : value)
            : value;
}

DECL_CONSTEXPR inline longdouble implementation(int64 exponent, longdouble base)
{
    return exponent >= 0
            ? implementation(exponent, base, 1.0e0l)
            : 1.0e0l / implementation(std::abs(exponent), base, 1.0e0l);
}

}

}

DECL_CONSTEXPR inline longdouble powerOf(int64 exponent, longdouble base)
{
    return Powers::Internal::implementation(exponent, base);
}

}

#endif // POWERS_H
