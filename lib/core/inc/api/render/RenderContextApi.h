//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_RENDERCONTEXTAPI_H
#define HEADERTECH_RENDERCONTEXTAPI_H

#include <api/window/WindowApi.h>
#include <api/render/RenderFramebuffer.h>

namespace HeaderTech::Core::Api::Render {
    class RenderContextApi {
    public:
        inline explicit RenderContextApi(HeaderTech::Core::Api::Window::WindowApi *api) noexcept
                : m_api(api)
        {}

        inline virtual ~RenderContextApi() noexcept = default;

        inline void MakeCurrent() noexcept
        { m_api->MakeCurrent(); }

        virtual inline void PrepareRenderDebugGUI() noexcept = 0;

        virtual inline void DestroyRenderDebugGUI() noexcept = 0;

        virtual inline void WillRenderDebugGUI() noexcept = 0;

        virtual inline void DidRenderDebugGUI() noexcept = 0;

        [[nodiscard]] virtual inline RenderFramebuffer *CreateFramebuffer(int width, int height) noexcept = 0;

    protected:
        HeaderTech::Core::Api::Window::WindowApi *m_api;
    };
}

#endif //HEADERTECH_RENDERCONTEXTAPI_H
