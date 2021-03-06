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
#include "cfilesystem.h"

//! Platform Includes
#if defined(_WIN32)
#   include <Windows.h>
#elif defined(__unix__) || defined(__linux__)
#   include <sys/stat.h>
#   include <unistd.h>
#   include <errno.h>
#endif

//! Std Includes
#include <vector>

//! CUtils Includes
#include "cutils.h"

//! Constants
static const std::string path_separator_pattern = "\\/";
static const std::string path_separator =  "/";
static const std::string dot_dot = "..";
static const std::string dot = ".";
static const std::string parent_dir = "../";
static const std::string current_dir = "./";

static inline std::vector<std::string> path_tree_from_string(const std::string &path)
{
    std::vector<std::string> result;

    size_t from = 0;
    auto to = path.find_first_of(path_separator_pattern, from);

    while (to != std::string::npos) {
        result.push_back(path.substr(from, to - from));

        from = to + 1;
        to = path.find_first_of(path_separator_pattern, from + 1);
    }

    to = path.length();

    if (from != to)
        result.push_back(path.substr(from, to - from));

    return result;
}

static inline std::string path_tree_to_string(const std::vector<std::string> &path_tree)
{
    std::string result;

    for (auto path_tree_it = path_tree.cbegin(), path_tree_end = path_tree.cend(); path_tree_it != path_tree_end; ++path_tree_it)
        result += (*path_tree_it) + path_separator;

    return result;
}

static inline void normalize_path_tree(std::vector<std::string> &path_tree)
{
    if (path_tree.size() < 2)
        return;

    auto path_tree_it = path_tree.begin() + 1;

    while (path_tree_it != path_tree.end()) {
        if ((*path_tree_it) == dot_dot) {
            auto prev_path_tree_it = path_tree_it - 1;

            if ((*prev_path_tree_it) != dot_dot) {
                path_tree_it = path_tree.erase(prev_path_tree_it, path_tree_it + 1);

                continue;
            }
        }

        ++path_tree_it;
    }
}

const c_int32 cfilesystem_create_path(const std::string &path)
{
    auto path_tree = path_tree_from_string(path);
    normalize_path_tree(path_tree);

    std::string current_path;

    auto path_tree_it = path_tree.begin();

    while (path_tree_it != path_tree.cend()) {
        current_path += (*path_tree_it) + path_separator;

        if (current_path == parent_dir) {
            path_tree_it = path_tree.erase(path_tree_it);

            continue;
        }

#if defined(_WIN32)
#   if defined(UNICODE)
        if (CreateDirectory(to_wstring(current_path).c_str(), nullptr) == 0) {
#   else
        if (CreateDirectory(current_path.c_str(), nullptr) == 0) {
#   endif
            switch (GetLastError()) {
            case ERROR_ALREADY_EXISTS:
                break;

            default:
                return GetLastError();
            }
        }
#elif defined(__unix__) || defined(__linux__)
        if (mkdir(current_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
            switch (errno) {
            case EEXIST:
                break;

            default:
                return errno;
            }
        }
#else
#   error platform not supported
#endif

        path_tree_it = path_tree.erase(path_tree_it);
    }

    return 0;
}

const c_int32 cfilesystem_remove_path(const std::string &path)
{
    auto path_tree = path_tree_from_string(path);
    normalize_path_tree(path_tree);

    std::string current_path;

    auto path_tree_it = path_tree.rbegin();

    while (path_tree_it != path_tree.crend()) {
        current_path = path_tree_to_string(path_tree);

        if (current_path == parent_dir) {
            path_tree_it = decltype(path_tree_it)(path_tree.erase(path_tree_it.base() - 1));

            continue;
        }

#if defined(_WIN32)
#   if defined(UNICODE)
        if (RemoveDirectory(to_wstring(current_path).c_str()) == 0)
#   else
        if (RemoveDirectory(current_path.c_str()) == 0)
#   endif
            return GetLastError();
#elif defined(__unix__) || defined(__linux__)
        if (rmdir(current_path.c_str()) != 0)
            return errno;
#else
#   error platform not supported
#endif

        path_tree_it = decltype(path_tree_it)(path_tree.erase(path_tree_it.base() - 1));
    }

    return 0;
}
