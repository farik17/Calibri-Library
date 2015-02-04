#ifndef CALIBRI_SIGNALS_SIGNAL_HPP
#define CALIBRI_SIGNALS_SIGNAL_HPP

//! Std includes
#include <list>
#include <mutex>
#include <iostream>

//! Calibri-Library includes
#include "connection.hpp"
#include "global/compilerdetection.hpp"

namespace Calibri {

namespace Signals {

//! Enumerations
enum class SignalConnectionMode : uint8 {
    DefaultConnection,
    UniqueConnection
};

/*!
 *  Signal class
 */
template<typename ...>
class Signal : private DisableConstructible
{
};

template<typename ReturnType,
         typename ...ArgumentsType>
class Signal<Internal::Function<ReturnType, ArgumentsType ...>> : private DisableCopyable, public Internal::TrackableObject, public Internal::TrackableObjectObserver
{
    //! Aliases
    using ConnectionType = Internal::Connection<Internal::Function<ReturnType, ArgumentsType ...>>;

public:
    virtual ~Signal() noexcept;

    auto operator ()(ArgumentsType &&...arguments) noexcept -> ReturnType;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
    auto connect(CallableType *callable) noexcept -> ConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
    auto connect(CallableType *callable) noexcept -> ConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignal, ObjectType>::value
                                     && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
    auto connect(ObjectType *object, CallableType callable) noexcept -> ConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignal, ObjectType>::value
                                     && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
    auto connect(ObjectType *object, CallableType callable) noexcept -> ConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
    auto connect(CallableType callable) noexcept -> ConnectionType *;

    template<SignalConnectionMode ConnectionMode = SignalConnectionMode::DefaultConnection,
             typename CallableType,
             typename std::enable_if<(Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                     && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
    auto connect(CallableType callable) noexcept -> ConnectionType *;

    template<typename CallableType,
             typename std::enable_if<Internal::IsFunctionObjectCallable<typename std::remove_reference<CallableType>::type, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    auto connect(CallableType &&callable) noexcept -> ConnectionType *;

    template<typename CallableType,
             typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    auto disconnect(CallableType *callable) noexcept -> bool;

    template<typename ObjectType,
             typename CallableType,
             typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                     && std::is_base_of<EnableSignal, ObjectType>::value)>::type ...Enabler>
    auto disconnect(ObjectType *object, CallableType callable) noexcept -> bool;

    template<typename CallableType,
             typename std::enable_if<Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
    auto disconnect(CallableType callable) noexcept -> bool;

    auto disconnect(ConnectionType *signalConnection) noexcept -> bool;

    auto disconnectAll() noexcept -> void;

    virtual auto destroyed(Internal::TrackableObject *trackableObject) noexcept -> void final;

private:
    std::list<std::pair<ConnectionType, Internal::TrackableObject *>> m_connections {};

    SpinLock m_context {};
};

/*!
 *  Signal inline methods
 */
template<typename ReturnType,
         typename ...ArgumentsType>
inline Signal<Internal::Function<ReturnType, ArgumentsType ...>>::~Signal() noexcept
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        for (const auto &item : m_connections) {
            if (item.second)
                item.second->disconnected(this);
        }
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::operator ()(ArgumentsType &&...arguments) noexcept -> ReturnType
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::begin(m_connections);

        for (decltype(it) end = std::prev(std::end(m_connections)); it != end; ++it)
            ((*it).first)(std::forward<ArgumentsType>(arguments) ...);

        if (it != std::end(m_connections))
            return ((*it).first)(std::forward<ArgumentsType>(arguments) ...);

        return ReturnType();
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return ReturnType();
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(CallableType *callable) noexcept -> ConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(callable), std::forward_as_tuple(callable));

