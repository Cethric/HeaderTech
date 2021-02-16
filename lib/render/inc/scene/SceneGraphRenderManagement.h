//
// Created by rogan2 on 21/12/2020.
//

#ifndef HEADERTECH_SCENEGRAPHRENDERMANAGEMENT_H
#define HEADERTECH_SCENEGRAPHRENDERMANAGEMENT_H

#include <RenderContext.h>
#include <api/render/RenderApiIncludes.h>

namespace HeaderTech::Scene {
    class SceneGraph;
}

namespace HeaderTech::Runtime {
    class Runtime;
}

namespace HeaderTech::Render::SceneGraph {
    struct RenderSurfaceOptions {
        glm::ivec2 window_size;
    };

    class SceneGraphRenderManagement {
    private:
        friend class HeaderTech::Scene::SceneGraph;

        inline explicit SceneGraphRenderManagement(
                HeaderTech::Runtime::Runtime *runtime,
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

        inline HeaderTech::Core::Api::Render::RenderFramebuffer *GetFramebuffer() noexcept
        { return m_framebuffer; }

    private:
        HeaderTech::Render::RenderContext *m_context;
        HeaderTech::Core::Api::Render::RenderFramebuffer *m_framebuffer;
    };
}

#endif //HEADERTECH_SCENEGRAPHRENDERMANAGEMENT_H
