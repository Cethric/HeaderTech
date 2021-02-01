// dear imgui: Renderer Backend for modern OpenGL with shaders / programmatic pipeline
// - Desktop GL: 2.x 3.x 4.x
// - Embedded GL: ES 2.0 (WebGL 1.0), ES 3.0 (WebGL 2.0)
// This needs to be used along with a Platform Backend (e.g. GLFW, SDL, Win32, custom..)

// Implemented features:
//  [X] Renderer: User texture binding. Use 'GLuint' OpenGL texture identifier as void*/ImTextureID. Read the FAQ about ImTextureID!
//  [X] Renderer: Multi-viewport support. Enable with 'io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable'.
//  [x] Renderer: Desktop GL only: Support for large meshes (64k+ vertices) with 16-bit indices.

// You can copy and use unmodified imgui_impl_* files in your project. See examples/ folder for examples of using this.
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// About Desktop OpenGL function loaders:
//  Modern Desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.

// About GLSL version:
//  The 'glsl_version' initialization parameter should be NULL (default) or a "#version XXX" string.
//  On computer platform the GLSL version default to "#version 130". On OpenGL ES 3 platform it defaults to "#version 300 es"
//  Only override if your GL version doesn't handle this GLSL version. See GLSL version table at the top of imgui_impl_opengl3.cpp.

#pragma once

#include "imgui.h"      // IMGUI_IMPL_API
#include <glad/gl.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD2

// Backend API
IMGUI_IMPL_API bool ImGui_ImplOpenGL3_Init(GladGLContext *gl, const char *glsl_version = nullptr);

IMGUI_IMPL_API void ImGui_ImplOpenGL3_Shutdown(GladGLContext *gl);

IMGUI_IMPL_API void ImGui_ImplOpenGL3_NewFrame(GladGLContext *gl);

IMGUI_IMPL_API void ImGui_ImplOpenGL3_RenderDrawData(GladGLContext *gl, ImDrawData *draw_data);

// (Optional) Called by Init/NewFrame/Shutdown
IMGUI_IMPL_API bool ImGui_ImplOpenGL3_CreateFontsTexture(GladGLContext *gl);

IMGUI_IMPL_API void ImGui_ImplOpenGL3_DestroyFontsTexture(GladGLContext *gl);

IMGUI_IMPL_API bool ImGui_ImplOpenGL3_CreateDeviceObjects(GladGLContext *gl);

IMGUI_IMPL_API void ImGui_ImplOpenGL3_DestroyDeviceObjects(GladGLContext *gl);
