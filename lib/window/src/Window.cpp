//
// Created by rogan2 on 19/11/2020.
//

#include <Window.h>

using Dispatcher = HeaderTech::Events::EventDispatcher;

namespace HeaderTech::Window {

    Window::Window(
            const HeaderTech::Config::WindowConfig &config,
            Dispatcher *dispatcher
    ) noexcept
            : m_dispatcher(dispatcher),
              m_window(nullptr),
              m_log(HeaderTech::Logging::make_logger_async<Window>())
    {
        m_window = glfwCreateWindow(config.width, config.height, config.title, nullptr, nullptr);
        glfwShowWindow(m_window);
        m_log->info("Created Window: {}", config.title);
        LinkEvents();
    }

    Window::~Window() noexcept
    {
        glfwSetWindowUserPointer(m_window, nullptr);
        glfwDestroyWindow(m_window);
    }

    bool Window::IsOpen() noexcept
    {
        return glfwWindowShouldClose(m_window) == GLFW_FALSE;
    }

    void Window::Swap() noexcept
    {
        glfwSwapBuffers(m_window);
    }
}
