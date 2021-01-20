//
// Created by rogan2 on 19/11/2020.
//

#include <Window.h>
#include <Render.h>
#include <Events.h>
#include <api/WindowApi.h>

#include <api/WindowApi.inl>

namespace HeaderTech::Window {
    using Dispatcher = HeaderTech::Events::EventDispatcher;

    inline Window::Window(
            const HeaderTech::Config::WindowConfig &config,
            Dispatcher *dispatcher
    ) noexcept
            : m_api(nullptr),
              m_context(nullptr)
    {
        switch (config.render.api) {
            case Config::RenderConfigApi_OpenGL: {
                auto windowApi = new HeaderTech::Window::Api::OpenGL::OpenGLWindowApi(config, dispatcher);
                auto contextApi = new HeaderTech::Render::Api::OpenGL::OpenGLRenderContextApi(windowApi);
                m_api = windowApi;
                m_context = new HeaderTech::Render::RenderContext(contextApi);
            }
                break;
            case Config::RenderConfigApi_Vulkan:
            case Config::RenderConfigApi_Metal:
            case Config::RenderConfigApi_Direct3D:
            default:
                break;
        }
    }

    inline Window::~Window() noexcept
    {
        delete m_context;
        delete m_api;
    }

    inline bool Window::IsOpen() noexcept
    { return m_api->IsOpen(); }

    inline void Window::Swap() noexcept
    { m_api->SwapBuffers(); }

    void Window::ToggleFullscreen() noexcept
    { m_api->ToggleFullscreen(); }

    inline int Window::GetWidth() const noexcept
    { return m_api->GetWidth(); }

    inline int Window::GetHeight() const noexcept
    { return m_api->GetHeight(); }

    inline HeaderTech::Render::RenderContext *Window::GetRenderContext() const noexcept
    { return m_context; }

}
