//! Self Includes
#include "elapsedtimer.h"

namespace Calibri {

auto ElapsedTimer::expired(ElapsedTimerMetrics metrics) const noexcept -> uint64
{
    switch (metrics) {
    case ElapsedTimerMetrics::Hours:
        return std::chrono::duration_cast<std::chrono::hours>(std::chrono::steady_clock::now() - m_startPoint).count();

    case ElapsedTimerMetrics::Minutes:
        return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - m_startPoint).count();

    case ElapsedTimerMetrics::Seconds:
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - m_startPoint).count();

    case ElapsedTimerMetrics::Miliseconds:
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_startPoint).count();

    case ElapsedTimerMetrics::Microseconds:
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - m_startPoint).count();

    case ElapsedTimerMetrics::Nanoseconds:
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - m_startPoint).count();

    default:
        return {};
    }
}

} // namespace Calibri
