//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_RENDERCONTEXT_H
#define HEADERTECH_RENDERCONTEXT_H

#include <api/render/RenderApiIncludes.h>

namespace HeaderTech::Render {
    class RenderContext {
    public:
        inline explicit RenderContext(HeaderTech::Core::Api::Render::RenderContextApi *api);

        inline ~RenderContext();

        inline void MakeCurrent();

        inline void WillRenderDebugGUI() noexcept;

        inline void DidRenderDebugGUI() noexcept;

        inline HeaderTech::Core::Api::Render::RenderFramebuffer *CreateFramebuffer(int width, int height);

    private:
        HeaderTech::Core::Api::Render::RenderContextApi *m_api;
    };

}

#endif //HEADERTECH_RENDERCONTEXT_H
