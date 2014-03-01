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

//! Typedefs
typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

typedef int64 longlong;
typedef uint64 ulonglong;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef long double longdouble;

typedef intptr_t intptr;
typedef uintptr_t uintptr;

#if defined(OS_WINDOWS)
typedef intptr fdptr;
#elif defined(OS_UNIX) || defined(OS_LINUX)
typedef int32 fdptr;
#endif

#endif // GLOBAL_H
