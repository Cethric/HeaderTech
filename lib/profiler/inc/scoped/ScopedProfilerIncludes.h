//
// Created by rogan2 on 9/02/2021.
//

#ifndef HEADERTECH_SCOPEDPROFILERINCLUDES_H
#define HEADERTECH_SCOPEDPROFILERINCLUDES_H

#include <scoped/ScopedProfiler.h>
#include <scoped/ScopedProfileMark.h>

#if defined(HEADERTECH_PROFILER_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <scoped/ScopedProfiler.inl>
#include <scoped/ScopedProfileMark.inl>

#endif

#endif //HEADERTECH_SCOPEDPROFILERINCLUDES_H
