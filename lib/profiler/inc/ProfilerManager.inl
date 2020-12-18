//
// Created by rogan2 on 10/11/2020.
//

#ifndef HEADERTECH_PROFILERMANAGER_INL
#define HEADERTECH_PROFILERMANAGER_INL

#include <ProfilerManager.h>
#include <Logger.inl>
#include <ProfileDispatcher.inl>


namespace HeaderTech::Profiler {
    inline ProfilerManager::ProfilerManager()
            : m_server(),
              m_logDispatcher(),
              m_profileDispatcher(),
              m_log(HeaderTech::Logging::make_logger<ProfilerManager>()),
              m_serverThread(&ProfilerManager::ProfilerServerThread, this)
    {
        SPDLOG_LOGGER_DEBUG(m_log, "Construct Profiler");
    }

    inline ProfilerManager::~ProfilerManager()
    {
        m_server.stop();
        m_serverThread.join();
        SPDLOG_LOGGER_DEBUG(m_log, "Destruct Profiler");
    }

    inline void ProfilerManager::LogMessage(const Message &message)
    {
        m_logDispatcher.PushMessage(message);
    }

    inline details::ProfileTimingMark *ProfilerManager::BeginProfileMark(const std::string &name)
    { return m_profileDispatcher.BeginProfileMark(name); }

    void ProfilerManager::EndProfileMark(const details::ProfileTimingMark &mark)
    { m_profileDispatcher.EndProfileMark(mark); }

    inline void ProfilerManager::Flush()
    {

    }

    inline void ProfilerManager::ProfilerServerThread()
    {
        SPDLOG_LOGGER_INFO(m_log, "Initialising profiler server thread");

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
            SPDLOG_LOGGER_INFO(log, "Request: {} {}", req.path, res.status);
        });

        SPDLOG_LOGGER_INFO(m_log, "Launching profiler server thread");
        m_server.listen("localhost", 8080, 0);
        SPDLOG_LOGGER_INFO(m_log, "Stopped profiler server thread");
    }
}

#endif //HEADERTECH_PROFILERMANAGER_INL
