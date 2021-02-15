//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_OPENGLWINDOWAPI_INL
#define HEADERTECH_OPENGLWINDOWAPI_INL

#include <api/opengl/OpenGLWindowApi.h>
#include <api/opengl/OpenGLWindowApiEvents.inl>

#include <api/GLFWKeyMapping.h>

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32 1
#endif

#include <GLFW/glfw3native.h>
#include <glad/gl.h>

namespace HeaderTech::Window::Api::OpenGL {
    OpenGLWindowApi::OpenGLWindowApi(
            const HeaderTech::Config::WindowConfig &config,
            HeaderTech::Events::EventDispatcher *dispatcher,
            GLFWwindow *shared
    ) noexcept
            : HeaderTech::Core::Api::Window::WindowApi(dispatcher),
              m_window(nullptr),
              m_log(HeaderTech::Logging::make_logger<OpenGLWindowApi>())
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

                SPDLOG_LOGGER_INFO(
                        m_log,
                        "Checking window: {} {}x{} {}x{}",
                        glfwGetMonitorName(current),
                        x,
                        y,
                        width,
                        height
                );

                if (wx > x && wy > y && wx < (x + width) && wy < (y + height)) {
                    activeMonitor = current;
                }
            }

            if (activeMonitor) {
                SPDLOG_LOGGER_INFO(
                        m_log,
                        "Using window: {} {}",
                        glfwGetMonitorName(activeMonitor),
                        glfwGetWin32Monitor(activeMonitor)
                );
                const GLFWvidmode *mode = glfwGetVideoMode(activeMonitor);

                glfwSetWindowMonitor(m_window, activeMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            }
        }
    }

    void OpenGLWindowApi::MakeCurrent() noexcept
    { glfwMakeContextCurrent(m_window); }

    GLFWwindow *OpenGLWindowApi::GetOwnedWindow() const noexcept
    { return m_window; }

    glm::ivec2 OpenGLWindowApi::GetSize() const noexcept
    {
        glm::ivec2 size;
        glfwGetFramebufferSize(m_window, &size.x, &size.y);
        return size;
    }

    bool OpenGLWindowApi::IsKeyPressed(HeaderTech::Core::KeyType key) const noexcept
    { return glfwGetKey(m_window, HeaderTech::Window::Api::GLFW::KeyMapping[key]) == GLFW_PRESS; }
}

#endif //HEADERTECH_OPENGLWINDOWAPI_INL