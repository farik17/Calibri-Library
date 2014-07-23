#ifndef ELAPSEDTIMER_H
#define ELAPSEDTIMER_H

//! Std Includes
#include <chrono>

//! Calibri-Library Includes
#include "global/global.h"

namespace Calibri {

enum class ElapsedTimerMetrics : uint8 {
    Hours = 0,
    Minutes,
    Seconds,
    Miliseconds,
    Microseconds,
    Nanoseconds
};

class ElapsedTimer
{
public:
    constexpr ElapsedTimer() noexcept;

    auto start() noexcept -> void;
    auto reset() noexcept -> void;

    auto restart(ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) noexcept -> uint64;
    auto elapsed(ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) const noexcept -> uint64;

    auto hasExpired(uint64 timeout, ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) const noexcept -> bool;

private:
    auto expired(ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) const noexcept -> uint64;

    std::chrono::steady_clock::time_point m_startPoint {};
};

/*!
 * ElapsedTimer inline methods
 */
inline constexpr ElapsedTimer::ElapsedTimer() noexcept
{
}

inline auto ElapsedTimer::start() noexcept -> void
{
    m_startPoint = std::chrono::steady_clock::now();
}

inline auto ElapsedTimer::reset() noexcept -> void
{
    m_startPoint = std::chrono::steady_clock::time_point();
}

inline auto ElapsedTimer::restart(ElapsedTimerMetrics metrics) noexcept -> uint64
{
    auto timeExpired = expired(metrics);

    m_startPoint = std::chrono::steady_clock::now();

    return timeExpired;
}

inline auto ElapsedTimer::elapsed(ElapsedTimerMetrics metrics) const noexcept -> uint64
{
    return expired(metrics);
}

inline auto ElapsedTimer::hasExpired(uint64 timeout, ElapsedTimerMetrics metrics) const noexcept -> bool
{
    return timeout < elapsed(metrics);
}

} // namespace Calibri

#endif // ELAPSEDTIMER_H
