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
#include "cutils.h"

//! Std Includes
#include <sstream>
#include <iomanip>
#include <cstdlib>

#if _MSC_VER
#pragma warning(disable:4996)
#endif

const bool lexical_cast(const std::string &data, c_int8 &out)
{
    if (data.empty())
        return false;

    out = static_cast<c_int8>(std::stoi(data));

    return true;
}

const bool lexical_cast(const std::string &data, c_int16 &out)
{
    if (data.empty())
        return false;

    out = static_cast<c_int16>(std::stoi(data));

    return true;
}

const bool lexical_cast(const std::string &data, c_int32 &out)
{
    if (data.empty())
        return false;

    out = std::stoi(data);

    return true;
}

const bool lexical_cast(const std::string &data, c_int64 &out)
{
    if (data.empty())
        return false;

    out = std::stoll(data);

    return true;
}

const bool lexical_cast(const std::string &data, c_long &out)
{
    if (data.empty())
        return false;

    out = std::stol(data);

    return true;
}

const bool lexical_cast(const std::string &data, c_uint8 &out)
{
    if (data.empty())
        return false;

    out = static_cast<c_uint8>(std::stoul(data));

    return true;
}

const bool lexical_cast(const std::string &data, c_uint16 &out)
{
    if (data.empty())
        return false;

    out = static_cast<c_uint16>(std::stoul(data));

    return true;
}

const bool lexical_cast(const std::string &data, c_uint32 &out)
{
    if (data.empty())
        return false;

    out = std::stoul(data);

    return true;
}

const bool lexical_cast(const std::string &data, c_uint64 &out)
{
    if (data.empty())
        return false;

    out = std::stoull(data);

    return true;
}

const bool lexical_cast(const std::string &data, c_ulong &out)
{
    if (data.empty())
        return false;

    out = std::stoul(data);

    return true;
}

const bool lexical_cast(const std::string &data, bool &out)
{
    if (data.empty())
        return false;

    out = std::stoi(data) != 0;

    return true;
}

const bool lexical_cast(const std::string &data, float &out)
{
    if (data.empty())
        return false;

    out = std::stof(data);

    return true;
}

const bool lexical_cast(const std::string &data, double &out)
{
    if (data.empty())
        return false;

    out = std::stod(data);

    return true;
}

const bool lexical_cast(const std::string &data, long double &out)
{
    if (data.empty())
        return false;

    out = std::stold(data);

    return true;
}

const bool lexical_cast(const std::string &data, std::wstring &out)
{
    out = to_wstring(data);

    return true;
}

const bool lexical_cast(const c_int8 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const c_int16 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const c_int32 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const c_int64 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const c_long data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const c_uint8 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const c_uint16 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const c_uint32 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const c_uint64 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const c_ulong data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const bool data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const float data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const double data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const long double data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

const bool lexical_cast(const std::string &data, std::string &out)
{
    out = data;

    return true;
}

const bool lexical_cast(const std::wstring &data, std::string &out)
{
    out = to_string(data);

    return true;
}

const bool str_contains(const char c, const std::string &str)
{
    const auto pos = str.find(c);

    if (pos == std::string::npos)
        return false;

    return true;
}

std::string str_left(const char c, const std::string &str)
{
    const auto pos = str.find(c);

    if (pos == std::string::npos)
        return std::string();

    return str.substr(0, pos);
}

std::string str_right(const char c, const std::string &str)
{
    const auto pos = str.find(c);

    if (pos == std::string::npos)
        return std::string();

    return str.substr(pos + 1);
}

std::string str_take_left(const char c, std::string &str)
{
    const auto pos = str.find(c);

    if (pos == std::string::npos)
        return std::string();

    const auto result = str.substr(0, pos);

    str.erase(0, pos + 1);

    return result;
}

std::string str_take_right(const char c, std::string &str)
{
    const auto pos = str.find(c);

    if (pos == std::string::npos)
        return std::string();

    const auto result = str.substr(pos);

    str.erase(pos);

    return result;
}

std::string to_hex(const unsigned char *data, const size_t len)
{
    std::stringstream stream;
    for (size_t ix = 0; ix < len; ++ix)
        stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<c_int32>(data[ix]);

    return stream.str();
}

std::string to_string(const std::wstring &data)
{
    const auto in_len = data.length();
    size_t out_len = 0;
    auto *buffer = new char[in_len];

    out_len = wcstombs(buffer, data.c_str(), in_len);

    std::string result(buffer, out_len);

    delete[] buffer;

    return result;
}

std::string to_string(const wchar_t *data)
{
    const auto in_len = std::char_traits<wchar_t>::length(data);
    size_t out_len = 0;
    auto *buffer = new char[in_len];

    out_len = wcstombs(buffer, data, in_len);

    std::string result(buffer, out_len);

    delete[] buffer;

    return result;
}

std::wstring to_wstring(const std::string &data)
{
    const auto in_len = data.length();
    size_t out_len = 0;
    auto *buffer = new wchar_t[in_len];

    out_len = mbstowcs(buffer, data.c_str(), in_len);

    std::wstring result(buffer, out_len);

    delete[] buffer;

    return result;
}

std::wstring to_wstring(const char *data)
{
    const auto in_len = std::char_traits<char>::length(data);
    size_t out_len = 0;
    auto *buffer = new wchar_t[in_len];

    out_len = mbstowcs(buffer, data, in_len);

    std::wstring result(buffer, out_len);

    delete[] buffer;

    return result;
}
