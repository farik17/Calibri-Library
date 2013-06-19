#ifndef CFILESYSTEM_H
#define CFILESYSTEM_H

//! Std Includes
#include <vector>

//! Project Includes
#include "cdefines.h"

//! Typedefs
typedef std::vector<std::string>                    cfilesystem_path_tree;

int cfilesystem_create_path(const std::string &path);
int cfilesystem_remove_path(const std::string &path);

cfilesystem_path_tree cfilesystem_parse_path(const std::string &path);

std::string cfilesystem_path_tree_to_string(const cfilesystem_path_tree &path_tree);

void cfilesystem_normalize_path_tree(cfilesystem_path_tree &path_tree);

#endif // CFILESYSTEM_H