        if (UNLIKELY(!callable->connected(this))) {
            m_connections.erase(it);

            return nullptr;
        }

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(CallableType *callable) noexcept -> ConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) {
            return item.first.isConnectedTo(callable);
        });

        if (it != std::end(m_connections))
            return nullptr;

        it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(callable), std::forward_as_tuple(callable));

        if (UNLIKELY(!callable->connected(this))) {
            m_connections.erase(it);

            return nullptr;
        }

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignal, ObjectType>::value
                                 && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(ObjectType *object, CallableType callable) noexcept -> ConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(object, callable), std::forward_as_tuple(object));

        if (UNLIKELY(!object->connected(this))) {
            m_connections.erase(it);

            return nullptr;
        }

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignal, ObjectType>::value
                                 && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(ObjectType *object, CallableType callable) noexcept -> ConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ object, &callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) {
            return item.first.isConnectedTo(object, callable);
        });

        if (it != std::end(m_connections))
            return nullptr;

        it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(object, callable), std::forward_as_tuple(object));

        if (UNLIKELY(!object->connected(this))) {
            m_connections.erase(it);

            return nullptr;
        }

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::DefaultConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(CallableType callable) noexcept -> ConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(callable), std::forward_as_tuple(nullptr));

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<SignalConnectionMode ConnectionMode,
         typename CallableType,
         typename std::enable_if<(Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value
                                 && ConnectionMode == SignalConnectionMode::UniqueConnection)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(CallableType callable) noexcept -> ConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) {
            return item.first.isConnectedTo(callable);
        });

        if (it != std::end(m_connections))
            return nullptr;

        it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(callable), std::forward_as_tuple(nullptr));

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsFunctionObjectCallable<typename std::remove_reference<CallableType>::type, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::connect(CallableType &&callable) noexcept -> ConnectionType *
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = m_connections.emplace(std::end(m_connections), std::piecewise_construct, std::forward_as_tuple(std::forward<CallableType>(callable)), std::forward_as_tuple(nullptr));

        return &((*it).first);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return nullptr;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsSignalCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::disconnect(CallableType *callable) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) {
            return item.first.isConnectedTo(callable);
        });

        if (it != std::end(m_connections)) {
            ((*it).second)->disconnected(this);

            m_connections.erase(it);

            return true;
        }

        return false;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return false;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename ObjectType,
         typename CallableType,
         typename std::enable_if<(Internal::IsMemberFunctionCallable<CallableType, ReturnType, ObjectType, ArgumentsType ...>::value
                                 && std::is_base_of<EnableSignal, ObjectType>::value)>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::disconnect(ObjectType *object, CallableType callable) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ object, &callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) {
            return item.first.isConnectedTo(object, callable);
        });

        if (it != std::end(m_connections)) {
            ((*it).second)->disconnected(this);

            m_connections.erase(it);

            return true;
        }

        return false;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return false;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
template<typename CallableType,
         typename std::enable_if<Internal::IsFunctionCallable<CallableType, ReturnType, ArgumentsType ...>::value>::type ...Enabler>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::disconnect(CallableType callable) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ callable ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) {
            return item.first.isConnectedTo(callable);
        });

        if (it != std::end(m_connections)) {
            m_connections.erase(it);

            return true;
        }

        return false;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return false;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::disconnect(ConnectionType *signalConnection) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_connections), std::end(m_connections), [ signalConnection ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) {
            return &item.first == signalConnection;
        });

        if (it != std::end(m_connections)) {
            if ((*it).second)
                ((*it).second)->disconnected(this);

            m_connections.erase(it);

            return true;
        }

        return false;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return false;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::disconnectAll() noexcept -> void
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        for (auto it = std::begin(m_connections); it != std::end(m_connections);) {
            if ((*it).second)
                (*it).second->disconnected(this);

            it = m_connections.erase(it);
        }
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;
    }
}

template<typename ReturnType,
         typename ...ArgumentsType>
inline auto Signal<Internal::Function<ReturnType, ArgumentsType ...>>::destroyed(Internal::TrackableObject *trackableObject) noexcept -> void
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        m_connections.remove_if([ trackableObject ](const std::pair<ConnectionType, Internal::TrackableObject *> &item) {
            return item.second == trackableObject;
        });
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;
    }
}

} // end namespace Signals

using Signals::SignalConnectionMode;
using Signals::Signal;

} // end namespace Calibri

#endif // CALIBRI_SIGNALS_SIGNAL_HPP
