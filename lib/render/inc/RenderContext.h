//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_RENDERCONTEXT_H
#define HEADERTECH_RENDERCONTEXT_H

namespace HeaderTech::Render {
    namespace Api {
        class RenderContextApi;

        class RenderFramebuffer;
    }

    class RenderContext {
    public:
        inline explicit RenderContext(HeaderTech::Render::Api::RenderContextApi *api);

        inline ~RenderContext();

        inline void MakeCurrent();

        inline void WillRenderDebugGUI() noexcept;

        inline void DidRenderDebugGUI() noexcept;

        inline Api::RenderFramebuffer *CreateFramebuffer(int width, int height);

    private:
        HeaderTech::Render::Api::RenderContextApi *m_api;
    };

}

#endif //HEADERTECH_RENDERCONTEXT_H
