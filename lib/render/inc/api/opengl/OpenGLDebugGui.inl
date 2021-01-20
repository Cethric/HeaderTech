//
// Created by rogan2 on 22/12/2020.
//

#ifndef HEADERTECH_OPENGLDEBUGGUI_INL
#define HEADERTECH_OPENGLDEBUGGUI_INL

#include "OpenGLRenderContextApi.inl"

#include <imgui_internal.h>

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32 1

#include <GLFW/glfw3native.h>

#endif

namespace HeaderTech::Render::Api::OpenGL {
    namespace details {
        static inline void OpenGLRenderStatePrep(
                DebugGuiData *data,
                ImDrawData *draw_data,
                int fb_width,
                int fb_height,
                GLuint vertex_array_object
        )
        {
            auto gl = data->gl;
            // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
            gl->Enable(GL_BLEND);
            gl->BlendEquation(GL_FUNC_ADD);
            gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            gl->Disable(GL_CULL_FACE);
            gl->Disable(GL_DEPTH_TEST);
            gl->Enable(GL_SCISSOR_TEST);
            gl->Disable(GL_PRIMITIVE_RESTART);
            gl->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            // Support for GL 4.5 rarely used glClipControl(GL_UPPER_LEFT)
            bool clip_origin_lower_left = true;
            GLenum current_clip_origin = 0;
            gl->GetIntegerv(GL_CLIP_ORIGIN, (GLint *) &current_clip_origin);
            if (current_clip_origin == GL_UPPER_LEFT)
                clip_origin_lower_left = false;

            gl->Viewport(0, 0, (GLsizei) fb_width, (GLsizei) fb_height);
            float L = draw_data->DisplayPos.x;
            float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
            float T = draw_data->DisplayPos.y;
            float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
            if (!clip_origin_lower_left) {
                float tmp = T;
                T = B;
                B = tmp;
            } // Swap top and bottom if origin is upper left
            const float ortho_projection[4][4] =
                    {
                            {2.0f / (R - L),    0.0f,              0.0f,  0.0f},
                            {0.0f,              2.0f / (T - B),    0.0f,  0.0f},
                            {0.0f,              0.0f,              -1.0f, 0.0f},
                            {(R + L) / (L - R), (T + B) / (B - T), 0.0f,  1.0f},
                    };
            gl->UseProgram(data->program);
            gl->Uniform1i(data->attribLocationTex, 0);
            gl->UniformMatrix4fv(data->attribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);

            gl->BindSampler(0, 0);
            gl->BindVertexArray(vertex_array_object);

            // Bind vertex/index buffers and setup attributes for ImDrawVert
            gl->BindBuffer(GL_ARRAY_BUFFER, data->vboHandle);
            gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->elementsHandle);
            gl->EnableVertexAttribArray(data->attribLocationVtxPos);
            gl->EnableVertexAttribArray(data->attribLocationVtxUV);
            gl->EnableVertexAttribArray(data->attribLocationVtxColor);
            gl->VertexAttribPointer(
                    data->attribLocationVtxPos,
                    2,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(ImDrawVert),
                    (GLvoid *) IM_OFFSETOF(ImDrawVert, pos)
            );
            gl->VertexAttribPointer(
                    data->attribLocationVtxUV,
                    2,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(ImDrawVert),
                    (GLvoid *) IM_OFFSETOF(ImDrawVert, uv)
            );
            gl->VertexAttribPointer(
                    data->attribLocationVtxColor,
                    4,
                    GL_UNSIGNED_BYTE,
                    GL_TRUE,
                    sizeof(ImDrawVert),
                    (GLvoid *) IM_OFFSETOF(ImDrawVert, col)
            );
        }

