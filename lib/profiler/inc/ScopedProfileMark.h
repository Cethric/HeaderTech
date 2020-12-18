//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_SCOPEDPROFILEMARK_H
#define HEADERTECH_SCOPEDPROFILEMARK_H

#include <scoped/ScopedProfiler.h>
#include <GLFW/glfw3.h>
#include <string>
#include <utility>

namespace HeaderTech::Profiler {
//    class ScopedProfileMark final {
//    public:
//        inline explicit ScopedProfileMark(const std::string &name)
//                : m_start(glfwGetTime()),
//                  m_profiler(Scoped::ScopedProfiler::GetProfiler()),
//                  m_mark(Scoped::ScopedProfiler::GetProfiler()->BeginProfileMark(name))
//        {}
//
//        inline ~ScopedProfileMark()
//        { Stop(); }
//
//        inline void Stop()
//        {
//            m_mark->Finish(glfwGetTime() - m_start);
//            m_profiler->EndProfileMark(*m_mark);
//        }
//
//    private:
//        double m_start;
//        ProfilerManager *m_profiler;
//        details::ProfileTimingMark *m_mark;
//    };
    enum ScopedProfilerFlags : std::uint8_t {
        ScopedProfilerFlags_None = 0,
    };

    class ScopedCpuProfiler final {
    public:
        ScopedCpuProfiler(
                const char *name,
                const char *function,
                const char *line,
                const char *file,
                std::uint8_t flags = ScopedProfilerFlags_None
        )
        {
            HeaderTech::Profiler::Scoped::ScopedProfiler::GetProfiler()->BeginCpuProfile(
                    name,
                    function,
                    line,
                    file,
                    flags
            );
        }

        ~ScopedCpuProfiler()
        {
            HeaderTech::Profiler::Scoped::ScopedProfiler::GetProfiler()->EndCpuProfile();
        }
    };
}

#define ProfileCpuScoped(name, flags) HeaderTech::Profiler::ScopedCpuProfiler(name, __FUNCTION__, __LINE__, __FILE__, flags)

#endif //HEADERTECH_SCOPEDPROFILEMARK_H
