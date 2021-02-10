//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_OPENGLWINDOWAPI_H
#define HEADERTECH_OPENGLWINDOWAPI_H

#define GLFW_INCLUDE_NONE 1

#include <GLFW/glfw3.h>

#include <api/window/WindowApi.h>
#include <ConfigIncludes.h>

#include <WindowTypes.h>

namespace HeaderTech::Window::Api::OpenGL {
    class OpenGLWindowApi final : public HeaderTech::Core::Api::Window::WindowApi {
    public:
        inline OpenGLWindowApi(
                const HeaderTech::Config::WindowConfig &config,
                HeaderTech::Events::EventDispatcher *dispatcher,
                GLFWwindow *shared = nullptr
        ) noexcept;

        inline ~OpenGLWindowApi() noexcept final;

        inline bool IsOpen() noexcept final;

        inline void SwapBuffers() noexcept final;

        inline void ToggleFullscreen() noexcept final;

        inline void MakeCurrent() noexcept final;

        inline GLFWwindow *GetOwnedWindow() const noexcept;

        [[nodiscard]] inline int GetWidth() const noexcept final;

        [[nodiscard]] inline int GetHeight() const noexcept final;

        [[nodiscard]] inline bool IsKeyPressed(HeaderTech::Core::KeyType key) const noexcept final;

    protected:
        inline void LinkEvents();

    protected:
        GLFWwindow *m_window;
    };
}

#endif //HEADERTECH_OPENGLWINDOWAPI_H
