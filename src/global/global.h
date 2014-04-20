#ifndef GLOBAL_H
#define GLOBAL_H

//! Std Includes
#include <cstdint>

//! LibCalibri Includes
#include "systemdetection.h"
#include "compilerdetection.h"
#include "processordetection.h"

//! Defines
#define CALIBRI_VERSION_VALUE(major, minor, patch) ((major * 100000) + (minor * 1000) + patch)
#define CALIBRI_VERSION CALIBRI_VERSION_VALUE(2, 0, 0)
#define CALIBRI_VERSION_CHECK(major, minor, patch) (CALIBRI_VERSION >= CALIBRI_VERSION_VALUE(major, minor, patch))

//! Aliases
using int8 = char;
using uint8 = unsigned char;
using int16 = short;
using uint16 = unsigned short;
using int32 = int;
using uint32 = unsigned int;
using int64 = long long;
using uint64 = unsigned long long;

using longlong = int64;
using ulonglong = uint64;

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;

using longdouble = long double;

using intptr = intptr_t;
using uintptr = uintptr_t;

#if defined(OS_WINDOWS)
using fdptr = intptr;
#elif defined(OS_UNIX) || defined(OS_LINUX)
using fdptr = int32;
#endif

#endif // GLOBAL_H
