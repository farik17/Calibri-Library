#ifndef DATETIME_H
#define DATETIME_H

//! Std Includes
#include <string>
#include <ctime>

#if _MSC_VER
#pragma warning(disable:4996)
#endif

std::string datetime_to_string(const time_t &_time, const std::string &format, bool utc = true);
std::string datetime_to_string(const tm &_time, const std::string &format);

time_t datetime_to_time_t(tm &_time);
tm datetime_to_tm(const time_t &_time, bool utc = true);

tm datetime_get_current_time_local_tm();
tm datetime_get_current_time_utc_tm();

time_t datetime_get_current_time_local_time_t();
time_t datetime_get_current_time_utc_time_t();

void datetime_add_secs(int sec, time_t &_time, bool utc = true);
void datetime_add_mins(int min, time_t &_time, bool utc = true);
void datetime_add_hours(int hours, time_t &_time, bool utc = true);
void datetime_add_days(int days, time_t &_time, bool utc = true);
void datetime_add_months(int months, time_t &_time, bool utc = true);
void datetime_add_years(int years, time_t &_time, bool utc = true);

bool operator ==(tm &src, tm &dst);
bool operator <(tm &src, tm &dst);
bool operator >(tm &src, tm &dst);
bool operator !=(tm &src, tm &dst);

#endif // DATETIME_H