        static inline void OpenGLRenderDrawData(ImDrawData *draw_data, DebugGuiData *data)
        {
            auto gl = data->gl;
            int fb_width = (int) (draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
            int fb_height = (int) (draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
            if (fb_width <= 0 || fb_height <= 0)
                return;

            // Backup GL state
            GLenum last_active_texture;
            gl->GetIntegerv(GL_ACTIVE_TEXTURE, (GLint *) &last_active_texture);
            gl->ActiveTexture(GL_TEXTURE0);
            GLuint last_program;
            gl->GetIntegerv(GL_CURRENT_PROGRAM, (GLint *) &last_program);
            GLuint last_texture;
            gl->GetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *) &last_texture);
            GLuint last_sampler;
            gl->GetIntegerv(GL_SAMPLER_BINDING, (GLint *) &last_sampler);
            GLuint last_array_buffer;
            gl->GetIntegerv(GL_ARRAY_BUFFER_BINDING, (GLint *) &last_array_buffer);
            GLuint last_vertex_array_object;
            gl->GetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint *) &last_vertex_array_object);
            GLint last_polygon_mode[2];
            gl->GetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
            GLint last_viewport[4];
            gl->GetIntegerv(GL_VIEWPORT, last_viewport);
            GLint last_scissor_box[4];
            gl->GetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
            GLenum last_blend_src_rgb;
            gl->GetIntegerv(GL_BLEND_SRC_RGB, (GLint *) &last_blend_src_rgb);
            GLenum last_blend_dst_rgb;
            gl->GetIntegerv(GL_BLEND_DST_RGB, (GLint *) &last_blend_dst_rgb);
            GLenum last_blend_src_alpha;
            gl->GetIntegerv(GL_BLEND_SRC_ALPHA, (GLint *) &last_blend_src_alpha);
            GLenum last_blend_dst_alpha;
            gl->GetIntegerv(GL_BLEND_DST_ALPHA, (GLint *) &last_blend_dst_alpha);
            GLenum last_blend_equation_rgb;
            gl->GetIntegerv(GL_BLEND_EQUATION_RGB, (GLint *) &last_blend_equation_rgb);
            GLenum last_blend_equation_alpha;
            gl->GetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint *) &last_blend_equation_alpha);
            GLboolean last_enable_blend = gl->IsEnabled(GL_BLEND);
            GLboolean last_enable_cull_face = gl->IsEnabled(GL_CULL_FACE);
            GLboolean last_enable_depth_test = gl->IsEnabled(GL_DEPTH_TEST);
            GLboolean last_enable_scissor_test = gl->IsEnabled(GL_SCISSOR_TEST);
            GLboolean last_enable_primitive_restart = gl->IsEnabled(GL_PRIMITIVE_RESTART);

            // Setup desired GL state
            // Recreate the VAO every time (this is to easily allow multiple GL contexts to be rendered to. VAO are not shared among GL contexts)
            // The renderer would actually work without any VAO bound, but then our VertexAttrib calls would overwrite the default one currently bound.
            GLuint vertex_array_object = 0;
            gl->GenVertexArrays(1, &vertex_array_object);
            OpenGLRenderStatePrep(data, draw_data, fb_width, fb_height, vertex_array_object);

            // Will project scissor/clipping rectangles into framebuffer space
            ImVec2 clip_off = draw_data->DisplayPos;         // (0,0) unless using multi-viewports
            ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

            // Render command lists
            for (int n = 0; n < draw_data->CmdListsCount; n++) {
                const ImDrawList *cmd_list = draw_data->CmdLists[n];

                // Upload vertex/index buffers
                gl->BufferData(
                        GL_ARRAY_BUFFER,
                        (GLsizeiptr) cmd_list->VtxBuffer.Size * (int) sizeof(ImDrawVert),
                        (const GLvoid *) cmd_list->VtxBuffer.Data,
                        GL_STREAM_DRAW
                );
                gl->BufferData(
                        GL_ELEMENT_ARRAY_BUFFER,
                        (GLsizeiptr) cmd_list->IdxBuffer.Size * (int) sizeof(ImDrawIdx),
                        (const GLvoid *) cmd_list->IdxBuffer.Data,
                        GL_STREAM_DRAW
                );

                for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
                    const ImDrawCmd *pcmd = &cmd_list->CmdBuffer[cmd_i];
                    if (pcmd->UserCallback != nullptr) {
                        // User callback, registered via ImDrawList::AddCallback()
                        // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                        if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                            OpenGLRenderStatePrep(data, draw_data, fb_width, fb_height, vertex_array_object);
                        else
                            pcmd->UserCallback(cmd_list, pcmd);
                    } else {
                        // Project scissor/clipping rectangles into framebuffer space
                        ImVec4 clip_rect;
                        clip_rect.x = (pcmd->ClipRect.x - clip_off.x) * clip_scale.x;
                        clip_rect.y = (pcmd->ClipRect.y - clip_off.y) * clip_scale.y;
                        clip_rect.z = (pcmd->ClipRect.z - clip_off.x) * clip_scale.x;
                        clip_rect.w = (pcmd->ClipRect.w - clip_off.y) * clip_scale.y;

                        if (clip_rect.x < fb_width &&
                            clip_rect.y < fb_height &&
                            clip_rect.z >= 0.0f &&
                            clip_rect.w >= 0.0f) {
                            // Apply scissor/clipping rectangle
                            gl->Scissor(
                                    (int) clip_rect.x,
                                    (int) (fb_height - clip_rect.w),
                                    (int) (clip_rect.z - clip_rect.x),
                                    (int) (clip_rect.w - clip_rect.y)
                            );

                            // Bind texture, Draw
                            gl->BindTexture(GL_TEXTURE_2D, (GLuint) (intptr_t) pcmd->TextureId);

                            gl->DrawElementsBaseVertex(
                                    GL_TRIANGLES,
                                    (GLsizei) pcmd->ElemCount,
                                    sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT,
                                    (void *) (intptr_t) (pcmd->IdxOffset * sizeof(ImDrawIdx)),
                                    (GLint) pcmd->VtxOffset
                            );
                        }
                    }
                }
            }

            // Destroy the temporary VAO
            gl->DeleteVertexArrays(1, &vertex_array_object);

            // Restore modified GL state
            gl->UseProgram(last_program);
            gl->BindTexture(GL_TEXTURE_2D, last_texture);
            gl->BindSampler(0, last_sampler);
            gl->ActiveTexture(last_active_texture);
            gl->BindVertexArray(last_vertex_array_object);
            gl->BindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
            gl->BlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
            gl->BlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
            if (last_enable_blend) gl->Enable(GL_BLEND); else gl->Disable(GL_BLEND);
            if (last_enable_cull_face) gl->Enable(GL_CULL_FACE); else gl->Disable(GL_CULL_FACE);
            if (last_enable_depth_test) gl->Enable(GL_DEPTH_TEST); else gl->Disable(GL_DEPTH_TEST);
            if (last_enable_scissor_test) gl->Enable(GL_SCISSOR_TEST); else gl->Disable(GL_SCISSOR_TEST);
            if (last_enable_primitive_restart) gl->Enable(GL_PRIMITIVE_RESTART); else gl->Disable(GL_PRIMITIVE_RESTART);
            gl->PolygonMode(GL_FRONT_AND_BACK, (GLenum) last_polygon_mode[0]);
            gl->Viewport(last_viewport[0], last_viewport[1], (GLsizei) last_viewport[2], (GLsizei) last_viewport[3]);
            gl->Scissor(
                    last_scissor_box[0],
                    last_scissor_box[1],
                    (GLsizei) last_scissor_box[2],
                    (GLsizei) last_scissor_box[3]
            );
        }

        static inline void OpenGLPlatformRenderer(ImGuiViewport *viewport, void *render_arg)
        {
            auto data = static_cast<DebugGuiData *>(render_arg);
            if (!(viewport->Flags & ImGuiViewportFlags_NoRendererClear)) {
                data->gl->ClearColor(0, 0, 0, 1);
                data->gl->Clear(GL_COLOR_BUFFER_BIT);
            }
            OpenGLRenderDrawData(viewport->DrawData, data);
        }

        static inline void PrepareOpenGLViewports(const DebugGuiData &gl)
        {
            ImGuiPlatformIO &platform_io = ImGui::GetPlatformIO();
            platform_io.Renderer_RenderWindow = OpenGLPlatformRenderer;
        }

        static inline void PrepareOpenGL(const DebugGuiData &gl, ImGuiIO &io)
        {
            io.BackendRendererName = "HeaderTech::Renderer";
            io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
            io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                PrepareOpenGLViewports(gl);
        }

        static inline void OpenGLCreateFontTexture(DebugGuiData *data)
        {
            auto gl = data->gl;
            auto &io = ImGui::GetIO();

            unsigned char *pixels;
            int width, height;
            io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

            // Upload texture to graphics system
            GLint last_texture;
            gl->GetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
            gl->GenTextures(1, &data->fontTexture);
            gl->BindTexture(GL_TEXTURE_2D, data->fontTexture);
            gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            gl->PixelStorei(GL_UNPACK_ROW_LENGTH, 0);
            gl->TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

            // Store our identifier
            io.Fonts->TexID = (ImTextureID) (intptr_t) data->fontTexture;

            // Restore state
            gl->BindTexture(GL_TEXTURE_2D, last_texture);
        }

        static inline void OpenGLDestroyFontTexture(DebugGuiData *data)
        {
            if (data->fontTexture) {
                auto gl = data->gl;
                auto &io = ImGui::GetIO();
                gl->DeleteTextures(1, &data->fontTexture);
                io.Fonts->TexID = nullptr;
                data->fontTexture = 0;
            }
        }

        static inline void OpenGLCreateObjects(DebugGuiData *data)
        {
            auto gl = data->gl;
            GLint last_texture, last_array_buffer, last_vertex_array;
            gl->GetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
            gl->GetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
            gl->GetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

            const GLchar *vertex_shader_glsl_410_core =
                    "layout (location = 0) in vec2 Position;\n"
                    "layout (location = 1) in vec2 UV;\n"
                    "layout (location = 2) in vec4 Color;\n"
                    "uniform mat4 ProjMtx;\n"
                    "out vec2 Frag_UV;\n"
                    "out vec4 Frag_Color;\n"
                    "void main()\n"
                    "{\n"
                    "    Frag_UV = UV;\n"
                    "    Frag_Color = Color;\n"
                    "    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
                    "}\n";

            const GLchar *fragment_shader_glsl_410_core =
                    "in vec2 Frag_UV;\n"
                    "in vec4 Frag_Color;\n"
                    "uniform sampler2D Texture;\n"
                    "layout (location = 0) out vec4 Out_Color;\n"
                    "void main()\n"
                    "{\n"
                    "    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
                    "}\n";

            // Select shaders matching our GLSL versions
            const GLchar *vertex_shader = vertex_shader_glsl_410_core;
            const GLchar *fragment_shader = fragment_shader_glsl_410_core;

            // Create shaders
            const GLchar *vertex_shader_with_version[2] = {"#version 460\n", vertex_shader};
            auto g_VertHandle = gl->CreateShader(GL_VERTEX_SHADER);
            gl->ShaderSource(g_VertHandle, 2, vertex_shader_with_version, nullptr);
            gl->CompileShader(g_VertHandle);
//            CheckShader(g_VertHandle, "vertex shader");

            const GLchar *fragment_shader_with_version[2] = {"#version 460\n", fragment_shader};
            auto g_FragHandle = gl->CreateShader(GL_FRAGMENT_SHADER);
            gl->ShaderSource(g_FragHandle, 2, fragment_shader_with_version, nullptr);
            gl->CompileShader(g_FragHandle);
//            CheckShader(g_FragHandle, "fragment shader");

            data->program = gl->CreateProgram();
            gl->AttachShader(data->program, g_VertHandle);
            gl->AttachShader(data->program, g_FragHandle);
            gl->LinkProgram(data->program);
//            CheckProgram(data->program, "shader program");

            data->attribLocationTex = gl->GetUniformLocation(data->program, "Texture");
            data->attribLocationProjMtx = gl->GetUniformLocation(data->program, "ProjMtx");
            data->attribLocationVtxPos = (GLuint) gl->GetAttribLocation(data->program, "Position");
            data->attribLocationVtxUV = (GLuint) gl->GetAttribLocation(data->program, "UV");
            data->attribLocationVtxColor = (GLuint) gl->GetAttribLocation(data->program, "Color");

            // Create buffers
            gl->GenBuffers(1, &data->vboHandle);
            gl->GenBuffers(1, &data->elementsHandle);

            OpenGLCreateFontTexture(data);

            // Restore modified GL state
            gl->BindTexture(GL_TEXTURE_2D, last_texture);
            gl->BindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
            gl->BindVertexArray(last_vertex_array);

            gl->DetachShader(data->program, g_VertHandle);
            gl->DetachShader(data->program, g_FragHandle);
            gl->DeleteShader(g_VertHandle);
            gl->DeleteShader(g_FragHandle);
        }

        static inline void OpenGLDestroyObjects(DebugGuiData *data)
        {
            auto gl = data->gl;
            gl->DeleteBuffers(1, &data->vboHandle);
            gl->DeleteBuffers(1, &data->elementsHandle);
            gl->DeleteProgram(data->program);

            OpenGLDestroyFontTexture(data);
        }

        namespace GLFW {
            struct PlatformData {
                bool owned = true;
                GLFWwindow *window = nullptr;
                int ignoreWindowPos = 0;
                int ignoreWindowSize = 0;
            };

            static inline void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
            {
                auto data = *(static_cast<DebugGuiData **>(glfwGetWindowUserPointer(window)) + 1);
                [[likely]] if (data->parentMouseButtonCallback && window == data->mainWindow) {
                    data->parentMouseButtonCallback(window, button, action, mods);
                }

                if (action == GLFW_PRESS && button > 0 && button < ImGuiMouseButton_COUNT) {
                    data->buttonPressed[button] = true;
                }
            }

            static inline void ScrollCallback(GLFWwindow *window, double x, double y)
            {
                auto data = *(static_cast<DebugGuiData **>(glfwGetWindowUserPointer(window)) + 1);
                [[likely]] if (data->parentScrollCallback && window == data->mainWindow) {
                    data->parentScrollCallback(window, x, y);
                }

                ImGuiIO &io = ImGui::GetIO();
                io.MouseWheelH += (float) x;
                io.MouseWheel += (float) y;
            }

            static inline void KeyCallback(GLFWwindow *window, int key, int scan, int action, int mods)
            {
                auto data = *(static_cast<DebugGuiData **>(glfwGetWindowUserPointer(window)) + 1);
                [[likely]] if (data->parentKeyCallback && window == data->mainWindow) {
                    data->parentKeyCallback(window, key, scan, action, mods);
                }

                ImGuiIO &io = ImGui::GetIO();
                if (action == GLFW_PRESS)
                    io.KeysDown[key] = true;
                if (action == GLFW_RELEASE)
                    io.KeysDown[key] = false;

                // Modifiers are not reliable across systems
                io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
                io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
                io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
#ifdef _WIN32
                io.KeySuper = false;
#else
                io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif
            }

            static inline void CharCallback(GLFWwindow *window, unsigned int key)
            {
                auto data = *(static_cast<DebugGuiData **>(glfwGetWindowUserPointer(window)) + 1);
                [[likely]] if (data->parentCharCallback && window == data->mainWindow) {
                    data->parentCharCallback(window, key);
                }

                ImGuiIO &io = ImGui::GetIO();
                io.AddInputCharacter(key);
            }

            static inline void WindowCloseCallback(GLFWwindow *window)
            {
                if (auto viewport = ImGui::FindViewportByPlatformHandle(window)) {
                    viewport->PlatformRequestClose = true;
                }
            }

            static inline void WindowPosCallback(GLFWwindow *window, int x, int y)
            {
                if (auto viewport = ImGui::FindViewportByPlatformHandle(window)) {
                    if (auto *data = static_cast<PlatformData *>(viewport->PlatformUserData)) {
                        bool ignore_event = (ImGui::GetFrameCount() <= data->ignoreWindowPos + 1);
                        if (ignore_event)
                            return;
                    }
                    viewport->PlatformRequestMove = true;
                }
            }

            static inline void WindowSizeCallback(GLFWwindow *window, int, int)
            {
                if (auto viewport = ImGui::FindViewportByPlatformHandle(window)) {
                    if (auto *data = static_cast<PlatformData *>(viewport->PlatformUserData)) {
                        bool ignore_event = (ImGui::GetFrameCount() <= data->ignoreWindowSize + 1);
                        if (ignore_event)
                            return;
                    }
                    viewport->PlatformRequestResize = true;
                }
            }

            static inline void CreateViewportWindow(ImGuiViewport *viewport)
            {
                auto data = static_cast<DebugGuiData *>(ImGui::GetIO().UserData);

                auto platformData = IM_NEW(PlatformData)();
                viewport->PlatformUserData = platformData;

                glfwWindowHint(GLFW_VISIBLE, false);
                glfwWindowHint(GLFW_FOCUSED, false);
                glfwWindowHint(GLFW_FOCUS_ON_SHOW, false);
                glfwWindowHint(GLFW_DECORATED, (viewport->Flags & ImGuiViewportFlags_NoDecoration) == 0);
                glfwWindowHint(GLFW_FLOATING, (viewport->Flags & ImGuiViewportFlags_TopMost) != 0);
                platformData->window = glfwCreateWindow(
                        (int) viewport->Size.x,
                        (int) viewport->Size.y,
                        "No Title Yet",

                        nullptr,
                        data->mainWindow
                );
                platformData->owned = true;
                viewport->PlatformHandle = (void *) platformData->window;
#ifdef _WIN32
                viewport->PlatformHandleRaw = glfwGetWin32Window(platformData->window);
#endif
                glfwSetWindowPos(platformData->window, (int) viewport->Pos.x, (int) viewport->Pos.y);

                // Install GLFW callbacks for secondary viewports
                glfwSetWindowUserPointer(platformData->window, glfwGetWindowUserPointer(data->mainWindow));
                glfwSetMouseButtonCallback(platformData->window, &MouseButtonCallback);
                glfwSetScrollCallback(platformData->window, &ScrollCallback);
                glfwSetKeyCallback(platformData->window, &KeyCallback);
                glfwSetCharCallback(platformData->window, &CharCallback);
                glfwSetWindowCloseCallback(platformData->window, &WindowCloseCallback);
                glfwSetWindowPosCallback(platformData->window, &WindowPosCallback);
                glfwSetWindowSizeCallback(platformData->window, &WindowSizeCallback);
                glfwMakeContextCurrent(platformData->window);
//                glfwSwapInterval(0);
            }

            static inline void DestroyViewportWindow(ImGuiViewport *viewport)
            {
                if (auto *data = static_cast<PlatformData *>(viewport->PlatformUserData)) {
                    if (data->owned) {
#if defined(_WIN32)
                        HWND hwnd = (HWND) viewport->PlatformHandleRaw;
                        ::RemovePropA(hwnd, "IMGUI_VIEWPORT");
#endif
                        glfwDestroyWindow(data->window);
                    }
                    data->window = nullptr;
                    IM_DELETE(data);
                }
                viewport->PlatformUserData = viewport->PlatformHandle = nullptr;
            }

#if  defined(_WIN32)
            static WNDPROC g_GlfwWndProc = nullptr;

            static LRESULT CALLBACK WndProcNoInputs(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
            {
                if (msg == WM_NCHITTEST) {
                    auto *viewport = (ImGuiViewport *) ::GetPropA(hWnd, "IMGUI_VIEWPORT");
                    if (viewport->Flags & ImGuiViewportFlags_NoInputs)
                        return HTTRANSPARENT;
                }
                return ::CallWindowProc(g_GlfwWndProc, hWnd, msg, wParam, lParam);
            }

#endif

            static inline void ShowWindow(ImGuiViewport *viewport)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);

#if defined(_WIN32)
                // GLFW hack: Hide icon from task bar
                HWND hwnd = (HWND) viewport->PlatformHandleRaw;
                if (viewport->Flags & ImGuiViewportFlags_NoTaskBarIcon) {
                    LONG ex_style = ::GetWindowLong(hwnd, GWL_EXSTYLE);
                    ex_style &= ~WS_EX_APPWINDOW;
                    ex_style |= WS_EX_TOOLWINDOW;
                    ::SetWindowLong(hwnd, GWL_EXSTYLE, ex_style);
                }

                // GLFW hack: install hook for WM_NCHITTEST message handler
                ::SetPropA(hwnd, "IMGUI_VIEWPORT", viewport);
                if (g_GlfwWndProc == nullptr)
                    g_GlfwWndProc = (WNDPROC) ::GetWindowLongPtr(hwnd, GWLP_WNDPROC);
                ::SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR) WndProcNoInputs);

                // GLFW hack: GLFW 3.2 has a bug where glfwShowWindow() also activates/focus the window.
                // The fix was pushed to GLFW repository on 2018/01/09 and should be included in GLFW 3.3 via a GLFW_FOCUS_ON_SHOW window attribute.
                // See https://github.com/glfw/glfw/issues/1189
                // FIXME-VIEWPORT: Implement same work-around for Linux/OSX in the meanwhile.
                if (viewport->Flags & ImGuiViewportFlags_NoFocusOnAppearing) {
                    ::ShowWindow(hwnd, SW_SHOWNA);
                    return;
                }
