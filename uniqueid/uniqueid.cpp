//! Self Includes
#include "uniqueid.h"

void uniqueid_generate(uniqueid &uid)
{
#if defined(_WIN32)
    UuidCreate(&uid);
#elif defined(__unix__) || defined(__linux__)
    uuid_generate(uid);
#endif
}

bool uniqueid_compare(const uniqueid &src, const uniqueid &dst)
{
#if defined(_WIN32)
    return !memcmp(&src, &dst, sizeof(uniqueid));
#elif defined(__unix__) || defined(__linux__)
    return !uuid_compare(src, dst);
#endif
}

c_platform_string uniqueid_to_string(const uniqueid &uid)
{
#if defined(_WIN32)
#   if defined(UNICODE)
    RPC_WSTR buffer[1];
    UuidToString(&uid, buffer);

    return reinterpret_cast<wchar_t *>(buffer[0]);
#   else
    RPC_CSTR buffer[1];
    UuidToString(&uid, buffer);

    return reinterpret_cast<char *>(buffer[0]);
#   endif
#elif defined(__unix__) || defined(__linux__)
    char buffer[128];
    uuid_unparse(uid, buffer);

    return reinterpret_cast<char *>(buffer);
#endif
}
