//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_WINDOW_H
#define HEADERTECH_WINDOW_H

#define GLFW_INCLUDE_NONE 1

#include <GLFW/glfw3.h>
#include <EventDispatcher.h>
#include <Config.h>
#include <Logging.h>

namespace HeaderTech::Window {
    class Window {
    public:
        explicit Window(
                const HeaderTech::Config::WindowConfig &config,
                HeaderTech::Events::EventDispatcher *dispatcher
        ) noexcept;

        ~Window() noexcept;

        bool IsOpen() noexcept;

        void Swap() noexcept;

    protected:
        void LinkEvents() noexcept;

    protected:
        HeaderTech::Logging::Logger m_log;
        GLFWwindow *m_window;
        HeaderTech::Events::EventDispatcher *m_dispatcher;
    };
}

#endif //HEADERTECH_WINDOW_H
