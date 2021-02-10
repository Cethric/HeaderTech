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
    { if (m_isBuilt) { Destroy(); }}

    inline void RenderFramebuffer::Resize(int width, int height)
    {
        auto built = m_isBuilt;
        if (built) { Destroy(); }
        m_width = width;
        m_height = height;
        if (built) { Build(); }
    }

    inline void RenderFramebuffer::Build()
    { m_isBuilt = true; }

    inline void RenderFramebuffer::Destroy() noexcept
    { m_isBuilt = false; }

    inline void RenderFramebuffer::Lock() noexcept
    { m_isLocked = true; }

    inline void RenderFramebuffer::Unlock() noexcept
    { m_isLocked = false; }
}

#endif //HEADERTECH_RENDERFRAMEBUFFER_INL
