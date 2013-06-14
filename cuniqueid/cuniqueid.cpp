//! Self Includes
#include "cuniqueid.h"

void cuniqueid_generate(cuniqueid &uid)
{
#if defined(_WIN32)
    UuidCreate(&uid);
#elif defined(__unix__) || defined(__linux__)
    uuid_generate(uid);
#endif
}

bool cuniqueid_compare(const cuniqueid &src, const cuniqueid &dst)
{
#if defined(_WIN32)
    return !memcmp(&src, &dst, sizeof(cuniqueid));
#elif defined(__unix__) || defined(__linux__)
    return !uuid_compare(src, dst);
#endif
}

c_platform_string cuniqueid_to_string(const cuniqueid &uid)
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
