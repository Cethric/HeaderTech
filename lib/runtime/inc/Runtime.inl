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

namespace HeaderTech::Runtime {

    inline Runtime::Runtime(const HeaderTech::Config::RuntimeConfig &config)
            : m_running(false),
              m_log(HeaderTech::Logging::make_logger_async<Runtime>()),
              m_window(new HeaderTech::Window::Window(config.window, this)),
              m_eventThread(&Runtime::EventProcessorThread, this) {
        SPDLOG_LOGGER_DEBUG(m_log, "Constructor");
    }

    inline Runtime::~Runtime() {
        SPDLOG_LOGGER_DEBUG(m_log, "Destructor");
        delete m_window;
    }

    inline int Runtime::Launch(HeaderTech::Scene::SceneManager &sceneManager) {
        SPDLOG_LOGGER_INFO(m_log, "Launch");
        m_running = true;

        double previous = glfwGetTime();
        double lag = 0.0;

        static const double MS_PER_UPDATE = 60. / 1000;

        while (IsRunning()) {
            {
                rmt_ScopedCPUSample(main_loop, RMTSF_None);
                double current = glfwGetTime();
                double elapsed = current - previous;
                previous = current;
                lag += elapsed;

                glfwPollEvents();
                {
                    rmt_ScopedCPUSample(update_frame, RMTSF_None);
                    while (lag >= MS_PER_UPDATE) {
                        rmt_ScopedCPUSample(process_tick, RMTSF_Aggregate);
                        sceneManager.TickScene(MS_PER_UPDATE, lag);
                        lag -= MS_PER_UPDATE;
                    }
                }
                {
                    rmt_ScopedOpenGLSample(render_view);
                    rmt_ScopedCPUSample(render_view, RMTSF_None);
                    {
                        rmt_ScopedOpenGLSample(render_frame);
                        rmt_ScopedCPUSample(render_frame, RMTSF_None);
                        sceneManager.RenderScene(lag / MS_PER_UPDATE);
                    }

                    {
                        rmt_ScopedOpenGLSample(render_imgui);
                        rmt_ScopedCPUSample(render_imgui, RMTSF_None);
                        sceneManager.RenderDebugUI();
                    }
                }
                {
                    rmt_ScopedCPUSample(render_swap, RMTSF_None);
                    m_window->Swap();
                }
            }
//            std::this_thread::yield();
        }
        m_eventThread.join();
        return 0;
    }

    inline void Runtime::Stop() { m_running = false; }

    inline bool Runtime::IsRunning() const noexcept { return m_running && m_window->IsOpen(); }

    inline void Runtime::EventProcessorThread() noexcept {
        rmt_SetCurrentThreadName("EventProcessorThread");

        while (!IsRunning()) {}

        while (IsRunning()) {
            rmt_ScopedCPUSample(process_event_thread, RMTSF_None);
            ProcessNextEvent();
            std::this_thread::yield();
        }
    }
}

#endif //HEADERTECH_RUNTIME_INL
