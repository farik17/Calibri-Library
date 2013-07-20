/****************************************************************************
**
** Copyright (c) 2013 Calibri-Software <calibrisoftware@gmail.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
**
****************************************************************************/

//! Self Includes
#include "celapsedtimer.h"

CElapsedTimer::CElapsedTimer()
    : m_started(false)
{
}

void CElapsedTimer::start()
{
    if (m_started)
        return;

    m_started = true;

    m_startPoint = std::chrono::steady_clock::now();
}

void CElapsedTimer::reset()
{
    if (!m_started)
        return;

    m_started = false;
}

const c_uint64 CElapsedTimer::restart(const Metrics metrics)
{
    if (!m_started)
        return 0;

    c_uint64 result = calculateElapsed(metrics);

    m_startPoint = std::chrono::steady_clock::now();

    return result;
}

const c_uint64 CElapsedTimer::elapsed(const Metrics metrics)
{
    if (!m_started)
        return 0;

    return calculateElapsed(metrics);
}

const bool CElapsedTimer::isStarted() const
{
    return m_started;
}

const bool CElapsedTimer::hasExpired(const c_uint64 timeout, const Metrics metrics)
{
    return timeout < elapsed(metrics);
}

const c_uint64 CElapsedTimer::calculateElapsed(const Metrics metrics)
{
    switch (metrics) {
    case Hours:
        return std::chrono::duration_cast<std::chrono::hours>(std::chrono::steady_clock::now() - m_startPoint).count();

    case Minutes:
        return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - m_startPoint).count();

    case Seconds:
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - m_startPoint).count();

    case Miliseconds:
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_startPoint).count();

    case Microseconds:
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - m_startPoint).count();

    case Nanoseconds:
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - m_startPoint).count();

    default:
        break;
    }

    return 0;
}
