//
// Created by rogan2 on 9/02/2021.
//

#ifndef HEADERTECH_SCOPEDPROFILER_INL
#define HEADERTECH_SCOPEDPROFILER_INL

#include <scoped/ScopedProfiler.h>

namespace HeaderTech::Profiler::Scoped {
    ScopedProfiler::ScopedProfiler()
    {
        auto settings = rmt_Settings();
        rmt_CreateGlobalInstance(&m_rmt);
    }

    ScopedProfiler::~ScopedProfiler()
    { rmt_DestroyGlobalInstance(m_rmt); }

    Remotery *ScopedProfiler::GetRemotery() noexcept
    { return ScopedProfiler::m_rmt; }
}

#endif //HEADERTECH_SCOPEDPROFILER_INL
