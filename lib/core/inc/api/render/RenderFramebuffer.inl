//
// Created by rogan2 on 22/12/2020.
//

#ifndef HEADERTECH_RENDERFRAMEBUFFER_INL
#define HEADERTECH_RENDERFRAMEBUFFER_INL

#include <api/render/RenderFramebuffer.h>

namespace HeaderTech::Core::Api::Render {
    inline RenderFramebuffer::RenderFramebuffer(int width, int height) noexcept
            : m_width(width),
              m_height(height),
              m_isBuilt(false),
              m_isLocked(false)
    {}

    inline RenderFramebuffer::~RenderFramebuffer() noexcept
    { if (m_isBuilt) { WillDestroy(); }}

    inline void RenderFramebuffer::Resize(int width, int height)
    {
        auto wasBuilt = m_isBuilt;
        if (wasBuilt) { WillDestroy(); }
        m_width = width;
        m_height = height;
        if (wasBuilt) { WillBuild(); }
    }

    void RenderFramebuffer::Build()
    { WillBuild(); }

    void RenderFramebuffer::Destroy() noexcept
    { WillDestroy(); }

    inline void RenderFramebuffer::Lock() noexcept
    { m_isLocked = true; }

    inline void RenderFramebuffer::Unlock() noexcept
    { m_isLocked = false; }

    void RenderFramebuffer::WillBuild()
    {
        OnBuild();
        m_isBuilt = true;
    }

    void RenderFramebuffer::WillDestroy() noexcept
    {
        OnDestroy();
        m_isBuilt = false;
    }
}

#endif //HEADERTECH_RENDERFRAMEBUFFER_INL
