//! Self Includes
#include "cutils.h"

//! Std Includes
#include <sstream>
#include <iomanip>

bool lexical_cast(const std::string &data, c_int8 &out)
{
    if (data.empty())
        return false;

    out = static_cast<c_int8>(std::stoi(data));

    return true;
}

bool lexical_cast(const std::string &data, c_int16 &out)
{
    if (data.empty())
        return false;

    out = static_cast<c_int16>(std::stoi(data));

    return true;
}

bool lexical_cast(const std::string &data, c_int32 &out)
{
    if (data.empty())
        return false;

    out = std::stoi(data);

    return true;
}

bool lexical_cast(const std::string &data, c_int64 &out)
{
    if (data.empty())
        return false;

    out = std::stoll(data);

    return true;
}

bool lexical_cast(const std::string &data, c_long &out)
{
    if (data.empty())
        return false;

    out = std::stol(data);

    return true;
}

bool lexical_cast(const std::string &data, c_uint8 &out)
{
    if (data.empty())
        return false;

    out = static_cast<c_uint8>(std::stoul(data));

    return true;
}

bool lexical_cast(const std::string &data, c_uint16 &out)
{
    if (data.empty())
        return false;

    out = static_cast<c_uint16>(std::stoul(data));

    return true;
}

bool lexical_cast(const std::string &data, c_uint32 &out)
{
    if (data.empty())
        return false;

    out = std::stoul(data);

    return true;
}

bool lexical_cast(const std::string &data, c_uint64 &out)
{
    if (data.empty())
        return false;

    out = std::stoull(data);

    return true;
}

bool lexical_cast(const std::string &data, c_ulong &out)
{
    if (data.empty())
        return false;

    out = std::stoul(data);

    return true;
}

bool lexical_cast(const std::string &data, bool &out)
{
    if (data.empty())
        return false;

    out = std::stoi(data) != 0;

    return true;
}

bool lexical_cast(const std::string &data, float &out)
{
    if (data.empty())
        return false;

    out = std::stof(data);

    return true;
}

bool lexical_cast(const std::string &data, double &out)
{
    if (data.empty())
        return false;

    out = std::stod(data);

    return true;
}

bool lexical_cast(const std::string &data, long double &out)
{
    if (data.empty())
        return false;

    out = std::stold(data);

    return true;
}

bool lexical_cast(c_int8 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(c_int16 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(c_int32 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(c_int64 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(c_long data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(c_uint8 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(c_uint16 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(c_uint32 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(c_uint64 data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(c_ulong data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(bool data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(float data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(double data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(long double data, std::string &out)
{
    out = std::to_string(data);

    return true;
}

bool lexical_cast(const std::string &data, std::string &out)
{
    out = data;

    return true;
}

std::string to_hex(const unsigned char *data, size_t len)
{
    std::stringstream stream;
    for (size_t ix = 0; ix < len; ++ix)
        stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[ix]);

    return stream.str();
}

std::string str_left(char c, const std::string &str)
{
    size_t pos = str.find(c);

    if (pos == std::string::npos)
        return std::string();

    return str.substr(0, pos);
}

std::string str_right(char c, const std::string &str)
{
    size_t pos = str.find(c);

    if (pos == std::string::npos)
        return std::string();

    return str.substr(pos + 1);
}

std::string str_take_left(char c, std::string &str)
{
    size_t pos = str.find(c);

    if (pos == std::string::npos)
        return std::string();

    std::string result = str.substr(0, pos);

    str.erase(0, pos + 1);

    return result;
}

std::string str_take_right(char c, std::string &str)
{
    size_t pos = str.find(c);

    if (pos == std::string::npos)
        return std::string();

    std::string result = str.substr(pos);

    str.erase(pos);

    return result;
}

bool str_contains(char c, const std::string &str)
{
    size_t pos = str.find(c);

    if (pos == std::string::npos)
        return false;

    return true;
}
