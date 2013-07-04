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

#ifndef CUNUQUEID_H
#define CUNUQUEID_H

//! Platform Includes
#if defined(_WIN32)
#   include <rpc.h>
#elif defined(__unix__) || defined(__linux__)
#   include <uuid/uuid.h>
#endif

//! Std Includes
#include <string>

//! Project Includes
#include "cdefines.h"

//! Typedefs
typedef uuid_t          c_uniqueid;

void cuniqueid_generate(c_uniqueid &uid);
bool cuniqueid_compare(const c_uniqueid &src, const c_uniqueid &dest);

std::string cuniqueid_to_string(const c_uniqueid &uid);

#endif // CUNUQUEID_H
