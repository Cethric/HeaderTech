//
// Created by rogan2 on 22/12/2020.
//

#ifndef HEADERTECH_OPENGLRENDERFRAMEBUFFER_H
#define HEADERTECH_OPENGLRENDERFRAMEBUFFER_H

#include <glad/gl.h>
#include <api/render/RenderApiIncludes.h>
#include <LoggingIncludes.h>

namespace HeaderTech::Render::Api::OpenGL {
    class OpenGLRenderFramebuffer final : public HeaderTech::Core::Api::Render::RenderFramebuffer {
    private:
        friend class OpenGLRenderContextApi;

        inline explicit OpenGLRenderFramebuffer(GladGLContext *ctx, int width, int height) noexcept;

    public:
        inline ~OpenGLRenderFramebuffer() noexcept final;

        inline void OnBuild() final;

        inline void OnDestroy() noexcept final;

        inline void Lock() noexcept final;

        inline void Unlock() noexcept final;

    private:
        GladGLContext *m_gl;
        HeaderTech::Logging::Logger m_log;

    private:
        GLuint m_framebuffer;
    };
}

#endif //HEADERTECH_OPENGLRENDERFRAMEBUFFER_H
