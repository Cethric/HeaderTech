//
// Created by rogan2 on 12/11/2020.
//

#ifndef HEADERTECH_SCOPEDPROFILER_H
#define HEADERTECH_SCOPEDPROFILER_H

#include <Remotery.h>

namespace HeaderTech::Profiler::Scoped {
    class ScopedProfiler {
    public:
        inline ScopedProfiler();

        inline ~ScopedProfiler();

        inline static Remotery *GetRemotery() noexcept;

        inline static Remotery *m_rmt = nullptr;
    };
}

#endif //HEADERTECH_SCOPEDPROFILER_H
