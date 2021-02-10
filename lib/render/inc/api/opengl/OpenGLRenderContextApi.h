//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_OPENGLRENDERCONTEXTAPI_H
#define HEADERTECH_OPENGLRENDERCONTEXTAPI_H

#include <glad/gl.h>

#include <api/render/RenderApiIncludes.h>

#include <api/opengl/OpenGLWindowApi.h>
#include <api/opengl/OpenGLRenderFramebuffer.h>


struct ImGuiContext;

namespace HeaderTech::Render::Api::OpenGL {
    class OpenGLRenderContextApi final : public HeaderTech::Core::Api::Render::RenderContextApi {
    public:
        inline explicit OpenGLRenderContextApi(HeaderTech::Window::Api::OpenGL::OpenGLWindowApi *api) noexcept;

        inline ~OpenGLRenderContextApi() noexcept final;

        [[nodiscard]] inline const GladGLContext &Gl() const noexcept;

        [[nodiscard]] inline HeaderTech::Core::Api::Render::RenderFramebuffer *
        CreateFramebuffer(int width, int height) noexcept final;

        inline void PrepareRenderDebugGUI() noexcept final;

        inline void DestroyRenderDebugGUI() noexcept final;

        inline void WillRenderDebugGUI() noexcept final;

        inline void DidRenderDebugGUI() noexcept final;

    protected:
        GladGLContext m_gl;

    protected:
        ImGuiContext *m_debugGuiContext;

    private:
        HeaderTech::Window::Api::OpenGL::OpenGLWindowApi *m_window;
    };
}

#endif //HEADERTECH_OPENGLRENDERCONTEXTAPI_H
