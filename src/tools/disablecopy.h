#ifndef DISABLECOPY_H
#define DISABLECOPY_H

//! Project Includes
#include "global.h"

namespace Calibri
{

class DisableCopy
{
public:
    DECL_CONSTEXPR explicit DisableCopy() DECL_NOEXCEPT {}

private:
    DisableCopy(const DisableCopy &) DECL_DELETE;
    DisableCopy &operator =(const DisableCopy &) DECL_DELETE;
};

}

#endif // DISABLECOPY_H
