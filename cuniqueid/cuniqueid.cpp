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
#include "cuniqueid.h"

//! CUtils Includes
#include "cutils.h"

void cuniqueid_generate(cuniqueid &uid)
{
#if defined(_WIN32)
    UuidCreate(&uid);
#elif defined(__unix__) || defined(__linux__)
    uuid_generate(uid);
#else
#   error platform not supported
#endif
}

bool cuniqueid_compare(const cuniqueid &src, const cuniqueid &dst)
{
#if defined(_WIN32)
    return !memcmp(&src, &dst, sizeof(cuniqueid));
#elif defined(__unix__) || defined(__linux__)
    return !uuid_compare(src, dst);
#else
#   error platform not supported
#endif
}

std::string cuniqueid_to_string(const cuniqueid &uid)
{
#if defined(_WIN32)
#   if defined(UNICODE)
    c_uint16 *buffer;
    UuidToString(&uid, &buffer);

    return to_string(reinterpret_cast<wchar_t *>(buffer));
#   else
    c_uint8 *buffer;
    UuidToString(&uid, &buffer);

    return reinterpret_cast<char *>(buffer);
#   endif
#elif defined(__unix__) || defined(__linux__)
    char buffer[128];
    uuid_unparse(uid, buffer);

    return buffer;
#else
#   error platform not supported
#endif
}
