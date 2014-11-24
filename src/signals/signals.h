#ifndef SIGNALS_H
#define SIGNALS_H

//! Std includes
#include <list>

//! Calibri-Library includes
#include "global/global.h"
#include "tools/disableconstructible.h"
#include "thread/spinlock.h"
#include "memberfunction.h"

namespace Calibri {

//! Enumerations
enum class SignalConnectionMode : uint8 {
    DefaultConnection,
    UniqueConnection
};

namespace Constants {

thread_local SpinLock threadContext {};
SpinLock globalContext {};

} // end namespace Constants

namespace Aliases {

template<typename ReturnType,
         typename ...ArgumentsType>
using SignalSignature = ReturnType (ArgumentsType ...);

} // end namespace Aliases

//! Forward declarations
class EnableSignals;
template<typename ...>
class Signal;

namespace Internal {

class FunctionCase
{
};

class FunctionPointerOrFunctionObjectCase
{
};

class MemberFunctionPointerCase
{
};

template<typename CallableType,
         typename ReturnType,
         typename ...ArgumentsType,
         typename std::enable_if<std::is_convertible<typename std::result_of<CallableType &(ArgumentsType ...)>::type, ReturnType>::value>::type ...Enabler>
constexpr auto isCallable(FunctionCase) noexcept -> std::true_type;

template<typename CallableType,
         typename ReturnType,
         typename ...ArgumentsType,
         typename std::enable_if<std::is_convertible<typename std::result_of<CallableType(ArgumentsType ...)>::type, ReturnType>::value>::type ...Enabler>
constexpr auto isCallable(FunctionPointerOrFunctionObjectCase) noexcept -> std::true_type;

template<typename CallableType,
         typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType,
         typename std::enable_if<std::is_convertible<typename std::result_of<CallableType(ClassType, ArgumentsType ...)>::type, ReturnType>::value>::type ...Enabler>
constexpr auto isCallable(MemberFunctionPointerCase) noexcept -> std::true_type;

template<typename ...>
constexpr auto isCallable(...) noexcept -> std::false_type;

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
    static constexpr auto value = (std::is_same<std::true_type, decltype(isCallable<SignalType, ReturnType, ArgumentsType ...>(FunctionPointerOrFunctionObjectCase()))>::value
                                   && IsSignal<SignalType>::value);
};

/*!
 *  IsFunctionCallable class
 */
template<typename FunctionType,
         typename ReturnType,
         typename ...ArgumentsType>
class IsFunctionCallable : private DisableConstructible
{
public:
    static constexpr auto value = (std::is_same<std::true_type, decltype(isCallable<FunctionType, ReturnType, ArgumentsType ...>(FunctionCase()))>::value
                                   && std::is_function<FunctionType>::value);
};

/*!
 *  IsFunctionObjectCallable class
 */
template<typename FunctionObjectType,
         typename ReturnType,
         typename ...ArgumentsType>
class IsFunctionObjectCallable : private DisableConstructible
{
public:
    static constexpr auto value = (std::is_same<std::true_type, decltype(isCallable<FunctionObjectType, ReturnType, ArgumentsType ...>(FunctionPointerOrFunctionObjectCase()))>::value
                                   && std::is_class<FunctionObjectType>::value);
};

/*!
 *  IsFunctionPointerCallable class
 */
template<typename FunctionPointerType,
         typename ReturnType,
         typename ...ArgumentsType>
class IsFunctionPointerCallable : private DisableConstructible
{
public:
    static constexpr auto value = (std::is_same<std::true_type, decltype(isCallable<FunctionPointerType, ReturnType, ArgumentsType ...>(FunctionPointerOrFunctionObjectCase()))>::value
                                   && std::is_pointer<FunctionPointerType>::value
                                   && std::is_function<typename std::remove_pointer<FunctionPointerType>::type>::value);
};

/*!
 *  IsMemberFunctionPointerCallable class
 */
template<typename MemberFunctionPointerType,
         typename ReturnType,
         typename ClassType,
         typename ...ArgumentsType>
class IsMemberFunctionPointerCallable : private DisableConstructible
{
public:
    static constexpr auto value = (std::is_same<std::true_type, decltype(isCallable<MemberFunctionPointerType, ReturnType, ClassType, ArgumentsType ...>(MemberFunctionPointerCase()))>::value
                                   && std::is_member_function_pointer<MemberFunctionPointerType>::value);
};

//! Forward declarations
class SignalTrackableObject;

/*!
 *  SignalObserver class
 */
class SignalObserver
{
public:
    virtual auto destroyed(SignalTrackableObject *trackableObject) noexcept -> void = 0;
};

/*!
 *  SignalTrackableObject class
 */
class SignalTrackableObject
{
public:
    virtual ~SignalTrackableObject() noexcept;

