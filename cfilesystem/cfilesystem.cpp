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

//! CFilesystem defines
#if defined(_WIN32) && defined(UNICODE)
#   define PATH_SEPARATOR_PATTERN       L"\\/"
#   define PATH_SEPARATOR               L"/"
#   define DOT_DOT                      L".."
#   define DOT                          "."
#   define PARENT_DIR                   L"../"
#   define CURRENT_DIR                  L"./"
#else
#   define PATH_SEPARATOR_PATTERN       "\\/"
#   define PATH_SEPARATOR               "/"
#   define DOT_DOT                      ".."
#   define DOT                          "."
#   define PARENT_DIR                   "../"
#   define CURRENT_DIR                  "./"
#endif

int cfilesystem_create_path(const c_platform_string &path)
{
    cfilesystem_path_tree path_tree = cfilesystem_parse_path(path);
    cfilesystem_normalize_path_tree(path_tree);

    c_platform_string current_path;

    auto it = path_tree.begin();
    while (it != path_tree.cend()) {
        current_path += (*it) + PATH_SEPARATOR;

        if (current_path == PARENT_DIR) {
            it = path_tree.erase(it);
            continue;
        }

#if defined(_WIN32)
        if (CreateDirectory(current_path.c_str(), nullptr) == 0) {
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

        it = path_tree.erase(it);
    }

    return 0;
}

int cfilesystem_remove_path(const c_platform_string &path)
{
    cfilesystem_path_tree path_tree = cfilesystem_parse_path(path);
    cfilesystem_normalize_path_tree(path_tree);

    c_platform_string current_path;

    auto it = path_tree.rbegin();
    while (it != path_tree.crend()) {
        current_path = cfilesystem_path_tree_to_string(path_tree);

        if (current_path == PARENT_DIR) {
            it = decltype(it)(path_tree.erase(it.base() - 1));
            continue;
        }

#if defined(_WIN32)
        if (RemoveDirectory(current_path.c_str()) == 0)
            return GetLastError();
#elif defined(__unix__) || defined(__linux__)
        if (rmdir(current_path.c_str()) != 0)
            return errno;
#else
#   error platform not supported
#endif

        it = decltype(it)(path_tree.erase(it.base() - 1));
    }

    return 0;
}

cfilesystem_path_tree cfilesystem_parse_path(const c_platform_string &path)
{
    cfilesystem_path_tree path_tree;

    size_t from = 0;
    size_t to = path.find_first_of(PATH_SEPARATOR_PATTERN, from);

    while (to != std::string::npos) {
        path_tree.push_back(path.substr(from, to - from));

        from = to + 1;
        to = path.find_first_of(PATH_SEPARATOR_PATTERN, from + 1);
    }

    to = path.length();

    if (from != to)
        path_tree.push_back(path.substr(from, to - from));

    return path_tree;
}

c_platform_string cfilesystem_path_tree_to_string(const cfilesystem_path_tree &path_tree)
{
    c_platform_string path;

    for (size_t ix = 0; ix < path_tree.size(); ++ix)
        path += path_tree[ix] + PATH_SEPARATOR;

    return path;
}

void cfilesystem_normalize_path_tree(cfilesystem_path_tree &path_tree)
{
    if (path_tree.size() < 2)
        return;

    auto it = path_tree.begin() + 1;
    while (it != path_tree.end()) {
        if ((*it) == DOT_DOT) {
            auto prev_it = it - 1;
            if ((*prev_it) != DOT_DOT) {
                it = path_tree.erase(prev_it, it + 1);
                continue;
            }
        }
        ++it;
    }
}
