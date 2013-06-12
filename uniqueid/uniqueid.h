#ifndef UUID_H
#define UUID_H

//! Platform Includes
#if defined(_WIN32)
#   include <rpc.h>
#elif defined(__unix__) || defined(__linux__)
#   include <uuid/uuid.h>
#endif

//! Project Includes
#include "defines.h"

//! Typedefs
typedef uuid_t          uniqueid;

void uniqueid_generate(uniqueid &uid);
bool uniqueid_compare(const uniqueid &src, const uniqueid &dst);

c_platform_string uniqueid_to_string(const uniqueid &uid);

#endif // UUID_H
