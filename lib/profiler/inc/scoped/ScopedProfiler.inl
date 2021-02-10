//
// Created by rogan2 on 9/02/2021.
//

#ifndef HEADERTECH_SCOPEDPROFILER_INL
#define HEADERTECH_SCOPEDPROFILER_INL

#include <scoped/ScopedProfiler.h>
#include <ProfilerManager.h>

namespace HeaderTech::Profiler::Scoped {
    ScopedProfiler::ScopedProfiler()
    { ScopedProfiler::m_manager = new HeaderTech::Profiler::ProfilerManager(); }

    ScopedProfiler::~ScopedProfiler()
    { delete ScopedProfiler::m_manager; }

    HeaderTech::Profiler::ProfilerManager *ScopedProfiler::GetProfiler() noexcept
    { return ScopedProfiler::m_manager; }

    bool ScopedProfiler::HasProfiler() noexcept
    { return ScopedProfiler::m_manager != nullptr; }

    void ScopedProfiler::UseProfiler(
            const std::function<void(HeaderTech::Profiler::ProfilerManager &)> &callback
    ) noexcept
    {
        if (ScopedProfiler::m_manager != nullptr) {
            callback(*ScopedProfiler::m_manager);
        }
    }
}

#endif //HEADERTECH_SCOPEDPROFILER_INL
