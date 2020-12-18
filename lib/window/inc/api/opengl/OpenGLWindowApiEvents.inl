//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_OPENGLWINDOWAPIEVENTS_INL
#define HEADERTECH_OPENGLWINDOWAPIEVENTS_INL

#include <Events.h>
#include <Profiler.h>
#include <api/opengl/OpenGLWindowApi.h>

#include <events/WindowPositionEvent.h>
#include <events/WindowSizeEvent.h>
#include <events/WindowCloseEvent.h>
#include <events/WindowRefreshEvent.h>
#include <events/WindowFocusEvent.h>
#include <events/WindowIconifyEvent.h>
#include <events/WindowMaximizeEvent.h>
#include <events/FramebufferSizeEvent.h>
#include <events/WindowContentScaleEvent.h>
#include <events/MouseButtonEvent.h>
#include <events/CursorPositionEvent.h>
#include <events/CursorEnterEvent.h>
#include <events/ScrollEvent.h>
#include <events/KeyEvent.h>
#include <events/CharEvent.h>
#include <events/CharModsEvent.h>
#include <events/FileDropEvent.h>

namespace HeaderTech::Window::Api::OpenGL {
    using Dispatcher = HeaderTech::Events::EventDispatcher;

    static inline void window_position_callback(GLFWwindow *window, int x, int y)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::WindowPositionEvent>(x, y);
    }

    static inline void window_size_callback(GLFWwindow *window, int width, int height)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::WindowSizeEvent>(width, height);
    }

    static inline void window_close_callback(GLFWwindow *window)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::WindowCloseEvent>();
    }

    static inline void window_refresh_callback(GLFWwindow *window)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::WindowRefreshEvent>();
    }

    static inline void window_focus_callback(GLFWwindow *window, int focused)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::WindowFocusEvent>(focused == GLFW_TRUE);
    }

    static inline void window_iconify_callback(GLFWwindow *window, int iconified)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::WindowIconifyEvent>(iconified == GLFW_TRUE);
    }

    static inline void window_maximize_callback(GLFWwindow *window, int maximized)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::WindowMaximizeEvent>(maximized == GLFW_TRUE);
    }

    static inline void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::FramebufferSizeEvent>(width, height);
    }

    static inline void window_content_scale_callback(GLFWwindow *window, float x, float y)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::WindowContentScaleEvent>(x, y);
    }

    static inline void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::MouseButtonEvent>(
                button,
                static_cast<HeaderTech::Window::Events::MouseButtonAction>(action),
                mods
        );
    }

    static inline void cursor_position_callback(GLFWwindow *window, double x, double y)
    {
        static double mX = 0;
        static double mY = 0;
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        double dX = x - mX;
        mX = x;
        double dY = y - mY;
        mY = y;
        dispatcher->Dispatch<HeaderTech::Window::Events::CursorPositionEvent>(x, y, dX, dY);
    }

    static inline void cursor_enter_callback(GLFWwindow *window, int entered)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::CursorEnterEvent>(entered == GLFW_TRUE);
    }

    static inline void scroll_callback(GLFWwindow *window, double x, double y)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::ScrollEvent>(x, y);
    }

    static inline void key_callback(GLFWwindow *window, int key, int scan, int action, int mods)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::KeyEvent>(
                key,
                scan,
                static_cast<HeaderTech::Window::Events::KeyAction>(action),
                mods
        );
    }

    static inline void char_callback(GLFWwindow *window, unsigned int code)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::CharEvent>(code);
    }

    static inline void char_mods_callback(GLFWwindow *window, unsigned int code, int mods)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        dispatcher->Dispatch<HeaderTech::Window::Events::CharModsEvent>(code, mods);
    }

    static inline void file_drop_callback(GLFWwindow *window, int count, const char **files)
    {
        HeaderTech::Profiler::ScopedProfileMark mark("glfw_event");
        auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
        auto result = HeaderTech::Window::Events::FileDropVector{files, files + count};
        dispatcher->Dispatch<HeaderTech::Window::Events::FileDropEvent>(result);
    }


    void OpenGLWindowApi::LinkEvents()
    {
        glfwSetWindowUserPointer(m_window, m_dispatcher);
        glfwSetWindowPosCallback(m_window, &window_position_callback);
        glfwSetWindowSizeCallback(m_window, &window_size_callback);
        glfwSetWindowCloseCallback(m_window, &window_close_callback);
        glfwSetWindowRefreshCallback(m_window, &window_refresh_callback);
        glfwSetWindowFocusCallback(m_window, &window_focus_callback);
        glfwSetWindowIconifyCallback(m_window, &window_iconify_callback);
        glfwSetWindowMaximizeCallback(m_window, &window_maximize_callback);
        glfwSetFramebufferSizeCallback(m_window, &framebuffer_size_callback);
        glfwSetWindowContentScaleCallback(m_window, &window_content_scale_callback);
        glfwSetMouseButtonCallback(m_window, &mouse_button_callback);
        glfwSetCursorPosCallback(m_window, &cursor_position_callback);
        glfwSetCursorEnterCallback(m_window, &cursor_enter_callback);
        glfwSetScrollCallback(m_window, &scroll_callback);
        glfwSetKeyCallback(m_window, &key_callback);
        glfwSetCharCallback(m_window, &char_callback);
        glfwSetCharModsCallback(m_window, &char_mods_callback);
        glfwSetDropCallback(m_window, &file_drop_callback);
    }
}

#endif //HEADERTECH_OPENGLWINDOWAPIEVENTS_INL