#endif

                glfwShowWindow(data->window);
            }

            static inline void SetWindowPos(ImGuiViewport *viewport, ImVec2 pos)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
                data->ignoreWindowPos = ImGui::GetFrameCount();
                glfwSetWindowPos(data->window, (int) pos.x, (int) pos.y);
            }

            static inline ImVec2 GetWindowPos(ImGuiViewport *viewport)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
                int w = 0, h = 0;
                glfwGetWindowSize(data->window, &w, &h);
                return ImVec2((float) w, (float) h);
            }

            static inline void SetWindowSize(ImGuiViewport *viewport, ImVec2 size)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
#if __APPLE__ && !GLFW_HAS_OSX_WINDOW_POS_FIX
                // Native OS windows are positioned from the bottom-left corner on macOS, whereas on other platforms they are
    // positioned from the upper-left corner. GLFW makes an effort to convert macOS style coordinates, however it
    // doesn't handle it when changing size. We are manually moving the window in order for changes of size to be based
    // on the upper-left corner.
    int x, y, width, height;
    glfwGetWindowPos(data->Window, &x, &y);
    glfwGetWindowSize(data->Window, &width, &height);
    glfwSetWindowPos(data->Window, x, y - height + size.y);
#endif
                data->ignoreWindowSize = ImGui::GetFrameCount();
                glfwSetWindowSize(data->window, (int) size.x, (int) size.y);
            }

            static inline ImVec2 GetWindowSize(ImGuiViewport *viewport)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
                int w = 0, h = 0;
                glfwGetWindowSize(data->window, &w, &h);
                return ImVec2((float) w, (float) h);
            }

            static inline void SetWindowFocus(ImGuiViewport *viewport)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
                glfwFocusWindow(data->window);
            }

            static inline bool GetWindowFocus(ImGuiViewport *viewport)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
                return glfwGetWindowAttrib(data->window, GLFW_FOCUSED) != 0;
            }

            static inline bool GetWindowMinimized(ImGuiViewport *viewport)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
                return glfwGetWindowAttrib(data->window, GLFW_ICONIFIED) != 0;
            }

            static inline void SetWindowTitle(ImGuiViewport *viewport, const char *title)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
                glfwSetWindowTitle(data->window, title);
            }

            static inline void RenderWindow(ImGuiViewport *viewport, void *)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
                glfwMakeContextCurrent(data->window);
            }

            static inline void SwapWindowBuffer(ImGuiViewport *viewport, void *)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
                glfwMakeContextCurrent(data->window);
                glfwSwapBuffers(data->window);
            }

            static inline void SetWindowAlpha(ImGuiViewport *viewport, float alpha)
            {
                auto *data = static_cast<PlatformData *>(viewport->PlatformUserData);
                glfwSetWindowOpacity(data->window, alpha);
            }

