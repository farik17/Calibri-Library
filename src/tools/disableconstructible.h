#ifndef DISABLECONSTRUCTIBLE_H
#define DISABLECONSTRUCTIBLE_H

//! Calibri-Library Includes
#include "disablecopyable.h"

namespace Calibri {

/*!
 *  DisableCopyable class
 */
class DisableConstructible : private DisableCopyable
{
private:
    DisableConstructible() = delete;
};

} // end namespace Calibri

#endif // DISABLECONSTRUCTIBLE_H
