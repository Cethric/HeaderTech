//
// Created by rogan2 on 12/11/2020.
//

#ifndef HEADERTECH_WINDOW_INL
#define HEADERTECH_WINDOW_INL

#include <Window.h>

namespace HeaderTech::Core {
    Window::Window(
            const Configuration::WindowConfig &config,
            HeaderTech::Events::EventDispatcher *dispatcher
    ) noexcept
            : m_dispatcher(dispatcher),
              m_window(nullptr)
    {
        m_window = glfwCreateWindow(config.width, config.height, config.title, nullptr, nullptr);
    }

    Window::~Window() noexcept
    {
        glfwDestroyWindow(m_window);
    }
}

#endif //HEADERTECH_WINDOW_INL