#if defined(_WIN32) && !defined(__GNUC__)
#define HAS_WIN32_IME   1

#include <imm.h>

#ifdef _MSC_VER
#pragma comment(lib, "imm32")
#endif

            static inline void SetImeInputPos(ImGuiViewport *viewport, ImVec2 pos)
            {
                COMPOSITIONFORM cf = {
                        CFS_FORCE_POSITION,
                        {(LONG) (pos.x - viewport->Pos.x), (LONG) (pos.y - viewport->Pos.y)},
                        {0, 0, 0, 0}
                };
                if (HWND hwnd = (HWND) viewport->PlatformHandleRaw) {
                    if (HIMC himc = ::ImmGetContext(hwnd)) {
                        ::ImmSetCompositionWindow(himc, &cf);
                        ::ImmReleaseContext(hwnd, himc);
                    }
                }
            }

#else
#define HAS_WIN32_IME   0
#endif

        }

        static inline void PrepareImGuiCallbacks(DebugGuiData &data, ImGuiIO &io, GLFWwindow *window)
        {
            data.parentUserPointer = glfwGetWindowUserPointer(window);
            data.parentMouseButtonCallback = glfwSetMouseButtonCallback(window, &GLFW::MouseButtonCallback);
            data.parentScrollCallback = glfwSetScrollCallback(window, &GLFW::ScrollCallback);
            data.parentKeyCallback = glfwSetKeyCallback(window, &GLFW::KeyCallback);
            data.parentCharCallback = glfwSetCharCallback(window, &GLFW::CharCallback);
//            g_PrevUserCallbackMonitor = glfwSetMonitorCallback(ImGui_ImplGlfw_MonitorCallback);
            auto array = new void *[2];
            *(array + 0) = data.parentUserPointer;
            *(array + 1) = &data;
            glfwSetWindowUserPointer(window, array);

            // Update monitors the first time (note: monitor callback are broken in GLFW 3.2 and earlier, see github.com/glfw/glfw/issues/784)
//            ImGui_ImplGlfw_UpdateMonitors();
//            glfwSetMonitorCallback(ImGui_ImplGlfw_MonitorCallback);
        }

        static inline void PrepareImGuiViewports(DebugGuiData &data, ImGuiIO &io, GLFWwindow *window)
        {
            ImGuiPlatformIO &platform_io = ImGui::GetPlatformIO();
            platform_io.Platform_CreateWindow = GLFW::CreateViewportWindow;
            platform_io.Platform_DestroyWindow = GLFW::DestroyViewportWindow;
            platform_io.Platform_ShowWindow = GLFW::ShowWindow;
            platform_io.Platform_SetWindowPos = GLFW::SetWindowPos;
            platform_io.Platform_GetWindowPos = GLFW::GetWindowPos;
            platform_io.Platform_SetWindowSize = GLFW::SetWindowSize;
            platform_io.Platform_GetWindowSize = GLFW::GetWindowSize;
            platform_io.Platform_SetWindowFocus = GLFW::SetWindowFocus;
            platform_io.Platform_GetWindowFocus = GLFW::GetWindowFocus;
            platform_io.Platform_GetWindowMinimized = GLFW::GetWindowMinimized;
            platform_io.Platform_SetWindowTitle = GLFW::SetWindowTitle;
            platform_io.Platform_RenderWindow = GLFW::RenderWindow;
            platform_io.Platform_SwapBuffers = GLFW::SwapWindowBuffer;
            platform_io.Platform_SetWindowAlpha = GLFW::SetWindowAlpha;
#if HAS_WIN32_IME
            platform_io.Platform_SetImeInputPos = GLFW::SetImeInputPos;
#endif

            // Register main window handle (which is owned by the main application, not by us)
            // This is mostly for simplicity and consistency, so that our code (e.g. mouse handling etc.) can use same logic for main and secondary viewports.
            ImGuiViewport *main_viewport = ImGui::GetMainViewport();

            auto platformData = IM_NEW(GLFW::PlatformData)();
            platformData->window = window;
            platformData->owned = false;
            main_viewport->PlatformUserData = platformData;
            main_viewport->PlatformHandle = (void *) window;
        }

        static inline void PrepareImGui(DebugGuiData &data, ImGuiIO &io, GLFWwindow *window)
        {
            io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
            io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
//            io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;    // We can create multi-viewports on the Platform side (optional)
#ifdef _WIN32
            io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport; // We can set io.MouseHoveredViewport correctly (optional, not easy)
#endif
            io.BackendPlatformName = "HeaderTech::GLFW";

            // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
            io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
            io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
            io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
            io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
            io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
            io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
            io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
            io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
            io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
            io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
            io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
            io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
            io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
            io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
            io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
            io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
            io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
            io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
            io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
            io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
            io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
            io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

//            io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
//            io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;
            io.ClipboardUserData = window;

            // Create mouse cursors
            // (By design, on X11 cursors are user configurable and some cursors may be missing. When a cursor doesn't exist,
            // GLFW will emit an error which will often be printed by the app, so we temporarily disable error reporting.
            // Missing cursors will return NULL and our _UpdateMouseCursor() function will use the Arrow cursor instead.)
            GLFWerrorfun prev_error_callback = glfwSetErrorCallback(nullptr);
            data.mouseCursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
            data.mouseCursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
            data.mouseCursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
            data.mouseCursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
            data.mouseCursors[ImGuiMouseCursor_Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
            data.mouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);
            data.mouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
            data.mouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
            data.mouseCursors[ImGuiMouseCursor_NotAllowed] = glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);
            glfwSetErrorCallback(prev_error_callback);

            PrepareImGuiCallbacks(data, io, window);

            // Our mouse update function expect PlatformHandle to be filled for the main viewport
            ImGuiViewport *main_viewport = ImGui::GetMainViewport();
            main_viewport->PlatformHandle = (void *) window;
