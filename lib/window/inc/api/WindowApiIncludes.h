//
// Created by rogan2 on 20/11/2020.
//

#ifndef HEADERTECH_WINDOWAPIINCLUDES2_H
#define HEADERTECH_WINDOWAPIINCLUDES2_H

#include <api/window/WindowApiIncludes.h>
#include <api/GLFWKeyMapping.h>
#include <api/opengl/OpenGLWindowApi.h>

#if defined(HEADERTECH_WINDOW_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <api/opengl/OpenGLWindowApi.inl>
#include <api/opengl/OpenGLWindowApiEvents.inl>

#endif

#endif //HEADERTECH_WINDOWAPIINCLUDES2_H
