//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_RENDERCONTEXTAPIINCLUDES_H
#define HEADERTECH_RENDERCONTEXTAPIINCLUDES_H

#include <api/opengl/OpenGLRenderContextApi.h>
#include <api/opengl/OpenGLRenderFramebuffer.h>

#if defined(HEADERTECH_RENDER_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <api/opengl/OpenGLRenderContextApi.inl>
#include <api/opengl/OpenGLRenderFramebuffer.inl>
#include <api/opengl/OpenGLDebugGui.inl>

#endif

#endif //HEADERTECH_RENDERCONTEXTAPIINCLUDES_H
