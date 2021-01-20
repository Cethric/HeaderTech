//
// Created by rogan2 on 21/12/2020.
//

#ifndef HEADERTECH_SCENEGRAPHRENDERMANAGEMENT_H
#define HEADERTECH_SCENEGRAPHRENDERMANAGEMENT_H

#include <RenderContext.h>

namespace HeaderTech::Scene {
    class SceneGraph;
}

namespace HeaderTech::Core {
    class Runtime;
}

namespace HeaderTech::Render::SceneGraph {
    struct RenderSurfaceOptions {
        int width;
        int height;
    };

    class SceneGraphRenderManagement {
    private:
        friend class HeaderTech::Scene::SceneGraph;

        inline explicit SceneGraphRenderManagement(
                HeaderTech::Core::Runtime *runtime,
                const RenderSurfaceOptions &options
        ) noexcept;

        inline explicit SceneGraphRenderManagement(
                HeaderTech::Render::RenderContext *context,
                const RenderSurfaceOptions &options
        ) noexcept;

        inline ~SceneGraphRenderManagement() noexcept;

        inline void ResizeFramebuffer(int width, int height) noexcept;

        inline void Activate() noexcept;

        inline void Deactivate() noexcept;

        inline void WillPushScene() noexcept;

        inline void WillPopScene() noexcept;

        inline void DidPushScene() noexcept;

        inline void DidPopScene() noexcept;

        inline void TickScene(double delta, double lag) noexcept;

        inline void WillRenderScene() noexcept;

        inline void RenderScene(double offset) noexcept;

        inline void DidRenderScene() noexcept;

        inline void WillRenderDebugGUI() noexcept;

        inline void DidRenderDebugGUI() noexcept;

        inline HeaderTech::Render::Api::RenderFramebuffer *GetFramebuffer() noexcept
        { return m_framebuffer; }

    private:
        HeaderTech::Render::RenderContext *m_context;
        HeaderTech::Render::Api::RenderFramebuffer *m_framebuffer;
    };
}

#endif //HEADERTECH_SCENEGRAPHRENDERMANAGEMENT_H
