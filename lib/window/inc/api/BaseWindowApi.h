//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_BASEWINDOWAPI_H
#define HEADERTECH_BASEWINDOWAPI_H

#include <EventDispatcher.h>
#include <api/RenderContextApi.h>

namespace HeaderTech::Window::Api {
    class WindowApi {
    public:
        inline explicit WindowApi(HeaderTech::Events::EventDispatcher *dispatcher) noexcept: m_dispatcher(dispatcher)
        {}

        inline virtual ~WindowApi() noexcept = default;

        inline virtual bool IsOpen() noexcept = 0;

        inline virtual void SwapBuffers() noexcept = 0;

        inline virtual void MakeCurrent() noexcept = 0;

    protected:
        HeaderTech::Events::EventDispatcher *m_dispatcher;
    };
}

#endif //HEADERTECH_BASEWINDOWAPI_H
