#ifndef CALIBRI_SIGNAL_TRACKABLEOBJECT_HPP
#define CALIBRI_SIGNAL_TRACKABLEOBJECT_HPP

//! Std includes
#include <mutex>
#include <vector>
#include <iostream>

//! Calibri-Library includes
#include "thread/spinlock.hpp"

namespace Calibri {

namespace Internal {

//! Forward declarations
class TrackableObject;

/*!
 *  SignalObserver class
 */
class TrackableObjectObserver
{
public:
    virtual auto destroyed(TrackableObject *trackableObject) noexcept -> void = 0;
};

/*!
 *  SignalTrackableObject class
 */
class TrackableObject
{
public:
    virtual ~TrackableObject() noexcept;

    auto connected(TrackableObjectObserver *observer) noexcept -> bool;
    auto disconnected(TrackableObjectObserver *observer) noexcept -> bool;

private:
    std::vector<std::pair<TrackableObjectObserver *, uint32>> m_observers {};

    SpinLock m_context {};
};

/*!
 *  SignalTrackableObject inline methods
 */
inline TrackableObject::~TrackableObject() noexcept
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        for (const auto &pair : m_observers)
            (pair.first)->destroyed(this);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;
    }
}

inline auto TrackableObject::connected(TrackableObjectObserver *observer) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_observers), std::end(m_observers), [ observer ](const std::pair<TrackableObjectObserver *, uint32> &pair) {
            return pair.first == observer;
        });

        if (it != std::end(m_observers))
            ++((*it).second);
        else
            m_observers.emplace_back(std::piecewise_construct, std::forward_as_tuple(observer), std::forward_as_tuple(1));

        return true;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return false;
    }
}

inline auto TrackableObject::disconnected(TrackableObjectObserver *observer) noexcept -> bool
{
    try {
        std::lock_guard<SpinLock> locker { m_context };

        auto it = std::find_if(std::begin(m_observers), std::end(m_observers), [ observer ](const std::pair<TrackableObjectObserver *, uint32> &pair) {
            return pair.first == observer;
        });

        if (it != std::end(m_observers)) {
            if (--((*it).second) == 0)
                m_observers.erase(it);

            return true;
        }

        return false;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return false;
    }
}

} // end namespace Internal

} // end namespace Calibri

#endif // CALIBRI_SIGNAL_TRACKABLEOBJECT_HPP
