//
// Created by rogan2 on 15/10/2020.
//

#ifndef HEADERTECH_RUNTIME_INL
#define HEADERTECH_RUNTIME_INL

#include <Runtime.h>
#include <ScopedProfileMark.h>

#include <GLFW/glfw3.h>
#include <thread>
#include <functional>

namespace HeaderTech::Core {

    Runtime::Runtime(const HeaderTech::Config::RuntimeConfig &config)
            : m_log(HeaderTech::Logging::make_logger_async<Runtime>()),
              m_running(false),
              m_window(config.window, this)
    {
        SPDLOG_LOGGER_DEBUG(m_log, "Constructor");
    }

    Runtime::~Runtime()
    {
        SPDLOG_LOGGER_DEBUG(m_log, "Destructor");
    }

    int Runtime::Launch(HeaderTech::Scene::SceneManager &sceneManager)
    {
        SPDLOG_LOGGER_INFO(m_log, "Launch");
        m_running = true;

        double previous = glfwGetTime();
        double lag = 0.0;

        static const double MS_PER_UPDATE = 60. / 1000;

        auto profiler = HeaderTech::Profiler::Scoped::ScopedProfiler::GetProfiler();

        while (m_running && m_window.IsOpen()) {
            HeaderTech::Profiler::ScopedProfileMark loop("main_loop");
            double current = glfwGetTime();
            double elapsed = current - previous;
            previous = current;
            lag += elapsed;

            glfwPollEvents();
            ProcessNextEvent();
            {
                HeaderTech::Profiler::ScopedProfileMark update("update_frame");
                while (lag >= MS_PER_UPDATE) {
                    HeaderTech::Profiler::ScopedProfileMark tick("process_tick");
                    sceneManager.TickScene(MS_PER_UPDATE, lag);
                    lag -= MS_PER_UPDATE;
                }
            }
            {
                HeaderTech::Profiler::ScopedProfileMark frame("process_frame");
                sceneManager.RenderScene(lag / MS_PER_UPDATE);
            }
            m_window.Swap();
            profiler->Flush();
        }
        return 0;
    }

    void Runtime::Stop()
    {
        m_running = false;
    }
}

#endif //HEADERTECH_RUNTIME_INL
