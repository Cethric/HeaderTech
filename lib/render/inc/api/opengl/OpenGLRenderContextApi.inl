//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_OPENGLRENDERCONTEXTAPI_INL
#define HEADERTECH_OPENGLRENDERCONTEXTAPI_INL

#include <string_view>

#include <api/opengl/OpenGLRenderContextApi.h>
#include <api/opengl/OpenGLRenderFramebuffer.h>
#include <Logging.h>

#include <GLFW/glfw3.h>

namespace HeaderTech::Render::Api::OpenGL {
    namespace detail {
        static inline void opengl_debug_callback(
                GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei /*length*/,
                const GLchar *message,
                const void * /*userParam*/
        )
        {
            auto log = HeaderTech::Logging::get_or_make_logger_async("OpenGL");
            std::string_view debug_source, debug_type;
            switch (source) {
                case GL_DEBUG_SOURCE_API:
                    debug_source = "API";
                    break;
                case GL_DEBUG_SOURCE_APPLICATION:
                    debug_source = "Application";
                    break;
                default:
                case GL_DEBUG_SOURCE_OTHER:
                    debug_source = "Other";
                    break;
                case GL_DEBUG_SOURCE_SHADER_COMPILER:
                    debug_source = "Shader Compiler";
                    break;
                case GL_DEBUG_SOURCE_THIRD_PARTY:
                    debug_source = "Third Party";
                    break;
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                    debug_source = "Window System";
                    break;
            }
            switch (type) {
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                    debug_type = "Deprecated Behavior";
                    break;
                case GL_DEBUG_TYPE_ERROR:
                    debug_type = "Error";
                    break;
                case GL_DEBUG_TYPE_MARKER:
                    debug_type = "Marker";
                    break;
                default:
                case GL_DEBUG_TYPE_OTHER:
                    debug_type = "Other";
                    break;
                case GL_DEBUG_TYPE_PERFORMANCE:
                    debug_type = "Performance";
                    break;
                case GL_DEBUG_TYPE_POP_GROUP:
                    debug_type = "Pop Group";
                    break;
                case GL_DEBUG_TYPE_PORTABILITY:
                    debug_type = "Portability";
                    break;
                case GL_DEBUG_TYPE_PUSH_GROUP:
                    debug_type = "Push Group";
                    break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                    debug_type = "Undefined Behavior";
                    break;
            }
            switch (severity) {
                case GL_DEBUG_SEVERITY_HIGH:
                    log->critical("ID ({}) TYPE ({}) SOURCE ({}) : {}", id, debug_type, debug_source, message);
                    break;
                case GL_DEBUG_SEVERITY_LOW:
                    log->info("ID ({}) TYPE ({}) SOURCE ({}) : {}", id, debug_type, debug_source, message);
                    break;
                case GL_DEBUG_SEVERITY_MEDIUM:
                    log->warn("ID ({}) TYPE ({}) SOURCE ({}) : {}", id, debug_type, debug_source, message);
                    break;
                default:
                case GL_DEBUG_SEVERITY_NOTIFICATION:
                    log->debug("ID ({}) TYPE ({}) SOURCE ({}) : {}", id, debug_type, debug_source, message);
                    break;
            }
        }
    }

    inline OpenGLRenderContextApi::OpenGLRenderContextApi(
            HeaderTech::Window::Api::OpenGL::OpenGLWindowApi *api
    ) noexcept
            : HeaderTech::Render::Api::RenderContextApi(api),
              m_gl{},
              m_window(api),
              m_debugGuiContext(ImGui::CreateContext(nullptr)),
              m_debugData{
                      .gl=nullptr,
                      .program=0,
                      .vboHandle=0,
                      .elementsHandle=0,
                      .attribLocationTex=0,
                      .attribLocationProjMtx=0,
                      .attribLocationVtxPos=0,
                      .attribLocationVtxUV=0,
                      .attribLocationVtxColor=0,
                      .fontTexture=0,
                      .mouseCursors={nullptr},
                      .buttonPressed={false},
                      .mainWindow=api->GetOwnedWindow(),
                      .parentUserPointer=nullptr,
                      .parentMouseButtonCallback=nullptr,
                      .parentScrollCallback=nullptr,
                      .parentKeyCallback=nullptr,
                      .parentCharCallback=nullptr,
              }
    {
        api->MakeCurrent();
        gladLoadGLContext(&m_gl, glfwGetProcAddress);
        m_gl.DebugMessageCallback(&detail::opengl_debug_callback, nullptr);

        PrepareRenderDebugGUI();

        m_gl.ClearColor(0, 1, 0, 1);
        m_gl.Clear(GL_COLOR_BUFFER_BIT);
        api->SwapBuffers();
        m_gl.ClearColor(0, 1, 0, 1);
        m_gl.Clear(GL_COLOR_BUFFER_BIT);
    }

    inline OpenGLRenderContextApi::~OpenGLRenderContextApi() noexcept
    {
        auto data = (void **) glfwGetWindowUserPointer(m_window->GetOwnedWindow());
        delete[] data;
        glfwSetWindowUserPointer(m_window->GetOwnedWindow(), m_debugData.parentUserPointer);
    };

    inline const GladGLContext &OpenGLRenderContextApi::Gl() const noexcept
    { return m_gl; }

    HeaderTech::Render::Api::RenderFramebuffer *
    OpenGLRenderContextApi::CreateFramebuffer(int width, int height) noexcept
    { return new OpenGLRenderFramebuffer(&m_gl, width, height); }

}

#endif //HEADERTECH_OPENGLRENDERCONTEXTAPI_INL
