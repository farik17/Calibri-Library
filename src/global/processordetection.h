#ifndef PROCESSORDETECTION_H
#define PROCESSORDETECTION_H

//! Defines
/*!
 *  The processor system, must be one of: (CPU_x)
 *
 *   X86        - X86 family, 32-bit
 *   X86_64     - X86 family, 64-bit
 *   IA64       - Itanium (IA-64) family, no revisions or variants
 */
#if defined(__i386__) || defined(_M_IX86)
#   define CPU_X86
#elif defined(__x86_64__) || defined(_M_X64)
#   define CPU_X86_64
#elif defined(__ia64__) || defined(_M_IA64)
#   define CPU_IA64
#else
#   error "Calibri does not support current processor"
#endif

#endif // PROCESSORDETECTION_H
