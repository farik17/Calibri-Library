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

#ifndef CELAPSEDTIMER_H
#define CELAPSEDTIMER_H

//! Std Includes
#include <chrono>

//! Project Includes
#include "cdefines.h"

class CElapsedTimer
{
public:
    CElapsedTimer();

    enum Metrics : c_uint8 {
        Hours = 1,
        Minutes,
        Seconds,
        Miliseconds,
        Microseconds,
        Nanoseconds
    };

    void start();
    void reset();

    c_uint64 restart(Metrics metrics = Miliseconds);
    c_uint64 elapsed(Metrics metrics = Miliseconds);

    bool isStarted() const;
    bool hasExpired(c_uint64 timeout, Metrics metrics = Miliseconds);

private:
    C_DISABLE_COPY(CElapsedTimer)

    c_uint64 calculateElapsed(Metrics metrics = Miliseconds);

    std::chrono::steady_clock::time_point m_startPoint;

    bool m_started;
};

#endif // CELAPSEDTIMER_H
