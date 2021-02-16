//
// Created by rogan2 on 15/10/2020.
//

#ifndef HEADERTECH_RUNTIME_H
#define HEADERTECH_RUNTIME_H

#include <memory>
#include <thread>
#include <LoggingIncludes.h>
#include <EventDispatcher.h>
#include <events/LaunchEvent.h>
#include <ConfigIncludes.h>

namespace HeaderTech::Scene {
    class SceneManager;
}

namespace HeaderTech::Window {
    class Window;
}

namespace HeaderTech::Runtime {
    class Runtime final : public HeaderTech::Events::EventDispatcher {
    public:
        inline explicit Runtime(const HeaderTech::Config::RuntimeConfig &config);

        inline ~Runtime() final;

        inline int Launch(HeaderTech::Scene::SceneManager &sceneManager);

        inline void Stop();

        [[nodiscard]] inline HeaderTech::Window::Window &GetWindow()
        { return *m_window; }

        [[nodiscard]] inline bool IsRunning() const noexcept;

    private:
        inline void EventProcessorThread() noexcept;

    protected:
        bool m_running;
        HeaderTech::Logging::Logger m_log;

        HeaderTech::Window::Window *m_window;

        std::thread m_eventThread;
    };
}

#endif //HEADERTECH_RUNTIME_H
