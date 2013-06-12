#ifndef UTILS_H
#define UTILS_H

//! Std Includes
#include <string>

std::string toHex(const unsigned char *data, size_t len);

std::string str_left(char c, const std::string &line);
std::string str_right(char c, const std::string &line);
std::string str_take_left(char c, std::string &line);
std::string str_take_right(char c, std::string &line);
bool str_contains(char c, const std::string &line);

#endif // UTILS_H
