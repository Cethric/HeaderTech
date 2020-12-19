//
// Created by rogan2 on 10/11/2020.
//

#ifndef HEADERTECH_PROFILERMANAGER_INL
#define HEADERTECH_PROFILERMANAGER_INL

#include <ProfilerManager.h>
#include <Logger.inl>
#include <ProfileDispatcher.inl>
#include <ScopedProfileMark.h>

namespace HeaderTech::Profiler {
    inline ProfilerManager::ProfilerManager()
            : m_server(),
              m_logDispatcher(),
              m_profileDispatcher(),
              m_cpuProfiles(),
              m_currentCpuProfile(),
              m_log(HeaderTech::Logging::make_logger<ProfilerManager>()),
              m_serverThread(&ProfilerManager::ProfilerServerThread, this)
    { SPDLOG_LOGGER_DEBUG(m_log, "Construct Profiler"); }

    inline ProfilerManager::~ProfilerManager()
    {
        m_server.stop();
        m_serverThread.join();
        SPDLOG_LOGGER_DEBUG(m_log, "Destruct Profiler");
    }

    inline void ProfilerManager::LogMessage(const Message &message)
    { m_logDispatcher.PushMessage(message); }

    inline void ProfilerManager::Flush()
    {
        m_profileDispatcher.ProcessCpuProfiles(m_cpuProfiles);
        m_cpuProfiles.clear();
        m_currentCpuProfile.clear();
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

    inline void ProfilerManager::BeginCpuProfile(
            const char *name,
            std::uint64_t hash,
            const char *function,
            const char *file,
            int line,
            Types::ScopedProfilerFlags flags
    ) noexcept
    {
        Types::CpuProfileHash parent_hash = 0;
        if (!m_currentCpuProfile.empty()) {
            parent_hash = m_currentCpuProfile.front();
        }

        if (flags == Types::ScopedProfilerFlags_Aggregate && m_cpuProfiles.contains(hash)) {
            auto &current = m_cpuProfiles.at(hash);
            ++current.call_count;
            current.end = glfwGetTime();
            m_currentCpuProfile.push_front(hash);
            return;
        }

        if (flags == Types::ScopedProfilerFlags_Recursive && parent_hash == hash) {
            auto &current = m_cpuProfiles.at(hash);
            ++current.call_count;
            ++current.recursion_count;
            current.max_recursion_count = current.max_recursion_count > current.recursion_count
                                          ? current.max_recursion_count
                                          : current.recursion_count;
            return;
        }

        m_cpuProfiles.insert_or_assign(
                hash,
                {
                        .name=name,
                        .function=function,
                        .line=line,
                        .file=file,
                        .flags=flags,
                        .call_count=1,
                        .recursion_count=(flags == Types::ScopedProfilerFlags_Recursive ? 1u : 0u),
                        .max_recursion_count=(flags == Types::ScopedProfilerFlags_Recursive ? 1u : 0u),
                        .start=glfwGetTime(),
                        .end=0,
                        .delta=0,
                        .total_delta=0,
                        .parent=parent_hash,
                        .children={}
                }
        );
        m_cpuProfiles[parent_hash].children.emplace(hash);
        m_currentCpuProfile.push_front(hash);
    }

    void ProfilerManager::EndCpuProfile() noexcept
    {
        if (m_currentCpuProfile.empty()) {
            return;
        }
        auto current_hash = m_currentCpuProfile.front();
        auto &current = m_cpuProfiles.at(current_hash);
        if (current.recursion_count > 0) {
            --current.recursion_count;
        } else {
            auto end_time = glfwGetTime();

            double delta;
            if (current.call_count > 1 && current.max_recursion_count == 0) {
                delta = end_time - current.end;
            } else {
                delta = end_time - current.start;
            }
            current.delta += delta;

            if (current.parent > 0) {
                auto &parent = m_cpuProfiles.at(current.parent);
                parent.total_delta += delta;
            }

            m_currentCpuProfile.pop_front();
            if (current.flags == Types::ScopedProfilerFlags_Recursive) {
                m_currentCpuProfile.pop_front();
            }
        }
    }
}

#endif //HEADERTECH_PROFILERMANAGER_INL
