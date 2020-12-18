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

    void OpenGLWindowApi::MakeCurrent() noexcept
    { glfwMakeContextCurrent(m_window); }

    GLFWwindow *OpenGLWindowApi::GetOwnedWindow() const noexcept
    { return m_window; }
}

#endif //HEADERTECH_OPENGLWINDOWAPI_INL
