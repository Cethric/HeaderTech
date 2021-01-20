//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_BASERENDERCONTEXTAPI_H
#define HEADERTECH_BASERENDERCONTEXTAPI_H

#include <api/BaseWindowApi.h>
#include <api/RenderFramebuffer.h>

#include <imgui.h>

namespace HeaderTech::Render::Api {
    class RenderContextApi {
    public:
        inline explicit RenderContextApi(HeaderTech::Window::Api::WindowApi *api) noexcept
                : m_api(api)
        {}

        inline virtual ~RenderContextApi() noexcept = default;

        inline void MakeCurrent() noexcept
        { m_api->MakeCurrent(); }

        virtual inline void PrepareRenderDebugGUI() noexcept = 0;

        virtual inline void DestroyRenderDebugGUI() noexcept = 0;

        virtual inline void WillRenderDebugGUI() noexcept = 0;

        virtual inline void DidRenderDebugGUI() noexcept = 0;

        [[nodiscard]]

        virtual inline RenderFramebuffer *CreateFramebuffer(int width, int height) noexcept
        { return new RenderFramebuffer(width, height); }

    protected:
        HeaderTech::Window::Api::WindowApi *m_api;
    };
}

#endif //HEADERTECH_BASERENDERCONTEXTAPI_H
