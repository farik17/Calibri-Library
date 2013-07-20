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

//! Std Includes
#include <iostream>

//! CUtils Includes
#include "cutils.h"

const std::string cuniqueid_to_string(const c_uniqueid &uid)
{
#if defined(_WIN32)
#   if defined(UNICODE)
    c_uint16 *buffer = nullptr;

    if (UuidToString(&uid, &buffer) == RPC_S_OUT_OF_MEMORY) {
#       if defined(DEBUG)
        C_DEBUG("needed memory is not available");
#       endif
        return std::string();
    }
    return to_string(reinterpret_cast<wchar_t *>(buffer));
#   else
    c_uint8 *buffer = nullptr;

    if (UuidToString(&uid, &buffer) == RPC_S_OUT_OF_MEMORY) {
#       if defined(DEBUG)
        C_DEBUG("needed memory is not available");
#       endif
        return std::string();
    }
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

const c_int32 cuniqueid_generate(c_uniqueid &uid)
{
#if defined(_WIN32)
#   if defined(DEBUG)
    int result = UuidCreate(&uid);
    switch (result) {
    case RPC_S_UUID_LOCAL_ONLY:
        C_DEBUG("c_uniqueid is guaranteed to be unique to this computer only");
        break;

    case RPC_S_UUID_NO_ADDRESS:
        C_DEBUG("cannot get Ethernet or token-ring hardware address for this computer");
        break;

    default:
        break;
    }
    return result;
#   else
    return UuidCreate(&uid);
#   endif
#elif defined(__unix__) || defined(__linux__)
    uuid_generate(uid);
    return 0;
#else
#   error platform not supported
#endif
}

const bool cuniqueid_compare(const c_uniqueid &src, const c_uniqueid &dest)
{
#if defined(_WIN32)
    return !memcmp(&src, &dest, sizeof(c_uniqueid));
#elif defined(__unix__) || defined(__linux__)
    return !uuid_compare(src, dest);
#else
#   error platform not supported
#endif
}
