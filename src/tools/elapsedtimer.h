#ifndef ELAPSEDTIMER_H
#define ELAPSEDTIMER_H

//! Std Includes
#include <chrono>

//! CalibriLibrary Includes
#include "global/global.h"

namespace Calibri
{

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
    constexpr explicit ElapsedTimer() noexcept;

    void start() noexcept;
    void reset() noexcept;

    auto restart(ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) noexcept -> uint64;
    auto elapsed(ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) const noexcept -> uint64;

    auto hasExpired(uint64 timeout, ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) const noexcept -> bool;

private:
    auto expired(ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) const noexcept -> uint64;

    std::chrono::steady_clock::time_point m_startPoint {};
};

} // namespace Calibri

#endif // ELAPSEDTIMER_H
