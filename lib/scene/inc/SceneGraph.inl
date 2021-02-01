//
// Created by rogan2 on 1/12/2020.
//

#ifndef HEADERTECH_SCENEGRAPH_INL
#define HEADERTECH_SCENEGRAPH_INL

#include <SceneGraph.h>

#include <Runtime.h>
#include <Runtime.inl>

namespace HeaderTech::Scene {
    inline SceneGraph::SceneGraph(
            HeaderTech::Core::Runtime *runtime,
            SceneManager *owner,
            SceneGraph *parent,
            HeaderTech::Logging::Logger logger,
            const HeaderTech::Render::SceneGraph::RenderSurfaceOptions &options
    ) noexcept
            : m_refCount(0),
              m_runtime(runtime),
              m_owner(owner),
              m_parent(parent),
              m_children(),
              m_management(runtime, options),
              m_entities(),
              m_log(std::move(logger))
    { m_runtime->Subscribe<HeaderTech::Window::Events::FramebufferSizeEvent>(this); }

    inline SceneGraph::~SceneGraph() noexcept
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

    inline void SceneGraph::OnEvent(HeaderTech::Window::Events::FramebufferSizeEvent *event) noexcept
    { ResizeFramebuffer(event->width, event->height); }

    template<typename ChildScene, typename... Args>
    inline ChildScene *SceneGraph::AddChildScene(Args... args) noexcept
    {
        auto scene = new ChildScene(m_runtime, m_owner, this, std::forward<Args>(args)...);
        m_children.push_back(scene);
        return scene;
    }

    inline void SceneGraph::PushSceneCount() noexcept
    {
        if ((m_refCount++) == 0) {
            Activate();
        }
    }

    inline void SceneGraph::PopSceneCount() noexcept
    {
        --m_refCount;
        if (m_refCount == 0) {
            Deactivate();
        }
        if (m_refCount < 0) {
            SPDLOG_LOGGER_WARN(m_log, "Scene Ref count decremented more that it was incremented: {}", m_refCount);
        }
    }

    inline bool SceneGraph::IsKeyPressed(HeaderTech::Window::KeyType key) noexcept
    {
        return Runtime()->GetWindow().IsKeyPressed(key);
    }
}

#endif //HEADERTECH_SCENEGRAPH_INL
