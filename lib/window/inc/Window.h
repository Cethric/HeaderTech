//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_WINDOW_H
#define HEADERTECH_WINDOW_H

#include <Config.h>
#include <Render.h>
#include <Events.h>
#include <api/WindowApi.h>

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
