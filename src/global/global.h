#ifndef GLOBAL_H
#define GLOBAL_H

//! Std includes
#include <cstdint>

//! Calibri-Library includes
#include "systemdetection.h"
#include "compilerdetection.h"
#include "processordetection.h"

//! Aliases
using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using intmax = intmax_t;
using intptr = intptr_t;
using longlong = long long;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;
using uintmax = uintmax_t;
using uintptr = uintptr_t;
using ulonglong = unsigned long long;

using longdouble = long double;

using char16 = char16_t;
using char32 = char32_t;

using wchar = wchar_t;

using uchar = unsigned char;
using uwchar = unsigned wchar_t;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;

using sizeinfo = size_t;

#if defined(OS_WINDOWS)
using fdptr = intptr;
#elif defined(OS_UNIX) || defined(OS_LINUX)
using fdptr = int32;
#endif

//! Defines
#define VERSION_VALUE(major, minor, patch) (major * 100000 + minor * 1000 + patch)
#define VERSION VERSION_VALUE(2, 0, 0)
#define VERSION_CHECK(major, minor, patch) (VERSION >= VERSION_VALUE(major, minor, patch))

#endif // GLOBAL_H
