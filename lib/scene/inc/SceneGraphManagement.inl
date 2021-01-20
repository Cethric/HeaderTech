//
// Created by rogan2 on 21/12/2020.
//

#ifndef HEADERTECH_SCENEGRAPHMANAGEMENT_INL
#define HEADERTECH_SCENEGRAPHMANAGEMENT_INL

#include <SceneGraph.h>

namespace HeaderTech::Scene {
    void SceneGraph::ResizeFramebuffer(int width, int height) noexcept
    {
        m_management.ResizeFramebuffer(width, height);
        OnFramebufferResized(width, height);
    }

    inline void SceneGraph::Activate() noexcept
    {
        m_management.Activate();
        OnActivated();
    }

    inline void SceneGraph::Deactivate() noexcept
    {
        m_management.Deactivate();
        OnDeactivated();
    }

    inline void SceneGraph::WillPushScene() noexcept
    {
        m_management.WillPushScene();
        OnSceneWillBePushed();
    }

    inline void SceneGraph::WillPopScene() noexcept
    {
        m_management.WillPopScene();
        OnSceneWillBePopped();
    }

    inline void SceneGraph::DidPushScene() noexcept
    {
        m_management.DidPushScene();
        OnSceneWasPushed();
    }

    inline void SceneGraph::DidPopScene() noexcept
    {
        m_management.DidPopScene();
        OnSceneWasPopped();
    }

    inline void SceneGraph::TickScene(double delta, double lag) noexcept
    {
        m_management.TickScene(delta, lag);
        OnSceneTicked(delta, lag);
    }

    inline void SceneGraph::RenderScene(double offset) noexcept
    {
        m_management.WillRenderScene();
        m_management.RenderScene(offset);
        OnSceneRendered(offset, m_management);
        m_management.DidRenderScene();
    }

    inline void SceneGraph::RenderDebugGUI() noexcept
    {
        m_management.WillRenderDebugGUI();
        OnDebugGuiRendered();
        m_management.DidRenderDebugGUI();
    }
}

#endif //HEADERTECH_SCENEGRAPHMANAGEMENT_INL
