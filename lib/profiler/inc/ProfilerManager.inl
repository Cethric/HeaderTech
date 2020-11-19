//
// Created by rogan2 on 10/11/2020.
//

#ifndef HEADERTECH_PROFILERMANAGER_INL
#define HEADERTECH_PROFILERMANAGER_INL

#include <ProfilerManager.h>
#include <Logger.inl>


namespace HeaderTech::Profiler {
    inline ProfilerManager::ProfilerManager()
            : m_server(),
              m_logDispatcher(),
              m_profileDispatcher(),
              m_log(HeaderTech::Logging::make_logger<ProfilerManager>()),
              m_serverThread(&ProfilerManager::ProfilerServerThread, this)
    {
        m_log->info("Construct Profiler");
    }

    inline ProfilerManager::~ProfilerManager()
    {
        m_server.stop();
        m_serverThread.join();
        m_log->info("Destruct Profiler");
    }

    inline void ProfilerManager::LogMessage(const Message &message)
    {
        m_logDispatcher.PushMessage(message);
    }

    void ProfilerManager::ProfileMark(const std::string &name, const double &delta)
    {
        m_profileDispatcher.PushProfile(name, delta);
    }

    inline void ProfilerManager::ProfilerServerThread()
    {
        m_log->info("Initialising profiler server thread");

        m_server.Get("/profiler/logs", [this](const httplib::Request &req, httplib::Response &res) {
            res.set_chunked_content_provider("text/event-stream", [&](size_t offset, httplib::DataSink &sink) {
                this->m_logDispatcher.WaitForEvent(&sink);
                return true;
            });
            res.set_header("Access-Control-Allow-Origin", "*");
        });

        m_server.Get("/profiler/marks", [this](const httplib::Request &req, httplib::Response &res) {
            res.set_chunked_content_provider("text/event-stream", [&](size_t offset, httplib::DataSink &sink) {
                this->m_profileDispatcher.WaitForEvent(&sink);
                return true;
            });
            res.set_header("Access-Control-Allow-Origin", "*");
        });

        m_server.set_mount_point("/", "./profiler/ui");
        m_server.Get(R"(/.*)", [](const httplib::Request &req, httplib::Response &res) {
            res.set_redirect("/");
        });
        m_server.set_logger([](const httplib::Request &req, const httplib::Response &res) {
            auto log = HeaderTech::Logging::get_or_make_logger("ProfilerServer");
            log->info("Request: {} {}", req.path, res.status);
        });

        m_log->info("Launching profiler server thread");
        m_server.listen("localhost", 8080, 0);
        m_log->info("Stopped profiler server thread");
    }
}

#endif //HEADERTECH_PROFILERMANAGER_INL
