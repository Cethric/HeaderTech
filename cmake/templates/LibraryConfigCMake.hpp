//
// Created by rogan2 on 5/04/2021.
//

#ifndef HEADERTECH_@Target@_HPP
#define HEADERTECH_@Target@_HPP

#include <@Target@/Exports.h>
#include <@Target@/Version.hpp>

#if defined(__ANDROID__)
#define PLATFORM_IS_ANDROID 1
#endif

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
#define PLATFORM_IS_BSD 1
#endif

#if defined(__CYGWIN__)
#define PLATFORM_IS_CYGWIN 1
#endif

#if defined(__gnu_linux__) || defined(__linux__)
#define PLATFORM_IS_LINUX 1
#endif

#if defined(__APPLE__) && defined(__MACH__)
#define PLATFORM_IS_APPLE 1
#endif

#if defined(__unix__) || defined(__unix)
#define PLATFORM_IS_UNIX 1
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__)
#define PLATFORM_IS_WINDOWS 1
#endif

#if defined(__clang__)
#define COMPILED_WITH_CLANG 1
#endif

#if defined(__GNUC__)
#define COMPILED_WITH_GNUC 1
#endif

#if defined(__llvm__)
#define COMPILED_WITH_LLVM 1
#endif

#if defined(_MSC_VER)
#define COMPILED_WITH_MSVC 1
#endif

#if defined(__MINGW32__)
#define PLATFORM_IS_MINGW 1
#define COMPILED_WITH_MINGW_32 1
#endif

#if defined(__MINGW64__)
#define PLATFORM_IS_MINGW 1
#define COMPILED_WITH_MINGW_64 1
#endif

#endif // HEADERTECH_@Target@_HPP
