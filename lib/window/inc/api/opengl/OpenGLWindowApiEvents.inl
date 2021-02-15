//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_OPENGLWINDOWAPIEVENTS_INL
#define HEADERTECH_OPENGLWINDOWAPIEVENTS_INL

#include <EventsIncludes.h>
#include <ProfilerIncludes.h>
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

#include <imgui_impl_glfw.h>

namespace HeaderTech::Window::Api::OpenGL {
    using Dispatcher = HeaderTech::Events::EventDispatcher;

    namespace Callbacks {
        static inline void window_position_callback(GLFWwindow *window, int x, int y)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::WindowPositionEvent>(x, y);
        }

        static inline void window_size_callback(GLFWwindow *window, int width, int height)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::WindowSizeEvent>(width, height);
        }

        static inline void window_close_callback(GLFWwindow *window)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::WindowCloseEvent>();
        }

        static inline void window_refresh_callback(GLFWwindow *window)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::WindowRefreshEvent>();
        }

        static inline void window_focus_callback(GLFWwindow *window, int focused)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::WindowFocusEvent>(focused == GLFW_TRUE);
        }

        static inline void window_iconify_callback(GLFWwindow *window, int iconified)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::WindowIconifyEvent>(iconified == GLFW_TRUE);
        }

        static inline void window_maximize_callback(GLFWwindow *window, int maximized)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::WindowMaximizeEvent>(maximized == GLFW_TRUE);
        }

        static inline void framebuffer_size_callback(GLFWwindow *window, int width, int height)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::FramebufferSizeEvent>(width, height);
        }

        static inline void window_content_scale_callback(GLFWwindow *window, float x, float y)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::WindowContentScaleEvent>(x, y);
        }

        static inline void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::MouseButtonEvent>(
                    button,
                    static_cast<HeaderTech::Window::Events::MouseButtonAction>(action),
                    mods
            );
            ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
        }

        static inline void cursor_position_callback(GLFWwindow *window, double x, double y)
        {
            static double mX = 0;
            static double mY = 0;
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            double dX = x - mX;
            mX = x;
            double dY = y - mY;
            mY = y;
            dispatcher->DispatchNow<HeaderTech::Window::Events::CursorPositionEvent>(x, y, dX, dY);
        }

        static inline void cursor_enter_callback(GLFWwindow *window, int entered)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::CursorEnterEvent>(entered == GLFW_TRUE);
        }

        static inline void scroll_callback(GLFWwindow *window, double x, double y)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::ScrollEvent>(x, y);
            ImGui_ImplGlfw_ScrollCallback(window, x, y);
        }

        static inline void key_callback(GLFWwindow *window, int key, int scan, int action, int mods)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::KeyEvent>(
                    key,
                    scan,
                    static_cast<HeaderTech::Window::Events::KeyAction>(action),
                    mods
            );
            ImGui_ImplGlfw_KeyCallback(window, key, scan, action, mods);
        }

        static inline void char_callback(GLFWwindow *window, unsigned int code)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::CharEvent>(code);
            ImGui_ImplGlfw_CharCallback(window, code);
        }

        static inline void char_mods_callback(GLFWwindow *window, unsigned int code, int mods)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            dispatcher->DispatchNow<HeaderTech::Window::Events::CharModsEvent>(code, mods);
        }

        static inline void file_drop_callback(GLFWwindow *window, int count, const char **files)
        {
            rmt_ScopedCPUSample(glfw_event, RMTSF_None);
            auto dispatcher = static_cast<Dispatcher *>(glfwGetWindowUserPointer(window));
            auto result = HeaderTech::Window::Events::FileDropVector{files, files + count};
            dispatcher->DispatchNow<HeaderTech::Window::Events::FileDropEvent>(result);
        }
    }


    void OpenGLWindowApi::LinkEvents()
    {
        glfwSetWindowUserPointer(m_window, m_dispatcher);
        glfwSetWindowPosCallback(m_window, &Callbacks::window_position_callback);
        glfwSetWindowSizeCallback(m_window, &Callbacks::window_size_callback);
        glfwSetWindowCloseCallback(m_window, &Callbacks::window_close_callback);
        glfwSetWindowRefreshCallback(m_window, &Callbacks::window_refresh_callback);
        glfwSetWindowFocusCallback(m_window, &Callbacks::window_focus_callback);
        glfwSetWindowIconifyCallback(m_window, &Callbacks::window_iconify_callback);
        glfwSetWindowMaximizeCallback(m_window, &Callbacks::window_maximize_callback);
        glfwSetFramebufferSizeCallback(m_window, &Callbacks::framebuffer_size_callback);
        glfwSetWindowContentScaleCallback(m_window, &Callbacks::window_content_scale_callback);
        glfwSetMouseButtonCallback(m_window, &Callbacks::mouse_button_callback);
        glfwSetCursorPosCallback(m_window, &Callbacks::cursor_position_callback);
        glfwSetCursorEnterCallback(m_window, &Callbacks::cursor_enter_callback);
        glfwSetScrollCallback(m_window, &Callbacks::scroll_callback);
        glfwSetKeyCallback(m_window, &Callbacks::key_callback);
        glfwSetCharCallback(m_window, &Callbacks::char_callback);
        glfwSetCharModsCallback(m_window, &Callbacks::char_mods_callback);
        glfwSetDropCallback(m_window, &Callbacks::file_drop_callback);
        glfwSetMonitorCallback(ImGui_ImplGlfw_MonitorCallback);
    }
}

#endif //HEADERTECH_OPENGLWINDOWAPIEVENTS_INL
