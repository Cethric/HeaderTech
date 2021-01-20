//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_OPENGLWINDOWAPI_INL
#define HEADERTECH_OPENGLWINDOWAPI_INL

#include <api/opengl/OpenGLWindowApi.h>
#include <api/opengl/OpenGLWindowApiEvents.inl>

namespace HeaderTech::Window::Api::OpenGL {
    OpenGLWindowApi::OpenGLWindowApi(
            const HeaderTech::Config::WindowConfig &config,
            HeaderTech::Events::EventDispatcher *dispatcher,
            GLFWwindow *shared
    ) noexcept
            : HeaderTech::Window::Api::WindowApi(dispatcher), m_window(nullptr)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_CONTEXT_DEBUG, GL_TRUE);
        m_window = glfwCreateWindow(config.width, config.height, config.title, nullptr, shared);
        glfwShowWindow(m_window);
        LinkEvents();
    }

    OpenGLWindowApi::~OpenGLWindowApi() noexcept
    {
        glfwSetWindowUserPointer(m_window, nullptr);
        glfwDestroyWindow(m_window);
    }

    bool OpenGLWindowApi::IsOpen() noexcept
    { return glfwWindowShouldClose(m_window) == GLFW_FALSE; }

    void OpenGLWindowApi::SwapBuffers() noexcept
    { glfwSwapBuffers(m_window); }

    void OpenGLWindowApi::ToggleFullscreen() noexcept
    {
        GLFWmonitor *monitor = glfwGetWindowMonitor(m_window);
        if (monitor) {
            glfwSetWindowMonitor(m_window, nullptr, 200, 200, 800, 600, 0);
        } else {
            int monitorCount = 0;
            GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);
            GLFWmonitor *activeMonitor = nullptr;

            int wx, wy;
            glfwGetWindowPos(m_window, &wx, &wy);

            for (int i = 0; i < monitorCount; ++i) {
                GLFWmonitor *current = *(monitors + i);
                int x, y, width, height;
                glfwGetMonitorWorkarea(current, &x, &y, &width, &height);

                SPDLOG_INFO("Checking window: {} {}x{} {}x{}", glfwGetMonitorName(current), x, y, width, height);

                if (wx > x && wy > y && wx < (x + width) && wy < (y + height)) {
                    activeMonitor = current;
                }
            }

            if (activeMonitor) {
                SPDLOG_INFO("Using window: {} {}", glfwGetMonitorName(activeMonitor), glfwGetWin32Monitor(activeMonitor));
                const GLFWvidmode *mode = glfwGetVideoMode(activeMonitor);

                glfwSetWindowMonitor(m_window, activeMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            }
        }
    }

    void OpenGLWindowApi::MakeCurrent() noexcept
    { glfwMakeContextCurrent(m_window); }

    GLFWwindow *OpenGLWindowApi::GetOwnedWindow() const noexcept
    { return m_window; }

    int OpenGLWindowApi::GetWidth() const noexcept
    {
        // TODO so yeah this is inefficient
        int width;
        glfwGetFramebufferSize(m_window, &width, nullptr);
        return width;
    }

    int OpenGLWindowApi::GetHeight() const noexcept
    {
        // TODO so yeah this is inefficient
        int height;
        glfwGetFramebufferSize(m_window, nullptr, &height);
        return height;
    }
}

#endif //HEADERTECH_OPENGLWINDOWAPI_INL
