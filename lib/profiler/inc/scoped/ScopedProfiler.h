//
// Created by rogan2 on 12/11/2020.
//

#ifndef HEADERTECH_SCOPEDPROFILER_H
#define HEADERTECH_SCOPEDPROFILER_H

#include <ProfilerManager.h>
#include <functional>

namespace HeaderTech::Profiler::Scoped {
    class ScopedProfiler {
        using CallbackFn = std::function<void(HeaderTech::Profiler::ProfilerManager &)>;
    public:
        inline ScopedProfiler()
        {
            ScopedProfiler::m_manager = new HeaderTech::Profiler::ProfilerManager();
        }

        inline ~ScopedProfiler()
        {
            delete ScopedProfiler::m_manager;
        }

        inline static HeaderTech::Profiler::ProfilerManager *GetProfiler() noexcept
        {
            return ScopedProfiler::m_manager;
        }

        inline static bool HasProfiler() noexcept
        {
            return ScopedProfiler::m_manager != nullptr;
        }

        inline static void UseProfiler(const CallbackFn &callback) noexcept
        {
            if (ScopedProfiler::m_manager != nullptr) {
                callback(*ScopedProfiler::m_manager);
            }
        }

    private:
        inline static HeaderTech::Profiler::ProfilerManager *m_manager = nullptr;
    };
}

#endif //HEADERTECH_SCOPEDPROFILER_H
