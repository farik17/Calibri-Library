#ifndef MEMBERFUNCTION_H
#define MEMBERFUNCTION_H

//! Calibri-Library includes
#include "tools/disableconstructible.h"

namespace Calibri {

namespace Aliases {

template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
using MemberFunctionPointer = ReturnType (ClassType::*)(ArgumentsType ...);

} // end namespace Aliases

/*!
 *  MemberFunction class
 */
template<typename ...>
class MemberFunction : private DisableConstructible
{
};

template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
class MemberFunction<Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...>>
{
public:
    constexpr MemberFunction(ClassType *object, Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...> memberFunctionPointer) noexcept;
    constexpr MemberFunction(ClassType &object, Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...> memberFunctionPointer) noexcept;

    auto object() const noexcept -> ClassType *;
    auto memberFunctionPointer() const noexcept -> const Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...> &;

    auto operator ()(ArgumentsType &&...arguments) const noexcept(false) -> ReturnType;
    auto operator ==(const MemberFunction &other) const noexcept -> bool;
    auto operator !=(const MemberFunction &other) const noexcept -> bool;

private:
    ClassType *m_object {};
    Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...> m_memberFunctionPointer {};
};

/*!
 *  MemberFunction inline methods
 */
template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
inline constexpr MemberFunction<Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...>>::
MemberFunction(ClassType *object, Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...> memberFunctionPointer) noexcept :
    m_object { object },
    m_memberFunctionPointer { memberFunctionPointer }
{
}

template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
inline constexpr MemberFunction<Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...>>::
MemberFunction(ClassType &object, Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...> memberFunctionPointer) noexcept :
    MemberFunction { &object, memberFunctionPointer }
{
}

template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
inline auto MemberFunction<Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...>>::object() const noexcept -> ClassType *
{
    return m_object;
}

template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
inline auto MemberFunction<Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...>>::
memberFunctionPointer() const noexcept -> const Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...> &
{
    return m_memberFunctionPointer;
}

template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
inline auto MemberFunction<Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...>>::operator ()(ArgumentsType &&...arguments) const noexcept(false) -> ReturnType
{
    return (m_object->*m_memberFunctionPointer)(std::forward<ArgumentsType>(arguments) ...);
}

template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
inline auto MemberFunction<Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...>>::operator ==(const MemberFunction &other) const noexcept -> bool
{
    return m_object == other.m_object && m_memberFunctionPointer == other.m_memberFunctionPointer;
}

template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
inline auto MemberFunction<Aliases::MemberFunctionPointer<ReturnType, ClassType, ArgumentsType ...>>::operator !=(const MemberFunction &other) const noexcept -> bool
{
    return m_object != other.m_object || m_memberFunctionPointer != other.m_memberFunctionPointer;
}

} // end namesapce Calibri

#endif // MEMBERFUNCTION_H
