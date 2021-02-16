//
// Created by rogan2 on 1/12/2020.
//

#ifndef HEADERTECH_SCENEMANAGER_INL
#define HEADERTECH_SCENEMANAGER_INL

#include <SceneManager.h>

namespace HeaderTech::Scene {
    inline SceneManager::SceneManager(HeaderTech::Runtime::Runtime *runtime) noexcept
            : m_root(nullptr),
              m_active(nullptr),
              m_log(HeaderTech::Logging::make_logger_async<SceneManager>()),
              m_runtime(runtime)
    {
        SPDLOG_LOGGER_DEBUG(m_log, "Create Scene Manager");
    }

    inline SceneManager::~SceneManager() noexcept
    {
        SPDLOG_LOGGER_DEBUG(m_log, "Destroy Scene Manager");
        m_active = nullptr;
        m_root->PopSceneCount();
        delete m_root;
        m_root = nullptr;
        SPDLOG_LOGGER_DEBUG(m_log, "Scene Manager Destroyed");
    }

    template<typename RootScene, typename... Args>
    void SceneManager::SetRootScene(Args... args) noexcept
    {
        auto scene = new RootScene(m_runtime, this, nullptr, std::forward<Args>(args)...);
        m_root = scene;
        m_active = scene;
        m_active->PushSceneCount();
    }

    inline void SceneManager::PushScene()
    {
        if (m_active->m_children.empty()) {
            SceneGraph *active = m_active;
            while (active) {
                if (active->m_parent == nullptr) {
                    break;
                }
                auto &children = active->m_parent->m_children;
                auto child = std::find(std::cbegin(children), std::cend(children), active);
                if (child == std::cend(children)) {
                    SPDLOG_LOGGER_CRITICAL(m_log, "Unable to find the active scene in the parent's scenes");
                    break;
                }
                auto distance = std::distance(std::cbegin(children), child) + 1;
                if (distance >= children.size()) {
                    active = active->m_parent;
                    continue;
                }
                PushNextScene(children.at(distance));
                return;
            }
            SPDLOG_LOGGER_WARN(m_log, "No more scenes to push");
            return;
        }
        PushNextScene(m_active->m_children.front());
    }

    inline void SceneManager::PushScene(SceneGraph *scene)
    { PushNextScene(scene); }

    inline void SceneManager::PopScene()
    {
        if (m_active == m_root) {
            if (m_active->m_refCount > 0) {
                m_active->PopSceneCount();
            }
            SPDLOG_LOGGER_WARN(m_log, "No more scenes to pop");
            return;
        }
        PopLastScene(m_active);
    }

    inline void SceneManager::RenderScene(double offset)
    { m_active->RenderScene(offset); }

    inline void SceneManager::TickScene(double delta, double lag)
    { m_active->TickScene(delta, lag); }

    void SceneManager::RenderDebugUI()
    { m_active->RenderDebugGUI(); }

    inline void SceneManager::PushNextScene(SceneGraph *scene)
    {
        scene->WillPushScene();
        SPDLOG_LOGGER_INFO(m_log, "Push Scene");
        scene->PushSceneCount();
        m_active = scene;
        scene->DidPushScene();
    }

    inline void SceneManager::PopLastScene(SceneGraph *scene)
    {
        scene->WillPopScene();
        SPDLOG_LOGGER_INFO(m_log, "Pop Scene");
        scene->PopSceneCount();
        m_active = scene->m_parent;
        scene->DidPopScene();
    }
}

#endif //HEADERTECH_SCENEMANAGER_INL
