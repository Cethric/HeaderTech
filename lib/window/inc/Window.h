//
// Created by rogan2 on 20/01/2021.
//

#ifndef HEADERTECH_WINDOW_H
#define HEADERTECH_WINDOW_H

#include <ConfigIncludes.h>
#include <WindowTypes.h>
#include <api/window/WindowApi.h>
#include <WindowTypes.h>

namespace HeaderTech {
    namespace Render {
        class RenderContext;
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

        [[nodiscard]] inline bool IsKeyPressed(HeaderTech::Core::KeyType key) const noexcept;

    protected:
        HeaderTech::Core::Api::Window::WindowApi *m_api;
        HeaderTech::Render::RenderContext *m_context;
    };
}

#endif //HEADERTECH_WINDOWINCLUDES_H
