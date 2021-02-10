//
// Created by rogan2 on 15/10/2020.
//

#ifndef HEADERTECH_RUNTIME_INL
#define HEADERTECH_RUNTIME_INL

#include <Runtime.h>
#include <scoped/ScopedProfilerIncludes.h>
#include <SceneManager.h>
#include <SceneManager.inl>
#include <WindowIncludes.h>

#include <GLFW/glfw3.h>
#include <functional>

namespace HeaderTech::Core {

    inline Runtime::Runtime(const HeaderTech::Config::RuntimeConfig &config)
            : m_running(false),
              m_log(HeaderTech::Logging::make_logger_async<Runtime>()),
              m_window(new HeaderTech::Window::Window(config.window, this)),
              m_eventThread(&Runtime::EventProcessorThread, this)
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

        while (IsRunning()) {
            {
                ProfileCpuScoped(main_loop);
                double current = glfwGetTime();
                double elapsed = current - previous;
                previous = current;
                lag += elapsed;

                glfwPollEvents();
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
                m_window->Swap();
            }
            profiler->Flush();
            std::this_thread::yield();
        }
        m_eventThread.join();
        return 0;
    }

    inline void Runtime::Stop()
    { m_running = false; }

    inline bool Runtime::IsRunning() const noexcept
    { return m_running && m_window->IsOpen(); }

    inline void Runtime::EventProcessorThread() noexcept
    {
        while (IsRunning()) {
            ProfileCpuScoped(process_event_thread);
            ProcessNextEvent();
            std::this_thread::yield();
        }
    }
}

#endif //HEADERTECH_RUNTIME_INL
