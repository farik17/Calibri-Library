#ifndef FILESYSTEM_H
#define FILESYSTEM_H

//! Std Includes
#include <vector>

//! Project Includes
#include "defines.h"

//! Typedefs
typedef std::vector<c_platform_string>              filesystem_path_tree;

int filesystem_create_path(const c_platform_string &path);
int filesystem_remove_path(const c_platform_string &path);

filesystem_path_tree filesystem_parse_path(const c_platform_string &path);

c_platform_string filesystem_path_tree_to_string(const filesystem_path_tree &path_tree);

void filesystem_normalize_path_tree(filesystem_path_tree &path_tree);

#endif // FILESYSTEM_H
