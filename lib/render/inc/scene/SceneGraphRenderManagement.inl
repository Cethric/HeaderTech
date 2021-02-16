//
// Created by rogan2 on 21/12/2020.
//

#ifndef HEADERTECH_SCENEGRAPHRENDERMANAGEMENT_INL
#define HEADERTECH_SCENEGRAPHRENDERMANAGEMENT_INL

#include <scene/SceneGraphRenderManagement.h>

#include <RuntimeIncludes.h>

namespace HeaderTech::Render::SceneGraph {
    inline SceneGraphRenderManagement::SceneGraphRenderManagement(
            HeaderTech::Runtime::Runtime *runtime,
            const RenderSurfaceOptions &options
    ) noexcept
            : SceneGraphRenderManagement(runtime->GetWindow().GetRenderContext(), options)
    {}

    inline SceneGraphRenderManagement::SceneGraphRenderManagement(
            HeaderTech::Render::RenderContext *context,
            const RenderSurfaceOptions &options
    ) noexcept
            : m_context(context),
              m_framebuffer(
                      context->CreateFramebuffer(
                              options.window_size.x,
                              options.window_size.y
                      )
              )
    {}

    inline SceneGraphRenderManagement::~SceneGraphRenderManagement() noexcept
    { delete m_framebuffer; }

    inline void SceneGraphRenderManagement::ResizeFramebuffer(int width, int height) noexcept
    { m_framebuffer->Resize(width, height); }

    inline void SceneGraphRenderManagement::Activate() noexcept
    { m_framebuffer->Build(); }

    inline void SceneGraphRenderManagement::Deactivate() noexcept
    { m_framebuffer->Destroy(); }

    inline void SceneGraphRenderManagement::WillPushScene() noexcept
    {}

    inline void SceneGraphRenderManagement::WillPopScene() noexcept
    {}

    inline void SceneGraphRenderManagement::DidPushScene() noexcept
    {}

    inline void SceneGraphRenderManagement::DidPopScene() noexcept
    {}

    inline void SceneGraphRenderManagement::TickScene(double delta, double lag) noexcept
    {}

    void SceneGraphRenderManagement::WillRenderScene() noexcept
    { m_framebuffer->Lock(); }

    inline void SceneGraphRenderManagement::RenderScene(double offset) noexcept
    {}

    void SceneGraphRenderManagement::DidRenderScene() noexcept
    { m_framebuffer->Unlock(); }

    inline void SceneGraphRenderManagement::WillRenderDebugGUI() noexcept
    { m_context->WillRenderDebugGUI(); }

    inline void SceneGraphRenderManagement::DidRenderDebugGUI() noexcept
    { m_context->DidRenderDebugGUI(); }
}

#endif //HEADERTECH_SCENEGRAPHRENDERMANAGEMENT_INL
