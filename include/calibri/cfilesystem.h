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

#ifndef CFILESYSTEM_H
#define CFILESYSTEM_H

//! Std Includes
#include <string>
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
