#ifndef CALIBRI_TOOL_DISABLECONSTRUCTIBLE_HPP
#define CALIBRI_TOOL_DISABLECONSTRUCTIBLE_HPP

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

#endif // CALIBRI_TOOL_DISABLECONSTRUCTIBLE_HPP
