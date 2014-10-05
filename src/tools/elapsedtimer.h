#ifndef ELAPSEDTIMER_H
#define ELAPSEDTIMER_H

//! Std Includes
#include <chrono>

//! Calibri-Library Includes
#include "global/global.h"

namespace Calibri {

enum class ElapsedTimerMetric : uint8 {
    Hours,
    Minutes,
    Seconds,
    Miliseconds,
    Microseconds,
    Nanoseconds
};

namespace Internal {

template<ElapsedTimerMetric Metric, typename std::enable_if<Metric == ElapsedTimerMetric::Hours>::type... Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::hours>(finish - start).count();
}

template<ElapsedTimerMetric Metric, typename std::enable_if<Metric == ElapsedTimerMetric::Minutes>::type... Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::minutes>(finish - start).count();
}

template<ElapsedTimerMetric Metric, typename std::enable_if<Metric == ElapsedTimerMetric::Seconds>::type... Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::seconds>(finish - start).count();
}

template<ElapsedTimerMetric Metric, typename std::enable_if<Metric == ElapsedTimerMetric::Miliseconds>::type... Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
}

template<ElapsedTimerMetric Metric, typename std::enable_if<Metric == ElapsedTimerMetric::Microseconds>::type... Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

template<ElapsedTimerMetric Metric, typename std::enable_if<Metric == ElapsedTimerMetric::Nanoseconds>::type... Enabler>
inline auto duration(const std::chrono::steady_clock::time_point &start, const std::chrono::steady_clock::time_point &finish) -> uint64
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

} // namespace Internal

/*!
 *  ElapsedTimer class
 */
class ElapsedTimer
{
public:
    constexpr ElapsedTimer() noexcept;

    auto start() noexcept -> void;
    auto reset() noexcept -> void;

    template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Miliseconds>
    auto restart() noexcept -> uint64;

    template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Miliseconds>
    auto elapsed() const noexcept -> uint64;

    template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Miliseconds>
    auto hasExpired(uint64 timeout) const noexcept -> bool;

private:    
    std::chrono::steady_clock::time_point m_startPoint {};
};

/*!
 *  ElapsedTimer inline methods
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

template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Miliseconds>
inline auto ElapsedTimer<Metric>::restart() noexcept -> uint64
{
    auto finishPoint = std::chrono::steady_clock::now();
    auto duration = Internal::duration<Metric>(m_startPoint, finishPoint);

    m_startPoint = finishPoint;

    return duration;
}

template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Miliseconds>
inline auto ElapsedTimer<Metric>::elapsed() const noexcept -> uint64
{
    return Internal::duration<Metric>(m_startPoint, std::chrono::steady_clock::now());
}

template<ElapsedTimerMetric Metric = ElapsedTimerMetric::Miliseconds>
inline auto ElapsedTimer<Metric>::hasExpired(uint64 timeout) const noexcept -> bool
{
    return timeout < elapsed<Metric>();
}

} // namespace Calibri

#endif // ELAPSEDTIMER_H
