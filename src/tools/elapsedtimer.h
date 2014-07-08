#ifndef ELAPSEDTIMER_H
#define ELAPSEDTIMER_H

//! Std Includes
#include <chrono>

//! CalibriLibrary Includes
#include "global.h"

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

    uint64 restart(ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) noexcept;
    uint64 elapsed(ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) const noexcept;

    bool hasExpired(uint64 timeout, ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) const noexcept;

private:
    uint64 expired(ElapsedTimerMetrics metrics = ElapsedTimerMetrics::Miliseconds) const noexcept;

    std::chrono::steady_clock::time_point m_startPoint {};
};

} // namespace Calibri

#endif // ELAPSEDTIMER_H
