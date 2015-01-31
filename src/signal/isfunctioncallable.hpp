#ifndef CALIBRI_SIGNAL_ISFUNCTIONCALLABLE_HPP
#define CALIBRI_SIGNAL_ISFUNCTIONCALLABLE_HPP

//! Calibri-Library includes
#include "iscallable.hpp"
#include "tool/disableconstructible.hpp"

namespace Calibri {

namespace Internal {

/*!
 *  IsFunctionCallable class
 */
template<typename FunctionType,
         typename ReturnType,
         typename ...ArgumentsType>
class IsFunctionCallable : private DisableConstructible
{
public:
    static constexpr auto value = (std::is_same<std::true_type, decltype(isCallable<FunctionType, ReturnType, ArgumentsType ...>(FunctionOrFunctionObjectCase()))>::value
                                   && std::is_pointer<FunctionType>::value
                                   && std::is_function<typename std::remove_pointer<FunctionType>::type>::value);
};

} // end namespace Internal

} // end namespace Calibri

#endif // CALIBRI_SIGNAL_ISFUNCTIONCALLABLE_HPP
