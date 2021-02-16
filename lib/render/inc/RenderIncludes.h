//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_RENDERINCLUDES_H
#define HEADERTECH_RENDERINCLUDES_H

#include <RenderContext.h>
#include <RenderObject.h>
#include <RenderSurface.h>

#include <scene/SceneGraphRenderManagement.h>

#include <api/RenderContextApiIncludes.h>

#if defined(HEADERTECH_RENDER_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <RenderContext.inl>

#include <scene/SceneGraphRenderManagement.inl>

#endif

namespace HeaderTech::Render {
    int RenderVersion();
}

#endif //HEADERTECH_RENDERINCLUDES_H
