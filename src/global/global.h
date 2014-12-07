#ifndef GLOBAL_H
#define GLOBAL_H

//! Std includes
#include <cstdint>

//! Calibri-Library includes
#include "systemdetection.h"
#include "compilerdetection.h"
#include "processordetection.h"

//! Aliases
using wchar = wchar_t;
using longlong = long long;
using int8 = char;
using int16 = short;
using int32 = int;
using int64 = longlong;
using intptr = intptr_t;

using uchar = unsigned char;
using uwchar = unsigned wchar_t;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using ulonglong = unsigned long long;
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = ulonglong;
using uintptr = uintptr_t;

using longdouble = long double;

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
