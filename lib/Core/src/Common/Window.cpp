/*==============================================================================
 = BSD 3-Clause License
 =
 = Copyright (c) 2021, Cethric
 = All rights reserved.
 =
 = Redistribution and use in source and binary forms, with or without
 = modification, are permitted provided that the following conditions are met:
 =
 = 1. Redistributions of source code must retain the above copyright notice, this
 =    list of conditions and the following disclaimer.
 =
 = 2. Redistributions in binary form must reproduce the above copyright notice,
 =    this list of conditions and the following disclaimer in the documentation
 =    and/or other materials provided with the distribution.
 =
 = 3. Neither the name of the copyright holder nor the names of its
 =    contributors may be used to endorse or promote products derived from
 =    this software without specific prior written permission.
 =
 = THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 = AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 = IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 = DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 = FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 = DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 = SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 = CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 = OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 = OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 =============================================================================*/

#define HEADERTECH_EVENT_IMPLEMENTATION 1

#include <Core/Common/Window.hpp>
#include <Core/Events/Window/WindowSizeEvent.hpp>
#include <Core/Events/Window/FramebufferSizeEvent.hpp>
#include <Core/Events/Window/WindowContentScaleEvent.hpp>
#include <Core/Events/Window/WindowPositionEvent.hpp>
#include <Core/Events/Window/WindowIconifyEvent.hpp>
#include <Core/Events/Window/WindowMaximiseEvent.hpp>
#include <Core/Events/Window/WindowFocusEvent.hpp>
#include <Core/Events/Window/WindowRefreshEvent.hpp>
#include <Core/Events/Input/KeyInputEvent.hpp>
#include <Core/Events/Input/CharacterInputEvent.hpp>
#include <Core/Events/Input/MouseButtonEvent.hpp>
#include <Core/Events/Input/CursorPositionEvent.hpp>
#include <Core/Events/Input/CursorEnterEvent.hpp>
#include <Core/Events/Input/ScrollEvent.hpp>
#include <Core/Events/Input/FileDropEvent.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <span>

using namespace HeaderTech::Core::Common;
using namespace HeaderTech::Core::Event;
using namespace HeaderTech::Core::Events::Window;
using namespace HeaderTech::Core::Events::Input;

struct HeaderTech_Core_Export HeaderTech::Core::Common::WindowImpl {
    GLFWwindow *window;
};

template<Event AnEvent, class...Args>
inline void dispatch_event(GLFWwindow *window, Args &&...args) noexcept
{
    static_cast<Window *>(
            glfwGetWindowUserPointer(window)
    )->DispatchNow<AnEvent>(
            std::forward<Args>(args)...
    );
}

inline void process_event(GLFWwindow *window) noexcept
{
    static_cast<Window *>(
            glfwGetWindowUserPointer(window)
    )->ProcessEvent();
}

inline static void window_size_callback(GLFWwindow *window, int width, int height)
{ dispatch_event<WindowSizeEvent>(window, width, height); }

inline static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{ dispatch_event<FramebufferSizeEvent>(window, width, height); }

inline static void window_content_scale_callback(GLFWwindow *window, float xScale, float yScale)
{ dispatch_event<WindowContentScaleEvent>(window, xScale, yScale); }

inline static void window_position_callback(GLFWwindow *window, int x, int y)
{ dispatch_event<WindowPositionEvent>(window, x, y); }

inline static void window_iconify_callback(GLFWwindow *window, int iconified)
{ dispatch_event<WindowIconifyEvent>(window, iconified == GLFW_TRUE); }

inline static void window_maximize_callback(GLFWwindow *window, int maximized)
{ dispatch_event<WindowMaximiseEvent>(window, maximized == GLFW_TRUE); }

inline static void window_focus_callback(GLFWwindow *window, int focused)
{ dispatch_event<WindowFocusEvent>(window, focused == GLFW_TRUE); }

inline static void window_refresh_callback(GLFWwindow *window)
{
    dispatch_event<WindowRefreshEvent>(window);
    process_event(window);
}

inline static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    dispatch_event<KeyInputEvent>(
            window,
            key,
            scancode,
            action == GLFW_PRESS
            ? KeyInputAction::KeyPress
            : action == GLFW_RELEASE
              ? KeyInputAction::KeyRelease
              : KeyInputAction::KeyRepeat,
            mods
    );
}

inline static void char_callback(GLFWwindow *window, unsigned int codePoint, int mods)
{ dispatch_event<CharacterInputEvent>(window, codePoint, mods); }

inline static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    dispatch_event<MouseButtonEvent>(
            window,
            button,
            action == GLFW_PRESS ? MouseButtonAction::MousePress : MouseButtonAction::MouseRelease,
            mods
    );
}

inline static void cursor_position_callback(GLFWwindow *window, double xPos, double yPos)
{ dispatch_event<CursorPositionEvent>(window, xPos, yPos); }

inline static void cursor_enter_callback(GLFWwindow *window, int entered)
{ dispatch_event<CursorEnterEvent>(window, entered == GLFW_TRUE); }

inline static void scroll_callback(GLFWwindow *window, double deltaX, double deltaY)
{ dispatch_event<ScrollEvent>(window, deltaX, deltaY); }

inline static void file_drop_callback(GLFWwindow *window, int count, const char **files)
{
    auto paths = std::span<const char *>(files, static_cast<std::span<const char *>::size_type>(count));
    dispatch_event<FileDropEvent>(window, std::vector<const char *>(paths.begin(), paths.end()));
}


Window::Window(const EventDispatcherPtr &dispatcher) noexcept
        : HeaderTech::Core::Event::EventDispatcher(),
          m_impl(new WindowImpl{.window=nullptr})
{
    glfwDefaultWindowHints();
    m_impl->window = glfwCreateWindow(800, 800, "New Window", nullptr, nullptr);
    glfwSetWindowUserPointer(m_impl->window, this);
    (void) glfwSetWindowSizeCallback(m_impl->window, window_size_callback);
    (void) glfwSetFramebufferSizeCallback(m_impl->window, framebuffer_size_callback);
    (void) glfwSetWindowContentScaleCallback(m_impl->window, window_content_scale_callback);
    (void) glfwSetWindowPosCallback(m_impl->window, window_position_callback);
    (void) glfwSetWindowIconifyCallback(m_impl->window, window_iconify_callback);
    (void) glfwSetWindowMaximizeCallback(m_impl->window, window_maximize_callback);
    (void) glfwSetWindowFocusCallback(m_impl->window, window_focus_callback);
    (void) glfwSetWindowRefreshCallback(m_impl->window, window_refresh_callback);

    (void) glfwSetKeyCallback(m_impl->window, key_callback);
    (void) glfwSetCharModsCallback(m_impl->window, char_callback);
    (void) glfwSetMouseButtonCallback(m_impl->window, mouse_button_callback);
    (void) glfwSetCursorPosCallback(m_impl->window, cursor_position_callback);
    (void) glfwSetCursorEnterCallback(m_impl->window, cursor_enter_callback);
    (void) glfwSetScrollCallback(m_impl->window, scroll_callback);
    (void) glfwSetDropCallback(m_impl->window, file_drop_callback);
}

Window::~Window() noexcept
{
    glfwDestroyWindow(m_impl->window);
    delete m_impl;
}

bool Window::IsOpen() const
{
    return glfwWindowShouldClose(m_impl->window) == GLFW_FALSE;
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_impl->window, GLFW_TRUE);
}
