//
// Created by rogan2 on 12/11/2020.
//

#ifndef HEADERTECH_SCOPEDPROFILER_H
#define HEADERTECH_SCOPEDPROFILER_H

#include <functional>

namespace HeaderTech::Profiler {
    class ProfilerManager;
}

namespace HeaderTech::Profiler::Scoped {
    class ScopedProfiler {
        using CallbackFn = std::function<void(HeaderTech::Profiler::ProfilerManager &)>;
    public:
        inline ScopedProfiler();

        inline ~ScopedProfiler();

        inline static HeaderTech::Profiler::ProfilerManager *GetProfiler() noexcept;

        inline static bool HasProfiler() noexcept;

        inline static void UseProfiler(const CallbackFn &callback) noexcept;

    private:
        inline static HeaderTech::Profiler::ProfilerManager *m_manager = nullptr;
    };
}

#endif //HEADERTECH_SCOPEDPROFILER_H
