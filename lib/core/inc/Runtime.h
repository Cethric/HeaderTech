//
// Created by rogan2 on 15/10/2020.
//

#ifndef HEADERTECH_RUNTIME_H
#define HEADERTECH_RUNTIME_H

#include <memory>
#include <Logging.h>
#include <EventDispatcher.h>
#include <events/LaunchEvent.h>
#include <Config.h>

namespace HeaderTech::Scene {
    class SceneManager;
}

namespace HeaderTech::Window {
    class Window;
}

namespace HeaderTech::Core {
    class Runtime final : public HeaderTech::Events::EventDispatcher {
    public:
        inline explicit Runtime(const HeaderTech::Config::RuntimeConfig &config);

        inline ~Runtime() final;

        inline int Launch(HeaderTech::Scene::SceneManager *sceneManager);

        inline void Stop();

        [[nodiscard]] inline HeaderTech::Window::Window &GetWindow()
        { return *m_window; }

    protected:
        bool m_running;
        HeaderTech::Logging::Logger m_log;

        HeaderTech::Window::Window *m_window;
    };
}

#endif //HEADERTECH_RUNTIME_H
