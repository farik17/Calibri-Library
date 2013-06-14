#ifndef CUTILS_H
#define CUTILS_H

//! Std Includes
#include <string>

std::string to_hex(const unsigned char *data, size_t len);

std::string str_left(char c, const std::string &str);
std::string str_right(char c, const std::string &str);
std::string str_take_left(char c, std::string &str);
std::string str_take_right(char c, std::string &str);
bool str_contains(char c, const std::string &str);

#endif // CUTILS_H