#ifdef _WIN32
            main_viewport->PlatformHandleRaw = glfwGetWin32Window(window);
#endif
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                PrepareImGuiViewports(data, io, window);
        }

        static inline void UpdateMousePosAndButtons(DebugGuiData &data, ImGuiIO &io)
        {
            for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) {
                // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
                io.MouseDown[i] = data.buttonPressed[i] || glfwGetMouseButton(data.mainWindow, i) != 0;
                data.buttonPressed[i] = false;
            }

            // Update mouse position
            const ImVec2 mouse_pos_backup = io.MousePos;
            io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
            io.MouseHoveredViewport = 0;
            ImGuiPlatformIO &platform_io = ImGui::GetPlatformIO();
            for (int n = 0; n < platform_io.Viewports.Size; n++) {
                ImGuiViewport *viewport = platform_io.Viewports[n];
                auto window = (GLFWwindow *) viewport->PlatformHandle;
                IM_ASSERT(window != nullptr);
#ifdef __EMSCRIPTEN__
                const bool focused = true;
IM_ASSERT(platform_io.Viewports.Size == 1);
#else
                const bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) != 0;
#endif
                if (focused) {
                    if (io.WantSetMousePos) {
                        glfwSetCursorPos(window, (double) (mouse_pos_backup.x - viewport->Pos.x),
                                         (double) (mouse_pos_backup.y - viewport->Pos.y));
                    } else {
                        double mouse_x, mouse_y;
                        glfwGetCursorPos(window, &mouse_x, &mouse_y);
                        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                            // Multi-viewport mode: mouse position in OS absolute coordinates (io.MousePos is (0,0) when the mouse is on the upper-left of the primary monitor)
                            int window_x, window_y;
                            glfwGetWindowPos(window, &window_x, &window_y);
                            io.MousePos = ImVec2(
                                    (float) mouse_x + (float) window_x,
                                    (float) mouse_y + (float) window_y
                            );
                        } else {
                            // Single viewport mode: mouse position in client window coordinates (io.MousePos is (0,0) when the mouse is on the upper-left corner of the app window)
                            io.MousePos = ImVec2((float) mouse_x, (float) mouse_y);
                        }
                    }
                    for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
                        io.MouseDown[i] |= glfwGetMouseButton(window, i) != 0;
                }