    auto connected(SignalObserver *observer) noexcept -> bool;
    auto disconnected(SignalObserver *observer) noexcept -> bool;

private:
    std::list<std::pair<SignalObserver *, size_t>> m_observers {};

    SpinLock m_context {};
};

/*!
 *  SignalTrackableObject inline methods
 */
inline SignalTrackableObject::~SignalTrackableObject() noexcept
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        for (const auto &pair : m_observers)
            (pair.first)->destroyed(this);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;
    }
}

inline auto SignalTrackableObject::connected(SignalObserver *observer) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_observers), std::end(m_observers), [observer](const std::pair<SignalObserver *, size_t> &pair) {
            return pair.first == observer;
        });

        if (it != std::end(m_observers))
            ++((*it).second);
        else
            m_observers.emplace_back(std::piecewise_construct, std::forward_as_tuple(observer), std::forward_as_tuple(1));

        return true;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return false;
    }
}

inline auto SignalTrackableObject::disconnected(SignalObserver *observer) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_observers), std::end(m_observers), [observer](const std::pair<SignalObserver *, size_t> &pair) {
            return pair.first == observer;
        });

        if (it != std::end(m_observers)) {
            if (--((*it).second) == 0)
                m_observers.erase(it);

            return true;
        }

        return false;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return false;
    }
}

/*!
 *  SignalConnection class
 */
template<typename ...>
class SignalConnection : private DisableConstructible
{
};

template<typename ReturnType,
         typename ...ArgumentsType>
class SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>> : private DisableCopyable
{
    using Invoker = ReturnType (*)(void *, ArgumentsType &&...) noexcept(false);
    using Deleter = void (*)(void *) noexcept;
    using Comparator = bool (*)(void *, void *) noexcept;

public:
    template<typename CallableType,
             typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    SignalConnection(CallableType *callable) noexcept;

    template<typename CallableType,
             typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    SignalConnection(CallableType &callable) noexcept;

    template<typename CallableType,
             typename std::enable_if<Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    SignalConnection(CallableType *callable) noexcept;

    template<typename CallableType,
             typename std::enable_if<Internal::IsFunctionObjectCallable<typename std::remove_reference<CallableType>::type, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    SignalConnection(CallableType &&callable) noexcept;

    template<typename CallableType,
             typename std::enable_if<Internal::IsFunctionPointerCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    SignalConnection(CallableType callable) noexcept;

    template<typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignals, ObjectType>::value)>::type ...Enabler>
    SignalConnection(ObjectType *object, CallableType callable) noexcept;

    template<typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignals, ObjectType>::value)>::type ...Enabler>
    SignalConnection(ObjectType &object, CallableType callable) noexcept;

    ~SignalConnection() noexcept;

    auto operator !=(const SignalConnection &other) const noexcept -> bool;
    auto operator ==(const SignalConnection &other) const noexcept -> bool;
    auto operator ()(ArgumentsType &&...arguments) const noexcept -> ReturnType;

    template<typename CallableType>
    auto isConnectedTo(CallableType *callable) const noexcept -> bool;

    template<typename CallableType>
    auto isConnectedTo(CallableType &callable) const noexcept -> bool;

    template<typename ObjectType,
             typename CallableReturnType,
             typename ...CallableArgumentsType>
    auto isConnectedTo(ObjectType *object, Aliases::MemberFunctionPointer<CallableReturnType, ObjectType, CallableArgumentsType ...> memberFunctionPointer) const noexcept -> bool;

    template<typename ObjectType,
             typename CallableReturnType,
             typename ...CallableArgumentsType>
    auto isConnectedTo(ObjectType &object, Aliases::MemberFunctionPointer<CallableReturnType, ObjectType, CallableArgumentsType ...> memberFunctionPointer) const noexcept -> bool;

