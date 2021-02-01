//
// Created by rogan2 on 15/10/2020.
//

#ifndef HEADERTECH_RUNTIME_INL
#define HEADERTECH_RUNTIME_INL

#include <Runtime.h>
#include <ScopedProfileMark.h>
#include <SceneManager.h>
#include <SceneManager.inl>
#include <Window.h>

#include <GLFW/glfw3.h>
#include <thread>
#include <functional>

namespace HeaderTech::Core {

    inline Runtime::Runtime(const HeaderTech::Config::RuntimeConfig &config)
            : m_running(false),
              m_log(HeaderTech::Logging::make_logger_async<Runtime>()),
              m_window(new HeaderTech::Window::Window(config.window, this))
    {
        SPDLOG_LOGGER_DEBUG(m_log, "Constructor");
    }

    inline Runtime::~Runtime()
    {
        SPDLOG_LOGGER_DEBUG(m_log, "Destructor");
        delete m_window;
    }

    inline int Runtime::Launch(HeaderTech::Scene::SceneManager &sceneManager)
    {
        SPDLOG_LOGGER_INFO(m_log, "Launch");
        m_running = true;

        double previous = glfwGetTime();
        double lag = 0.0;

        static const double MS_PER_UPDATE = 60. / 1000;

        auto profiler = HeaderTech::Profiler::Scoped::ScopedProfiler::GetProfiler();

        auto &window = *m_window;

        while (m_running && window.IsOpen()) {
            {
                ProfileCpuScoped(main_loop);
                double current = glfwGetTime();
                double elapsed = current - previous;
                previous = current;
                lag += elapsed;

                glfwPollEvents();
                DrainEvents();
                {
                    ProfileCpuScoped(update_frame);
                    while (lag >= MS_PER_UPDATE) {
                        ProfileCpuScopedFlags(process_tick, HeaderTech::Profiler::Types::ScopedProfilerFlags_Recursive);
                        sceneManager.TickScene(MS_PER_UPDATE, lag);
                        lag -= MS_PER_UPDATE;
                    }
                }
                {
                    ProfileCpuScoped(process_frame);
                    sceneManager.RenderScene(lag / MS_PER_UPDATE);
                }

                {
                    ProfileCpuScoped(render_imgui);
                    sceneManager.RenderDebugUI();
                }
                window.Swap();
            }
            profiler->Flush();
        }
        return 0;
    }

    inline void Runtime::Stop()
    {
        m_running = false;
    }
}

#endif //HEADERTECH_RUNTIME_INL
