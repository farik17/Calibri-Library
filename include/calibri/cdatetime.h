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

std::string cdatetime_to_string(const time_t &_time, const std::string &format, bool utc = true);
std::string cdatetime_to_string(const time_t &_time);
std::string cdatetime_to_string(const tm &_tm, const std::string &format);
std::string cdatetime_to_string(const tm &_tm);

time_t cdatetime_to_time_t(tm &_tm);
tm cdatetime_to_tm(const time_t &_time, bool utc = true);

tm cdatetime_get_current_time_local_tm();
tm cdatetime_get_current_time_utc_tm();

time_t cdatetime_get_current_time_local_time_t();
time_t cdatetime_get_current_time_utc_time_t();

void cdatetime_add_secs(c_int32 sec, time_t &_time, bool utc = true);
void cdatetime_add_mins(c_int32 min, time_t &_time, bool utc = true);
void cdatetime_add_hours(c_int32 hours, time_t &_time, bool utc = true);
void cdatetime_add_days(c_int32 days, time_t &_time, bool utc = true);
void cdatetime_add_months(c_int32 months, time_t &_time, bool utc = true);
void cdatetime_add_years(c_int32 years, time_t &_time, bool utc = true);

bool operator ==(tm &src, tm &dst);
bool operator <(tm &src, tm &dst);
bool operator >(tm &src, tm &dst);
bool operator !=(tm &src, tm &dst);

#endif // CDATETIME_H
