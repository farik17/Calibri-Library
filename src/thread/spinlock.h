#ifndef SPINLOCK_H
#define SPINLOCK_H

//! Std includes
#include <atomic>
#include <thread>

//! Calibri-Library includes
#include "global/global.h"
#include "tools/disablecopyable.h"

#if defined(CC_GNU) && defined(__SSE__)
//! Platform includes
#   include <x86intrin.h>

//! Defines
#   define SMT_PAUSE _mm_pause();
#else
//! Defines
#   define SMT_PAUSE
#endif

namespace Calibri {

namespace Internal {

inline void yield(uint32 spin) noexcept
{
    if (spin < 4) {
    } else if (spin < 16) {
        SMT_PAUSE
    } else if (spin < 32) {
        std::this_thread::yield();
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

} // end namespace Internal

/*!
 *  SpinLock class
 */
class SpinLock : private DisableCopyable
{
public:
    virtual ~SpinLock() noexcept;

    auto lock() noexcept -> void;
    auto unlock() noexcept -> void;

    auto tryLock() noexcept -> bool;

private:
    std::atomic_flag m_atomicFlag { ATOMIC_FLAG_INIT };
};

/*!
 *  SpinLock inline methods
 */
inline SpinLock::~SpinLock() noexcept
{
    unlock();
}

inline auto SpinLock::lock() noexcept -> void
{
    for (uint32 spin = 0; !tryLock(); ++spin)
        Internal::yield(spin);
}

inline auto SpinLock::unlock() noexcept -> void
{
    m_atomicFlag.clear(std::memory_order_release);
}

inline auto SpinLock::tryLock() noexcept -> bool
{
    return !m_atomicFlag.test_and_set(std::memory_order_acquire);
}

} // end namespace Calibri

#endif // SPINLOCK_H
