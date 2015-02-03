#ifndef CALIBRI_SIGNALS_MEMBERFUNCTIONWRAPPER_HPP
#define CALIBRI_SIGNALS_MEMBERFUNCTIONWRAPPER_HPP

//! Calibri-Library includes
#include "tools/disableconstructible.hpp"

namespace Calibri {

namespace Internal {

//! Aliases
template<typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
using MemberFunction = ReturnType (ClassType::*)(ArgumentsType ...);

/*!
 *  MemberFunction class
 */
template<typename ...>
class MemberFunctionWrapper : private DisableConstructible
{
};

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
class MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>
{
public:
    constexpr MemberFunctionWrapper(ObjectType *object, MemberFunction<ReturnType, ObjectType, ArgumentsType ...> memberFunctionPointer) noexcept;

    auto object() const noexcept -> ObjectType *;
    auto memberFunctionPointer() const noexcept -> const MemberFunction<ReturnType, ObjectType, ArgumentsType ...> &;

    auto operator ()(ArgumentsType &&...arguments) const -> ReturnType;
    auto operator ==(const MemberFunctionWrapper &other) const noexcept -> bool;
    auto operator !=(const MemberFunctionWrapper &other) const noexcept -> bool;

private:
    MemberFunction<ReturnType, ObjectType, ArgumentsType ...> m_memberFunction {};

    ObjectType *m_object {};
};

/*!
 *  MemberFunction inline methods
 */
template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline constexpr MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::
MemberFunctionWrapper(ObjectType *object, MemberFunction<ReturnType, ObjectType, ArgumentsType ...> memberFunctionPointer) noexcept :
    m_memberFunction { memberFunctionPointer },
    m_object { object }
{
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::object() const noexcept -> ObjectType *
{
    return m_object;
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::
memberFunctionPointer() const noexcept -> const MemberFunction<ReturnType, ObjectType, ArgumentsType ...> &
{
    return m_memberFunction;
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::operator ()(ArgumentsType &&...arguments) const -> ReturnType
{
    return (m_object->*m_memberFunction)(std::forward<ArgumentsType>(arguments) ...);
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::operator ==(const MemberFunctionWrapper &other) const noexcept -> bool
{
    return m_object == other.m_object && m_memberFunction == other.m_memberFunction;
}

template<typename ObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
inline auto MemberFunctionWrapper<MemberFunction<ReturnType, ObjectType, ArgumentsType ...>>::operator !=(const MemberFunctionWrapper &other) const noexcept -> bool
{
    return m_object != other.m_object || m_memberFunction != other.m_memberFunction;
}

} // end namespace Internal

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_MEMBERFUNCTIONWRAPPER_HPP
