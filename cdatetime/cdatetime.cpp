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
#include "cdatetime.h"

std::string cdatetime_to_string(const time_t &_time, const std::string &format, bool utc)
{
    tm tm_time = cdatetime_to_tm(_time, utc);

    char date_buffer[80];
    strftime(date_buffer, 80, format.c_str(), &tm_time);

    return date_buffer;
}

std::string cdatetime_to_string(const time_t &_time)
{
    return ctime(&_time);
}

std::string cdatetime_to_string(const tm &_tm, const std::string &format)
{
    char date_buffer[80];
    strftime(date_buffer, 80, format.c_str(), &_tm);

    return date_buffer;
}

std::string cdatetime_to_string(const tm &_tm)
{
    return asctime(&_tm);
}

time_t cdatetime_to_time_t(tm &_tm)
{
    return mktime(&_tm);
}

tm cdatetime_to_tm(const time_t &_time, bool utc)
{
    if (utc)
        return *gmtime(&_time);
    else
        return *localtime(&_time);
}

tm cdatetime_get_current_time_local_tm()
{
    time_t current_time = time(0);
    return *localtime(&current_time);
}

tm cdatetime_get_current_time_utc_tm()
{
    time_t current_time = time(0);
    return *gmtime(&current_time);
}

time_t cdatetime_get_current_time_local_time_t()
{
    return time(0);
}

time_t cdatetime_get_current_time_utc_time_t()
{
    time_t current_time = time(0);
    return cdatetime_to_time_t(*gmtime(&current_time));
}

void cdatetime_add_secs(c_int32 sec, time_t &_time, bool utc)
{
    tm _tm = cdatetime_to_tm(_time, utc);
    _tm.tm_sec += sec;

    _time = cdatetime_to_time_t(_tm);
}

void cdatetime_add_mins(c_int32 min, time_t &_time, bool utc)
{
    tm _tm = cdatetime_to_tm(_time, utc);
    _tm.tm_min += min;

    _time = cdatetime_to_time_t(_tm);
}

void cdatetime_add_hours(c_int32 hours, time_t &_time, bool utc)
{
    tm _tm = cdatetime_to_tm(_time, utc);
    _tm.tm_hour += hours;

    _time = cdatetime_to_time_t(_tm);
}

void cdatetime_add_days(c_int32 days, time_t &_time, bool utc)
{
    tm _tm = cdatetime_to_tm(_time, utc);
    _tm.tm_mday += days;

    _time = cdatetime_to_time_t(_tm);
}

void cdatetime_add_months(c_int32 months, time_t &_time, bool utc)
{
    tm _tm = cdatetime_to_tm(_time, utc);
    _tm.tm_mon += months;

    _time = cdatetime_to_time_t(_tm);
}

void cdatetime_add_years(c_int32 years, time_t &_time, bool utc)
{
    tm _tm = cdatetime_to_tm(_time, utc);
    _tm.tm_year += years;

    _time = cdatetime_to_time_t(_tm);
}

bool operator ==(tm &src, tm &dst)
{
    return cdatetime_to_time_t(src) == cdatetime_to_time_t(dst);
}

bool operator <(tm &src, tm &dst)
{
    return cdatetime_to_time_t(src) < cdatetime_to_time_t(dst);
}

bool operator >(tm &src, tm &dst)
{
    return cdatetime_to_time_t(src) > cdatetime_to_time_t(dst);
}

bool operator !=(tm &src, tm &dst)
{
    return cdatetime_to_time_t(src) != cdatetime_to_time_t(dst);
}
