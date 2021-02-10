//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_RENDERCONTEXT_INL
#define HEADERTECH_RENDERCONTEXT_INL

#include <RenderContext.h>

namespace HeaderTech::Render {
    inline RenderContext::RenderContext(HeaderTech::Core::Api::Render::RenderContextApi *api) : m_api(api)
    {}

    inline RenderContext::~RenderContext()
    { delete m_api; }

    inline void RenderContext::MakeCurrent()
    { m_api->MakeCurrent(); }

    void RenderContext::WillRenderDebugGUI() noexcept
    { m_api->WillRenderDebugGUI(); }

    void RenderContext::DidRenderDebugGUI() noexcept
    { m_api->DidRenderDebugGUI(); }

    inline HeaderTech::Core::Api::Render::RenderFramebuffer *RenderContext::CreateFramebuffer(int width, int height)
    { return m_api->CreateFramebuffer(width, height); }
}

#endif //HEADERTECH_RENDERCONTEXT_INL
