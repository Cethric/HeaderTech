//
// Created by rogan2 on 19/11/2020.
//

#include <Window.h>

#include <api/WindowApi.inl>

namespace HeaderTech::Window {
    using Dispatcher = HeaderTech::Events::EventDispatcher;

    Window::Window(
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

    Window::~Window() noexcept
    {
        delete m_context;
        delete m_api;
    }

    bool Window::IsOpen() noexcept
    { return m_api->IsOpen(); }

    void Window::Swap() noexcept
    { m_api->SwapBuffers(); }

    HeaderTech::Render::RenderContext *Window::GetRenderContext() const noexcept
    { return m_context; }

}
