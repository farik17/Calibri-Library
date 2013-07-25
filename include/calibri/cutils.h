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

#ifndef CUTILS_H
#define CUTILS_H

//! Std Includes
#include <string>

//! Project Includes
#include "cdefines.h"

const bool lexical_cast(const std::string &data, c_int8 &out);
const bool lexical_cast(const std::string &data, c_int16 &out);
const bool lexical_cast(const std::string &data, c_int32 &out);
const bool lexical_cast(const std::string &data, c_int64 &out);
const bool lexical_cast(const std::string &data, c_long &out);
const bool lexical_cast(const std::string &data, c_uint8 &out);
const bool lexical_cast(const std::string &data, c_uint16 &out);
const bool lexical_cast(const std::string &data, c_uint32 &out);
const bool lexical_cast(const std::string &data, c_uint64 &out);
const bool lexical_cast(const std::string &data, c_ulong &out);
const bool lexical_cast(const std::string &data, bool &out);
const bool lexical_cast(const std::string &data, float &out);
const bool lexical_cast(const std::string &data, double &out);
const bool lexical_cast(const std::string &data, long double &out);
const bool lexical_cast(const std::string &data, std::wstring &out);
const bool lexical_cast(const c_int8 data, std::string &out);
const bool lexical_cast(const c_int16 data, std::string &out);
const bool lexical_cast(const c_int32 data, std::string &out);
const bool lexical_cast(const c_int64 data, std::string &out);
const bool lexical_cast(const c_long data, std::string &out);
const bool lexical_cast(const c_uint8 data, std::string &out);
const bool lexical_cast(const c_uint16 data, std::string &out);
const bool lexical_cast(const c_uint32 data, std::string &out);
const bool lexical_cast(const c_uint64 data, std::string &out);
const bool lexical_cast(const c_ulong data, std::string &out);
const bool lexical_cast(const bool data, std::string &out);
const bool lexical_cast(const float data, std::string &out);
const bool lexical_cast(const double data, std::string &out);
const bool lexical_cast(const long double data, std::string &out);
const bool lexical_cast(const std::string &data, std::string &out);
const bool lexical_cast(const std::wstring &data, std::string &out);

const bool str_contains(const char c, const std::string &str);

std::string str_left(const char c, const std::string &str);
std::string str_right(const char c, const std::string &str);
std::string str_take_left(const char c, std::string &str);
std::string str_take_right(const char c, std::string &str);

std::string to_hex(const unsigned char *data, const size_t len);

std::string to_string(const std::wstring &data);
std::string to_string(const wchar_t *data);

std::wstring to_wstring(const std::string &data);
std::wstring to_wstring(const char *data);

#endif // CUTILS_H
