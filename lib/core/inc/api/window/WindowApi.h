//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_WINDOWAPI_H
#define HEADERTECH_WINDOWAPI_H

#include <EventDispatcher.h>
#include <WindowTypes.h>

#include <glm/glm.hpp>

namespace HeaderTech::Core::Api::Window {
    class WindowApi {
    public:
        inline explicit WindowApi(HeaderTech::Events::EventDispatcher *dispatcher) noexcept: m_dispatcher(dispatcher)
        {}

        inline virtual ~WindowApi() noexcept = default;

        inline virtual bool IsOpen() noexcept = 0;

        inline virtual void SwapBuffers() noexcept = 0;

        inline virtual void ToggleFullscreen() noexcept = 0;

        inline virtual void MakeCurrent() noexcept = 0;

        [[nodiscard]] inline virtual glm::ivec2 GetSize() const noexcept = 0;

        [[nodiscard]] inline virtual bool IsKeyPressed(KeyType key) const noexcept = 0;

    protected:
        HeaderTech::Events::EventDispatcher *m_dispatcher;
    };
}

#endif //HEADERTECH_WINDOWAPI_H
