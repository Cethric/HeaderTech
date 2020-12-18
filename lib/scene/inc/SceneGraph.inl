//
// Created by rogan2 on 1/12/2020.
//

#ifndef HEADERTECH_SCENEGRAPH_INL
#define HEADERTECH_SCENEGRAPH_INL

#include <SceneGraph.h>


namespace HeaderTech::Scene {
    SceneGraph::SceneGraph(HeaderTech::Core::Runtime *runtime, SceneManager *owner, SceneGraph *parent) noexcept
            : m_refCount(0),
              m_runtime(runtime),
              m_owner(owner),
              m_parent(parent),
              m_children(),
              m_entities(),
              m_log(HeaderTech::Logging::get_or_make_logger_async<SceneGraph>())
    {}

    SceneGraph::~SceneGraph() noexcept
    {
        while (!m_children.empty()) {
            auto child = m_children.back();
            m_children.pop_back();
            if (child->m_refCount > 0) {
                child->PopSceneCount();
            }
            delete child;
        }
        if (m_refCount > 0) {
            SPDLOG_LOGGER_WARN(m_log, "Scene Ref Count was to high, should be 0 but got {}", m_refCount);
        }
    }

    template<typename ChildScene, typename... Args>
    ChildScene *SceneGraph::AddChildScene(Args... args) noexcept
    {
        auto scene = new ChildScene(m_runtime, m_owner, this, std::forward<Args>(args)...);
        m_children.push_back(scene);
        return scene;
    }

    ECS::EntityBuilder SceneGraph::AddEntity() noexcept
    { return m_entities.NextEntity(); }

    ECS::Entity SceneGraph::GetEntity(ECS::EntityId entityId) noexcept
    { return m_entities.GetEntity(entityId); }

    void SceneGraph::RegisterTickingSystem(const ECS::SystemTickingCallback &system) noexcept
    {}

    void SceneGraph::RegisterRenderingSystem(const ECS::SystemRenderingCallback &system) noexcept
    {}

    void SceneGraph::PushSceneCount() noexcept
    {
        if ((m_refCount++) == 0) {
            Activate();
        }
    }

    void SceneGraph::PopSceneCount() noexcept
    {
        --m_refCount;
        if (m_refCount == 0) {
            Deactivate();
        }
        if (m_refCount < 0) {
            SPDLOG_LOGGER_WARN(m_log, "Scene Ref count decremented more that it was incremented: {}", m_refCount);
        }
    }
}

#endif //HEADERTECH_SCENEGRAPH_INL
