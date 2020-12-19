//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_SCOPEDPROFILEMARK_H
#define HEADERTECH_SCOPEDPROFILEMARK_H

#include <scoped/ScopedProfiler.h>
#include <ProfilerTypes.h>
#include <GLFW/glfw3.h>
#include <string>
#include <utility>
#include <ctti/type_id.hpp>

namespace HeaderTech::Profiler {
    class ScopedCpuProfiler final {
    public:
        inline ScopedCpuProfiler(
                const char *name,
                std::uint64_t hash,
                const char *function,
                const char *file,
                int line,
                Types::ScopedProfilerFlags flags
        ) noexcept
        { Scoped::ScopedProfiler::GetProfiler()->BeginCpuProfile(name, hash, function, file, line, flags); }

        inline ~ScopedCpuProfiler() noexcept
        { Scoped::ScopedProfiler::GetProfiler()->EndCpuProfile(); }
    };
}

#if defined(__FUNCSIG__)
#define FUNCTION_NAME __FUNCSIG__
#elif defined(__PRETTY_FUNCTION__)
#define FUNCTION_NAME __PRETTY_FUNCTION__
#else
#define FUNCTION_NAME __FUNCTION_NAME__
#endif

#define ProfileCpuScopedFlags(name, flags) HeaderTech::Profiler::ScopedCpuProfiler scoped_cpu_profile_##name(#name,ctti::id_from_name(#name).hash(), __FUNCTION__, __FILE__, __LINE__, flags)

#define ProfileCpuScoped(name) ProfileCpuScopedFlags(name, HeaderTech::Profiler::Types::ScopedProfilerFlags_None)

#endif //HEADERTECH_SCOPEDPROFILEMARK_H
