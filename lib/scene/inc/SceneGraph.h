//
// Created by rogan2 on 18/11/2020.
//

#ifndef HEADERTECH_SCENEGRAPH_H
#define HEADERTECH_SCENEGRAPH_H


#include <memory>
#include <ctti/detailed_nameof.hpp>

#include <ecs/System.h>
#include <ecs/EntityCollection.h>

namespace HeaderTech::Core {
    class Runtime;
}

namespace HeaderTech::Scene {
    class SceneGraph {
    private:
        friend class SceneManager;

    public:
        SceneGraph(HeaderTech::Core::Runtime *runtime, SceneManager *owner, SceneGraph *parent) noexcept;

        virtual ~SceneGraph() noexcept;

        template<typename ChildScene, typename...Args>
        ChildScene *AddChildScene(Args...args) noexcept;

        ECS::EntityBuilder AddEntity() noexcept;

        ECS::Entity GetEntity(ECS::EntityId entityId) noexcept;

        void RegisterTickingSystem(const ECS::SystemTickingCallback &) noexcept;

        void RegisterRenderingSystem(const ECS::SystemRenderingCallback &) noexcept;

    protected:
        virtual void Activate()
        {}

        virtual void Deactivate()
        {}

        virtual void WillPushScene()
        {}

        virtual void WillPopScene()
        {}

        virtual void DidPushScene()
        {}

        virtual void DidPopScene()
        {}

        virtual void TickScene(double delta, double lag)
        {}

        virtual void RenderScene(double offset)
        {}

    private:
        std::int32_t m_refCount;

        void PushSceneCount() noexcept;

        void PopSceneCount() noexcept;

    protected:
        [[nodiscard]] HeaderTech::Core::Runtime *Runtime() const
        { return m_runtime; }

        [[nodiscard]] SceneManager *Owner() const
        { return m_owner; }

        [[nodiscard]] SceneGraph *Parent() const
        { return m_parent; }

        [[nodiscard]] const ECS::EntityCollection &Collection() const
        { return m_entities; }

    private:
        HeaderTech::Core::Runtime *m_runtime;
        SceneManager *m_owner;
        SceneGraph *m_parent;
        std::vector<SceneGraph *> m_children;
        HeaderTech::Logging::Logger m_log;

    private: // ECS
        ECS::EntityCollection m_entities;
    };
}

#endif //HEADERTECH_SCENEGRAPH_H
