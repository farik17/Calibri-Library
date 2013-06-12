//! Self Includes
#include "utils.h"

//! Std Includes
#include <sstream>
#include <iomanip>

std::string toHex(const unsigned char *data, size_t len)
{
    std::stringstream stream;
    for (size_t ix = 0; ix < len; ++ix)
        stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[ix]);

    return stream.str();
}

std::string str_left(char c, const std::string &line)
{
    size_t pos = line.find(c);

    if (pos == std::string::npos)
        return std::string();

    return line.substr(0, pos);
}

std::string str_right(char c, const std::string &line)
{
    size_t pos = line.find(c);

    if (pos == std::string::npos)
        return std::string();

    return line.substr(pos + 1);
}

std::string str_take_left(char c, std::string &line)
{
    size_t pos = line.find(c);

    if (pos == std::string::npos)
        return std::string();

    std::string result = line.substr(0, pos);

    line.erase(0, pos + 1);

    return result;
}

std::string str_take_right(char c, std::string &line)
{
    size_t pos = line.find(c);

    if (pos == std::string::npos)
        return std::string();

    std::string result = line.substr(pos);

    line.erase(pos);

    return result;
}

bool str_contains(char c, const std::string &line)
{
    size_t pos = line.find(c);

    if (pos == std::string::npos)
        return false;

    return true;
}
