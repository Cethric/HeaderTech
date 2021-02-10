//
// Created by rogan2 on 9/02/2021.
//

#ifndef HEADERTECH_SCOPEDPROFILEMARK_INL
#define HEADERTECH_SCOPEDPROFILEMARK_INL

#include <scoped/ScopedProfileMark.h>
#include <scoped/ScopedProfiler.h>

namespace HeaderTech::Profiler::Scoped {
    ScopedCpuProfiler::ScopedCpuProfiler(
            const char *name, std::uint64_t hash, const char *function, const char *file, int line,
            Types::ScopedProfilerFlags flags
    ) noexcept
    { ScopedProfiler::GetProfiler()->BeginCpuProfile(name, hash, function, file, line, flags); }

    ScopedCpuProfiler::~ScopedCpuProfiler() noexcept
    { ScopedProfiler::GetProfiler()->EndCpuProfile(); }

}

#endif //HEADERTECH_SCOPEDPROFILEMARK_INL
