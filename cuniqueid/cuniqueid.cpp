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
