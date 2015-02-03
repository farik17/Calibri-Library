#ifndef CALIBRI_TOOLS_DISABLECONSTRUCTIBLE_HPP
#define CALIBRI_TOOLS_DISABLECONSTRUCTIBLE_HPP

//! Calibri-Library Includes
#include "disablecopyable.hpp"

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

#endif // CALIBRI_TOOLS_DISABLECONSTRUCTIBLE_HPP
