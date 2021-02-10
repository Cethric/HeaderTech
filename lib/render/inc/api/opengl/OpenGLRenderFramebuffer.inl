//
// Created by rogan2 on 22/12/2020.
//

#ifndef HEADERTECH_OPENGLRENDERFRAMEBUFFER_INL
#define HEADERTECH_OPENGLRENDERFRAMEBUFFER_INL

#include <api/opengl/OpenGLRenderFramebuffer.h>

namespace HeaderTech::Render::Api::OpenGL {
    inline OpenGLRenderFramebuffer::OpenGLRenderFramebuffer(
            GladGLContext *ctx,
            int width,
            int height
    ) noexcept
            : HeaderTech::Core::Api::Render::RenderFramebuffer(width, height),
              m_gl(ctx),
              m_log(HeaderTech::Logging::get_or_make_logger_async<OpenGLRenderFramebuffer>()),
              m_framebuffer(0)
    {}

    inline OpenGLRenderFramebuffer::~OpenGLRenderFramebuffer() noexcept = default;

    inline void OpenGLRenderFramebuffer::OnBuild()
    {
        SPDLOG_LOGGER_INFO(m_log, "Build framebuffer with size: {} {}", m_width, m_height);

        m_gl->CreateFramebuffers(1, &m_framebuffer);


        SPDLOG_LOGGER_INFO(m_log, "Framebuffer {} with size: {} {} has been created", m_framebuffer, m_width, m_height);
    }

    inline void OpenGLRenderFramebuffer::OnDestroy() noexcept
    {
        SPDLOG_LOGGER_INFO(m_log, "Destroy framebuffer with size: {} {}", m_width, m_height);

        m_gl->DeleteFramebuffers(1, &m_framebuffer);
    }

    inline void OpenGLRenderFramebuffer::Lock() noexcept
    {
        SPDLOG_LOGGER_TRACE(m_log, "Lock Framebuffer {}", m_framebuffer);
        m_gl->BindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
        RenderFramebuffer::Lock();
    }

    inline void OpenGLRenderFramebuffer::Unlock() noexcept
    {
        SPDLOG_LOGGER_TRACE(m_log, "Unlock Framebuffer {}", m_framebuffer);
        m_gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
        RenderFramebuffer::Unlock();
    }
}

#endif //HEADERTECH_OPENGLRENDERFRAMEBUFFER_INL
