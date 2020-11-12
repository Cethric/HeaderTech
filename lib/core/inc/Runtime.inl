//
// Created by rogan2 on 15/10/2020.
//

#ifndef HEADERTECH_RUNTIME_INL
#define HEADERTECH_RUNTIME_INL

#include <Runtime.h>
#include <events/LaunchEvent.h>
#include <ScopedProfileMark.h>

#include <GLFW/glfw3.h>
#include <thread>
#include <functional>

namespace HeaderTech::Core {

    Runtime::Runtime(int argc, const char **argv, const Configuration::RuntimeConfig &config)
            : m_log(HeaderTech::Logging::make_logger_async<Runtime>()), m_running(false)
    {
        m_log->info("Constructor");
        Subscribe<HeaderTech::Core::Events::LaunchEvent>(this);
        Subscribe<HeaderTech::Core::Events::LaunchEvent>([](auto event) {
            auto log = HeaderTech::Logging::make_logger_async("Runtime2");
            log->info("Launch Event 2 Called");
        });
        if (glfwInit() == GLFW_FALSE) {
            throw std::exception("Could not initialise GLFW");
        }
    }

    Runtime::~Runtime()
    {
        m_log->info("Destructor");
        glfwTerminate();
    }

    int Runtime::Launch()
    {
        m_log->info("Launch");
        m_running = true;
        Dispatch<HeaderTech::Core::Events::LaunchEvent, HeaderTech::Events::EventPriority>(0);

        double previous = glfwGetTime();
        double lag = 0.0;

        static const double MS_PER_UPDATE = 60. / 1000;

        std::uint16_t counter = 0;
        while (m_running && (counter++) < 0xffff) {
            HeaderTech::Profiler::ScopedProfileMark mark("main_loop");
            double current = glfwGetTime();
            double elapsed = current - previous;
            previous = current;
            lag += elapsed;

            glfwPollEvents();
            ProcessNextEvent();
            while (lag >= MS_PER_UPDATE) {
                ProcessNextTick();
                lag -= MS_PER_UPDATE;
            }
            RenderNextFrame(lag / MS_PER_UPDATE);
        }
        return 0;
    }

    void Runtime::ProcessNextTick()
    {
        HeaderTech::Profiler::ScopedProfileMark mark("process_tick");
        m_log->debug("Process Tick: {}", 60. / 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(6));
    }

    void Runtime::RenderNextFrame(double offset)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("process_frame");
        m_log->debug("Render with offset: {}", offset);
        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }
}

#endif //HEADERTECH_RUNTIME_INL
