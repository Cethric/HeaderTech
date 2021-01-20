//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_RENDER_H
#define HEADERTECH_RENDER_H

#include <RenderContext.h>
#include <RenderObject.h>
#include <RenderSurface.h>

#include <scene/SceneGraphRenderManagement.h>

#include <api/RenderContextApi.h>

#if defined(HEADERTECH_RENDER_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <RenderContext.inl>

#include <scene/SceneGraphRenderManagement.inl>

#include <api/RenderContextApi.inl>

#endif

#endif //HEADERTECH_RENDER_H
