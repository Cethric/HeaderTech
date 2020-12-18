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

namespace HeaderTech::Profiler {
    namespace Scoped {
        class ScopedProfiler;
    }

    class ProfilerManager {
    public:
        inline ~ProfilerManager();

        inline void LogMessage(const Message &message);

        inline details::ProfileTimingMark *BeginProfileMark(const std::string &name);

        inline void EndProfileMark(const details::ProfileTimingMark& mark);

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
    };
}

#endif //HEADERTECH_PROFILERMANAGER_H
