//
// Created by rogan2 on 5/11/2020.
//

#ifndef HEADERTECH_PROFILERINCLUDES_H
#define HEADERTECH_PROFILERINCLUDES_H


#include <scoped/ScopedProfilerIncludes.h>

#if defined(HEADERTECH_PROFILER_IMPL) && DEFINE_IMPLEMENTATION == 1

#endif

namespace HeaderTech::Profiler {
    int ProfilerVersion();
}

#endif //HEADERTECH_PROFILERINCLUDES_H
