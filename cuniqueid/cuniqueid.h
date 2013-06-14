#ifndef CUNUQUEID_H
#define CUNUQUEID_H

//! Platform Includes
#if defined(_WIN32)
#   include <rpc.h>
#elif defined(__unix__) || defined(__linux__)
#   include <uuid/uuid.h>
#endif

//! Project Includes
#include "cdefines.h"

//! Typedefs
typedef uuid_t          cuniqueid;

void cuniqueid_generate(cuniqueid &uid);
bool cuniqueid_compare(const cuniqueid &src, const cuniqueid &dst);

c_platform_string cuniqueid_to_string(const cuniqueid &uid);

#endif // CUNUQUEID_H