#if defined(_WIN32)
                const bool window_no_input = (viewport->Flags & ImGuiViewportFlags_NoInputs) != 0;
                glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, window_no_input);
                if (glfwGetWindowAttrib(window, GLFW_HOVERED) && !window_no_input)
                    io.MouseHoveredViewport = viewport->ID;
#endif
            }
        }

        static inline void UpdateMouseCursor(DebugGuiData &data, ImGuiIO &io)
        {
            if ((io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) ||
                glfwGetInputMode(data.mainWindow, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
                return;

            ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
            ImGuiPlatformIO &platform_io = ImGui::GetPlatformIO();
            for (int n = 0; n < platform_io.Viewports.Size; n++) {
                auto window = (GLFWwindow *) platform_io.Viewports[n]->PlatformHandle;
                if (imgui_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor) {
                    // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                } else {
                    // Show OS mouse cursor
                    // FIXME-PLATFORM: Unfocused windows seems to fail changing the mouse cursor with GLFW 3.2, but 3.3 works here.
                    glfwSetCursor(window, data.mouseCursors[imgui_cursor] ? data.mouseCursors[imgui_cursor]
                                                                          : data.mouseCursors[ImGuiMouseCursor_Arrow]);
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }
            }
        }

        static inline void UpdateGamepads(DebugGuiData &data, ImGuiIO &io)
        {
            memset(io.NavInputs, 0, sizeof(io.NavInputs));
            if ((io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) == 0)
                return;

            // Update gamepad inputs
#define MAP_BUTTON(NAV_NO, BUTTON_NO)       { if (buttons_count > BUTTON_NO && buttons[BUTTON_NO] == GLFW_PRESS) io.NavInputs[NAV_NO] = 1.0f; }
#define MAP_ANALOG(NAV_NO, AXIS_NO, V0, V1) { float v = (axes_count > AXIS_NO) ? axes[AXIS_NO] : V0; v = (v - V0) / (V1 - V0); if (v > 1.0f) v = 1.0f; if (io.NavInputs[NAV_NO] < v) io.NavInputs[NAV_NO] = v; }
            int axes_count = 0, buttons_count = 0;
            const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
            const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
            MAP_BUTTON(ImGuiNavInput_Activate, 0);     // Cross / A
            MAP_BUTTON(ImGuiNavInput_Cancel, 1);     // Circle / B
            MAP_BUTTON(ImGuiNavInput_Menu, 2);     // Square / X
            MAP_BUTTON(ImGuiNavInput_Input, 3);     // Triangle / Y
            MAP_BUTTON(ImGuiNavInput_DpadLeft, 13);    // D-Pad Left
            MAP_BUTTON(ImGuiNavInput_DpadRight, 11);    // D-Pad Right
            MAP_BUTTON(ImGuiNavInput_DpadUp, 10);    // D-Pad Up
            MAP_BUTTON(ImGuiNavInput_DpadDown, 12);    // D-Pad Down
            MAP_BUTTON(ImGuiNavInput_FocusPrev, 4);     // L1 / LB
            MAP_BUTTON(ImGuiNavInput_FocusNext, 5);     // R1 / RB
            MAP_BUTTON(ImGuiNavInput_TweakSlow, 4);     // L1 / LB
            MAP_BUTTON(ImGuiNavInput_TweakFast, 5);     // R1 / RB
            MAP_ANALOG(ImGuiNavInput_LStickLeft, 0, -0.3f, -0.9f);
            MAP_ANALOG(ImGuiNavInput_LStickRight, 0, +0.3f, +0.9f);
            MAP_ANALOG(ImGuiNavInput_LStickUp, 1, +0.3f, +0.9f);
            MAP_ANALOG(ImGuiNavInput_LStickDown, 1, -0.3f, -0.9f);
#undef MAP_BUTTON
#undef MAP_ANALOG
            if (axes_count > 0 && buttons_count > 0)
                io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
            else
                io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
        }


        static inline void UpdateImGui(DebugGuiData &data, ImGuiIO &io)
        {
            UpdateMousePosAndButtons(data, io);
            UpdateMouseCursor(data, io);
            UpdateGamepads(data, io);
        }
    }

    void OpenGLRenderContextApi::PrepareRenderDebugGUI() noexcept
    {
        ImGui::SetCurrentContext(m_debugGuiContext);

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
//        ImGuiStyle &style = ImGui::GetStyle();
//        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
//            style.WindowRounding = 0.0f;
//            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//        }

        m_debugData.gl = &m_gl;
        m_debugData.program = 0;
        io.UserData = &m_debugData;

        details::PrepareImGui(m_debugData, io, m_window->GetOwnedWindow());

        details::PrepareOpenGL(m_debugData, io);
    }

    void OpenGLRenderContextApi::DestroyRenderDebugGUI() noexcept
    {
        details::OpenGLDestroyObjects(&m_debugData);
        ImGui::DestroyPlatformWindows();
        ImGui::DestroyContext(m_debugGuiContext);
    }

    void OpenGLRenderContextApi::WillRenderDebugGUI() noexcept
    {
        static bool show_demo_window = true;
        if (m_debugData.program == 0) {
            details::OpenGLCreateObjects(&m_debugData);
        }
        auto &io = ImGui::GetIO();

        IM_ASSERT(io.Fonts->IsBuilt() &&
                  "Font atlas not built! It is generally built by the renderer backend. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

        // Setup display size (every frame to accommodate for window resizing)
        int w, h;
        int display_w, display_h;
        glfwGetWindowSize(m_window->GetOwnedWindow(), &w, &h);
        glfwGetFramebufferSize(m_window->GetOwnedWindow(), &display_w, &display_h);
        io.DisplaySize = ImVec2((float) w, (float) h);
        if (w > 0 && h > 0)
            io.DisplayFramebufferScale = ImVec2(
                    (float) display_w / (float) w,
                    (float) display_h / (float) h
            );
//        if (g_WantUpdateMonitors)
//            ImGui_ImplGlfw_UpdateMonitors();

        // Setup time step
        static double g_Time = 0;
        double current_time = glfwGetTime();
        io.DeltaTime = g_Time > 0.0 ? (float) (current_time - g_Time) : (float) (1.0f / 60.0f);
        g_Time = current_time;

        details::UpdateImGui(m_debugData, io);

        ImGui::NewFrame();
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
    }

    void OpenGLRenderContextApi::DidRenderDebugGUI() noexcept
    {
        ImGuiIO &io = ImGui::GetIO();
        ImGui::Render();
        m_gl.Viewport(0, 0, m_window->GetWidth(), m_window->GetHeight());
        m_gl.ClearColor(0, 0, 0, 1);
        m_gl.Clear(GL_COLOR_BUFFER_BIT);
        details::OpenGLRenderDrawData(ImGui::GetDrawData(), &m_debugData);

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            auto *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault(m_window, &m_debugData);
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}

#endif //HEADERTECH_OPENGLDEBUGGUI_INL
