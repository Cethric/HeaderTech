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
//    public:
//        static ProfilerManager &Get();

    public:
        inline ~ProfilerManager();

        inline void LogMessage(const Message &message);

        inline void ProfileMark(const std::string &name, const double &delta);

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

//        static ProfilerManager c_instance;
    };
}

#endif //HEADERTECH_PROFILERMANAGER_H
