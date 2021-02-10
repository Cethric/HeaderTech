//
// Created by rogan2 on 20/01/2021.
//

#ifndef HEADERTECH_WINDOW_INL
#define HEADERTECH_WINDOW_INL

#include <Window.h>
#include <RenderIncludes.h>
#include <EventsIncludes.h>

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

    glm::ivec2 Window::GetSize() const noexcept
    { return m_api->GetSize(); }

    inline HeaderTech::Render::RenderContext *Window::GetRenderContext() const noexcept
    { return m_context; }

    inline bool Window::IsKeyPressed(HeaderTech::Core::KeyType key) const noexcept
    { return m_api->IsKeyPressed(key); }

}

#endif //HEADERTECH_WINDOW_INL
