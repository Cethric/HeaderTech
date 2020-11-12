//
// Created by rogan2 on 12/11/2020.
//

#ifndef HEADERTECH_WINDOW_H
#define HEADERTECH_WINDOW_H

//#include <GLFW/glfw3.h>
#include <configuration/Configuration.h>

namespace HeaderTech::Core {
    class Window {
    public:
        inline explicit Window(
                const Configuration::WindowConfig &config,
                HeaderTech::Events::EventDispatcher *dispatcher
        ) noexcept;

        inline ~Window() noexcept;

    protected:
        GLFWwindow *m_window;
        HeaderTech::Events::EventDispatcher *m_dispatcher;
    };
}

#endif //HEADERTECH_WINDOW_H
