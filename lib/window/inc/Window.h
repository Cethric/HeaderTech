//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_WINDOW_H
#define HEADERTECH_WINDOW_H

#include <Config.h>

namespace HeaderTech {
    namespace Render {
        class RenderContext;
    }
    namespace Window::Api {
        class WindowApi;
    }
    namespace Events {
        class EventDispatcher;
    }
}

namespace HeaderTech::Window {
    class Window {
    public:
        inline explicit Window(
                const HeaderTech::Config::WindowConfig &config,
                HeaderTech::Events::EventDispatcher *dispatcher
        ) noexcept;

        inline ~Window() noexcept;

        inline bool IsOpen() noexcept;

        inline void Swap() noexcept;

        inline void ToggleFullscreen() noexcept;

        [[nodiscard]] inline int GetWidth() const noexcept;

        [[nodiscard]] inline int GetHeight() const noexcept;

        [[nodiscard]] inline HeaderTech::Render::RenderContext *GetRenderContext() const noexcept;

    protected:
        HeaderTech::Window::Api::WindowApi *m_api;
        HeaderTech::Render::RenderContext *m_context;
    };
}


#if defined(HEADERTECH_WINDOW_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <Window.inl>

#endif

#endif //HEADERTECH_WINDOW_H
