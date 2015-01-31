#ifndef CALIBRI_SIGNAL_ISSIGNALCALLABLE_HPP
#define CALIBRI_SIGNAL_ISSIGNALCALLABLE_HPP

//! Calibri-Library includes
#include "iscallable.hpp"
#include "tool/disableconstructible.hpp"

namespace Calibri {

namespace Internal {

//! Forward declarations
template<typename ...>
class Signal;

/*!
 *  IsSignal class
 */
template<typename ...>
class IsSignal : private DisableConstructible
{
public:
    static constexpr auto value = false;
};

template<typename ReturnType,
         typename ...ArgumentsType>
class IsSignal<Signal<ReturnType, ArgumentsType ...>> : private DisableConstructible
{
public:
    static constexpr auto value = true;
};

/*!
 *  IsSignalCallable class
 */
template<typename SignalType,
         typename ReturnType,
         typename ...ArgumentsType>
class IsSignalCallable : private DisableConstructible
{
public:
    static constexpr auto value = (std::is_same<std::true_type, decltype(isCallable<SignalType, ReturnType, ArgumentsType ...>(FunctionOrFunctionObjectCase()))>::value
                                   && IsSignal<SignalType>::value);
};

} // end namespace Internal

} // end namespace Calibri

#endif // CALIBRI_SIGNAL_ISSIGNALCALLABLE_HPP
