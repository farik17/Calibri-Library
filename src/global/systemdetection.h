#ifndef SYSTEMDETECTION_H
#define SYSTEMDETECTION_H

//! Defines
/*!
 *  The operation system, must be one of: (OS_x)
 *
 *   WINDOWS    - Windows
 *   LINUX      - Linux
 *   UNIX       - Any UNIX BSD/SYSV system
 */
#if defined(_WIN32)
#   define OS_WINDOWS
#elif defined(__linux__)
#   define OS_LINUX
#elif defined(__unix__)
#   define OS_UNIX
#else
#   error "Calibri does not support current operation system"
#endif

#endif // SYSTEMDETECTION_H
