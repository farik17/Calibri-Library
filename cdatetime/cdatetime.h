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

#ifndef CDATETIME_H
#define CDATETIME_H

//! Std Includes
#include <string>
#include <ctime>

//! Project Includes
#include "cdefines.h"

#if _MSC_VER
#pragma warning(disable:4996)
#endif

std::string cdatetime_to_string(const time_t &_time, const std::string &format, const bool utc = true);
std::string cdatetime_to_string(const tm &_tm, const std::string &format);

const time_t cdatetime_to_time_t(tm &_tm);
const tm cdatetime_to_tm(const time_t &_time, const bool utc = true);

const tm cdatetime_get_current_time_local_tm();
const tm cdatetime_get_current_time_utc_tm();

const time_t cdatetime_get_current_time_local_time_t();
const time_t cdatetime_get_current_time_utc_time_t();

void cdatetime_add_secs(const c_int32 sec, time_t &_time, const bool utc = true);
void cdatetime_add_mins(const c_int32 min, time_t &_time, const bool utc = true);
void cdatetime_add_hours(const c_int32 hours, time_t &_time, const bool utc = true);
void cdatetime_add_days(const c_int32 days, time_t &_time, const bool utc = true);
void cdatetime_add_months(const c_int32 months, time_t &_time, const bool utc = true);
void cdatetime_add_years(const c_int32 years, time_t &_time, const bool utc = true);

bool operator ==(tm &src, tm &dest);
bool operator <(tm &src, tm &dest);
bool operator >(tm &src, tm &dest);
bool operator !=(tm &src, tm &dest);

#endif // CDATETIME_H
