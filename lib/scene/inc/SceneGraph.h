//
// Created by rogan2 on 18/11/2020.
//

#ifndef HEADERTECH_SCENEGRAPH_H
#define HEADERTECH_SCENEGRAPH_H


#include <memory>
#include <concepts>
#include <type_traits>
#include <ctti/type_id.hpp>
#include <ctti/detailed_nameof.hpp>

#include <EntityCollection.h>
#include <events/FramebufferSizeEvent.h>
#include <scene/SceneGraphRenderManagement.h>

#include <WindowTypes.h>

namespace HeaderTech::Core {
    class Runtime;
}

namespace HeaderTech::Scene {

    class SceneGraph {
    private:
        friend class SceneManager;

    public:
        inline SceneGraph(
                HeaderTech::Core::Runtime *runtime,
                SceneManager *owner,
                SceneGraph *parent,
                HeaderTech::Logging::Logger logger,
                const HeaderTech::Render::SceneGraph::RenderSurfaceOptions &options
        ) noexcept;

        inline virtual ~SceneGraph() noexcept;

        inline void ResizeFramebuffer(int width, int height) noexcept;

        inline void OnEvent(HeaderTech::Window::Events::FramebufferSizeEvent *event) noexcept;

    protected:

        template<typename ChildScene, typename...Args>
        inline ChildScene *AddChildScene(Args...args) noexcept;

    private:
        inline void Activate() noexcept;

        inline void Deactivate() noexcept;

        inline void WillPushScene() noexcept;

        inline void WillPopScene() noexcept;

        inline void DidPushScene() noexcept;

        inline void DidPopScene() noexcept;

        inline void TickScene(double delta, double lag) noexcept;

        inline void RenderScene(double offset) noexcept;

        inline void RenderDebugGUI() noexcept;

    protected:
        inline bool IsKeyPressed(HeaderTech::Window::KeyType key) noexcept;

        virtual inline void OnActivated() noexcept = 0;

        virtual inline void OnDeactivated() noexcept = 0;

        virtual inline void OnSceneWillBePushed() noexcept = 0;

        virtual inline void OnSceneWillBePopped() noexcept = 0;

        virtual inline void OnSceneWasPushed() noexcept = 0;

        virtual inline void OnSceneWasPopped() noexcept = 0;

        virtual inline void OnSceneTicked(double delta, double lag) noexcept = 0;

        virtual inline void OnSceneRendered(double offset, const HeaderTech::Render::SceneGraph::SceneGraphRenderManagement& mgmt) noexcept = 0;

        virtual inline void OnDebugGuiRendered() noexcept = 0;

        virtual inline void OnFramebufferResized(int width, int height) noexcept = 0;

    private:
        std::int32_t m_refCount;

        inline void PushSceneCount() noexcept;

        inline void PopSceneCount() noexcept;

    protected:
        [[nodiscard]] inline HeaderTech::Core::Runtime *Runtime() const noexcept
        { return m_runtime; }

        [[nodiscard]] inline SceneManager *Owner() const noexcept
        { return m_owner; }

        [[nodiscard]] inline SceneGraph *Parent() const noexcept
        { return m_parent; }

        [[nodiscard]] inline EntityComponentSystem::EntityCollection &Entities() noexcept
        { return m_entities; }

    private:
        HeaderTech::Core::Runtime *m_runtime;
        SceneManager *m_owner;
        SceneGraph *m_parent;
        std::vector<SceneGraph *> m_children;

    private: // Render Management
        HeaderTech::Render::SceneGraph::SceneGraphRenderManagement m_management;

    private: // EntityComponentSystem
        EntityComponentSystem::EntityCollection m_entities;

    protected:
        HeaderTech::Logging::Logger m_log;
    };
}

#endif //HEADERTECH_SCENEGRAPH_H
