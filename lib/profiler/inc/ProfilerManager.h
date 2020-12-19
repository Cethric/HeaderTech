//
// Created by rogan2 on 10/11/2020.
//

#ifndef HEADERTECH_PROFILERMANAGER_H
#define HEADERTECH_PROFILERMANAGER_H

#include <thread>

#include <httplib.h>

#include <Types.h>
#include <LogDispatcher.h>
#include <ProfileDispatcher.h>

#include <Logging.h>
#include <ProfilerTypes.h>

namespace HeaderTech::Profiler {
    namespace Scoped {
        class ScopedProfiler;
    }

    class ProfilerManager {
    public:
        inline ~ProfilerManager();

        inline void LogMessage(const Message &message);

        inline void Flush();

    private:
        inline void ProfilerServerThread();

    public:
        LogDispatcher m_logDispatcher;
        ProfileDispatcher m_profileDispatcher;

    private:
        HeaderTech::Logging::Logger m_log;

        httplib::Server m_server;
        std::thread m_serverThread;

    private:
        inline ProfilerManager();

        friend class HeaderTech::Profiler::Scoped::ScopedProfiler;

    private:
        friend class ScopedCpuProfiler;

        inline void BeginCpuProfile(
                const char *name,
                std::uint64_t hash,
                const char *function,
                const char *file,
                int line,
                Types::ScopedProfilerFlags flags
        ) noexcept;

        inline void EndCpuProfile() noexcept;

        Types::CpuProfileMap m_cpuProfiles;
        Types::CpuProfileHashQueue m_currentCpuProfile;
    };
}

#endif //HEADERTECH_PROFILERMANAGER_H