private:
    void *m_callable {};

    Invoker m_invoker {};
    Deleter m_deleter {};
    Comparator m_comparator {};
};

/*!
 *  SignalConnection inline methods
 */
template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::SignalConnection(CallableType *callable) noexcept
{
    using SignalType = CallableType;

    m_callable = reinterpret_cast<decltype(m_callable)>(callable);
    m_invoker = [](void *callable, ArgumentsType &&...arguments) noexcept(false) -> ReturnType {
        return (*reinterpret_cast<SignalType *>(callable))(std::forward<ArgumentsType>(arguments) ...);
    };
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::SignalConnection(CallableType &callable) noexcept :
    SignalConnection(&callable)
{
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::SignalConnection(CallableType *callable) noexcept
{
    using FunctionType = CallableType;

    m_callable = reinterpret_cast<decltype(m_callable)>(callable);
    m_invoker = [](void *callable, ArgumentsType &&...arguments) noexcept(false) -> ReturnType {
        std::lock_guard<SpinLock> locker { Constants::globalContext };

        return reinterpret_cast<FunctionType *>(callable)(std::forward<ArgumentsType>(arguments) ...);
    };
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsFunctionObjectCallable<typename std::remove_reference<CallableType>::type, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::SignalConnection(CallableType &&callable) noexcept
{
    try {
        using FunctionObjectType = typename std::remove_reference<CallableType>::type;

        m_callable = new FunctionObjectType(std::forward<CallableType>(callable));
        m_invoker = [](void *callable, ArgumentsType &&...arguments) noexcept(false) -> ReturnType {
            return (*reinterpret_cast<FunctionObjectType *>(callable))(std::forward<ArgumentsType>(arguments) ...);
        };
        m_deleter = [](void *callable) noexcept {
            delete reinterpret_cast<FunctionObjectType *>(callable);
        };
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsFunctionPointerCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::SignalConnection(CallableType callable) noexcept
{
    using FunctionPointerType = CallableType;

    m_callable = reinterpret_cast<decltype(m_callable)>(callable);
    m_invoker = [](void *callable, ArgumentsType &&...arguments) noexcept(false) -> ReturnType {
        std::lock_guard<SpinLock> locker { Constants::globalContext };

        return reinterpret_cast<FunctionPointerType>(callable)(std::forward<ArgumentsType>(arguments) ...);
    };
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignals, ObjectType>::value)>::type ...Enabler>
inline SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::SignalConnection(ObjectType *object, CallableType callable) noexcept
{
    using MemberFunctionType = MemberFunction<CallableType>;

    m_callable = new MemberFunctionType(object, callable);
    m_invoker = [](void *callable, ArgumentsType &&...arguments) noexcept(false) -> ReturnType {
        std::lock_guard<SpinLock> locker { reinterpret_cast<MemberFunctionType *>(callable)->object()->context() };

        return (*reinterpret_cast<MemberFunctionType *>(callable))(std::forward<ArgumentsType>(arguments) ...);
    };
    m_deleter = [](void *callable) noexcept {
        delete reinterpret_cast<MemberFunctionType *>(callable);
    };
    m_comparator = [](void *thisCallable, void *otherCallable) noexcept -> bool {
        return (*reinterpret_cast<MemberFunctionType *>(thisCallable)) == (*reinterpret_cast<MemberFunctionType *>(otherCallable));
    };
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignals, ObjectType>::value)>::type ...Enabler>
inline SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::SignalConnection(ObjectType &object, CallableType callable) noexcept :
    SignalConnection(&object, callable)
{
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::~SignalConnection() noexcept
{
    if (m_deleter)
        m_deleter(m_callable);
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::operator !=(const SignalConnection &other) const noexcept -> bool
{
    if (m_comparator)
        return !m_comparator(m_callable, other.m_callable);

    return m_callable != other.m_callable;
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::operator ==(const SignalConnection &other) const noexcept -> bool
{
    if (m_comparator)
        return m_comparator(m_callable, other.m_callable);

    return m_callable == other.m_callable;
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::operator ()(ArgumentsType &&...arguments) const noexcept -> ReturnType
{
    try {
        return m_invoker(m_callable, std::forward<ArgumentsType>(arguments) ...);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return ReturnType();
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType>
inline auto SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::isConnectedTo(CallableType *callable) const noexcept -> bool
{
    return m_callable == callable;
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType>
inline auto SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::isConnectedTo(CallableType &callable) const noexcept -> bool
{
    return isConnectedTo(&callable);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableReturnType,
         typename ...CallableArgumentsType>
inline auto SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::
isConnectedTo(ObjectType *object, Aliases::MemberFunctionPointer<CallableReturnType, ObjectType, CallableArgumentsType ...> memberFunctionPointer) const noexcept -> bool
{
    if (m_comparator) {
        auto memberFunction = MemberFunction<decltype(memberFunctionPointer)>(object, memberFunctionPointer);

        return m_comparator(m_callable, reinterpret_cast<decltype(m_callable)>(&memberFunction));
    }

    return false;
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableReturnType,
         typename ...CallableArgumentsType>
inline auto SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::
isConnectedTo(ObjectType &object, Aliases::MemberFunctionPointer<CallableReturnType, ObjectType, CallableArgumentsType ...> memberFunctionPointer) const noexcept -> bool
{
    return isConnectedTo(&object, memberFunctionPointer);
}

} // end namespace Internal

/*!
 *  EnableSignals class
 */
class EnableSignals : private DisableCopyable, public Internal::SignalTrackableObject
{
public:
    auto context() const noexcept -> SpinLock &;

private:
    SpinLock *m_context { &Constants::threadContext };
};

/*!
 *  EnableSignals inline methods
 */
inline auto EnableSignals::context() const noexcept -> SpinLock &
{
    return *m_context;
}

/*!
 *  Signal class
 */
template<typename ...>
class Signal : private DisableConstructible
{
};

template<typename ReturnType,
         typename ...ArgumentsType>
class Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>> : private DisableCopyable, public Internal::SignalTrackableObject, public Internal::SignalObserver
{
    using SignalConnectionType = Internal::SignalConnection<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>;

public:
    virtual ~Signal() noexcept;

    auto operator ()(ArgumentsType &&...arguments) noexcept -> ReturnType;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
    auto connect(CallableType *callable) noexcept -> SignalConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
    auto connect(CallableType *callable) noexcept -> SignalConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
    auto connect(CallableType &callable) noexcept -> SignalConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
    auto connect(CallableType &callable) noexcept -> SignalConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignals, ObjectType>::value
                                     && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
    auto connect(ObjectType *object, CallableType callable) noexcept -> SignalConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignals, ObjectType>::value
                                     && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
    auto connect(ObjectType *object, CallableType callable) noexcept -> SignalConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignals, ObjectType>::value
                                     && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
    auto connect(ObjectType &object, CallableType callable) noexcept -> SignalConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignals, ObjectType>::value
                                     && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
    auto connect(ObjectType &object, CallableType callable) noexcept -> SignalConnectionType *;

    template<typename CallableType,
             typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    auto disconnect(CallableType *callable) noexcept -> bool;

    template<typename CallableType,
             typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    auto disconnect(CallableType &callable) noexcept -> bool;

    template<typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignals, ObjectType>::value)>::type ...Enabler>
    auto disconnect(ObjectType *object, CallableType callable) noexcept -> bool;

    template<typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignals, ObjectType>::value)>::type ...Enabler>
    auto disconnect(ObjectType &object, CallableType callable) noexcept -> bool;

    auto disconnect(SignalConnectionType *signalConnection) noexcept -> bool;

    virtual auto destroyed(Internal::SignalTrackableObject *trackableObject) noexcept -> void override;

private:
    std::list<std::pair<SignalConnectionType, SignalTrackableObject *>> m_connections {};

    SpinLock m_context {};
};

/*!
 *  Signal inline methods
 */
template<typename ReturnType,
         typename ...ArgumentsType>
inline Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::~Signal() noexcept
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        for (const auto &pair : m_connections)
            (pair.second)->disconnected(this);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::operator ()(ArgumentsType &&...arguments) noexcept -> ReturnType
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::begin(m_connections);

        for (decltype(it) end = std::prev(std::end(m_connections)); it != end; ++it)
            ((*it).first)(std::forward<ArgumentsType>(arguments) ...);

        if (it != std::end(m_connections))
            return (m_connections.back().first)(std::forward<ArgumentsType>(arguments) ...);

        return ReturnType();
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return ReturnType();
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::connect(CallableType *callable) noexcept -> SignalConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(callable), std::forward_as_tuple(callable));

        callable->connected(this);

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::connect(CallableType *callable) noexcept -> SignalConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [callable](const std::pair<SignalConnectionType, SignalTrackableObject *> &pair) {
            return pair.first.isConnectedTo(callable);
        });

        if (it != std::end(m_connections))
            return nullptr;

        it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(callable), std::forward_as_tuple(callable));

        callable->connected(this);

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::connect(CallableType &callable) noexcept -> SignalConnectionType *
{
    return connect(&callable);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::connect(CallableType &callable) noexcept -> SignalConnectionType *
{
    return connect<ConnectionMode>(&callable);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignals, ObjectType>::value
                                 && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::connect(ObjectType *object, CallableType callable) noexcept -> SignalConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(object, callable), std::forward_as_tuple(object));

        object->connected(this);

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignals, ObjectType>::value
                                 && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::connect(ObjectType *object, CallableType callable) noexcept -> SignalConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [object, &callable](const std::pair<SignalConnectionType, SignalTrackableObject *> &pair) {
            return pair.first.isConnectedTo(object, callable);
        });

        if (it != std::end(m_connections))
            return nullptr;

        it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(object, callable), std::forward_as_tuple(object));

        object->connected(this);

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignals, ObjectType>::value
                                 && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::connect(ObjectType &object, CallableType callable) noexcept -> SignalConnectionType *
{
    return connect(&object, callable);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignals, ObjectType>::value
                                 && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::connect(ObjectType &object, CallableType callable) noexcept -> SignalConnectionType *
{
    return connect<ConnectionMode>(&object, callable);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::disconnect(CallableType *callable) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [callable](const std::pair<SignalConnectionType, SignalTrackableObject *> &pair) {
            return pair.first.isConnectedTo(callable);
        });

        if (it != std::end(m_connections)) {
            ((*it).second)->disconnected(this);

            m_connections.erase(it);

            return true;
        }

        return false;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return false;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::disconnect(CallableType &callable) noexcept -> bool
{
    return disconnect(&callable);
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignals, ObjectType>::value)>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::disconnect(ObjectType *object, CallableType callable) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [object, &callable](const std::pair<SignalConnectionType, SignalTrackableObject *> &pair) {
            return pair.first.isConnectedTo(object, callable);
        });

        if (it != std::end(m_connections)) {
            ((*it).second)->disconnected(this);

            m_connections.erase(it);

            return true;
        }

        return false;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return false;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionPointerCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignals, ObjectType>::value)>::type ...Enabler>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::disconnect(ObjectType &object, CallableType callable) noexcept -> bool
{
    return disconnect(&object, callable);
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::disconnect(SignalConnectionType *signalConnection) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [signalConnection](const std::pair<SignalConnectionType, SignalTrackableObject *> &pair) {
            return pair.first == *signalConnection;
        });

        if (it != std::end(m_connections)) {
            ((*it).second)->disconnected(this);

            m_connections.erase(it);

            return true;
        }

        return false;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return false;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Signal<Aliases::SignalSignature<ReturnType, ArgumentsType ...>>::destroyed(Internal::SignalTrackableObject *trackableObject) noexcept -> void
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        m_connections.remove_if([trackableObject](const std::pair<SignalConnectionType, SignalTrackableObject *> &pair) {
            return pair.second == trackableObject;
        });
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;
    }
}

} // end namespace Calibri

#endif // SIGNALS_H
