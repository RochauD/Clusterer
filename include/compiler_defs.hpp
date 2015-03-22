#ifndef _COMMON_UTILS_COMPILER_DEFS_H
#define _COMMON_UTILS_COMPILER_DEFS_H

/**
 * @brief Compiler Utilities
 * @file compiler_defs.hpp
 *
 */

#define DISALLOW_CONSTRUCTION(TypeName)                                     \
    TypeName() = delete;                                                    \
    TypeName(const TypeName&) = delete;                                     \
    TypeName(const TypeName&&) = delete

#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                  \
    TypeName(const TypeName&) = delete;                                     \
    TypeName& operator=(const TypeName&) = delete

#endif  // _COMMON_UTILS_COMPILER_DEFS_H
