//
// Created by rogan2 on 18/11/2020.
//

#ifndef HEADERTECH_SCENEMANAGER_H
#define HEADERTECH_SCENEMANAGER_H

#include <Logging.h>
#include <thread>
#include <vector>
#include <SceneGraph.h>

namespace HeaderTech::Core {
    class Runtime;
}

namespace HeaderTech::Scene {
    class SceneManager {
    public:
        inline explicit SceneManager(HeaderTech::Core::Runtime *runtime) noexcept;

        inline ~SceneManager() noexcept;

        template<typename RootScene, typename...Args>
        inline void SetRootScene(Args...args) noexcept;

        inline void PushScene();

        inline void PushScene(SceneGraph *scene);

        inline void PopScene();

        inline void RenderScene(double offset);

        inline void TickScene(double delta, double lag);

        inline void RenderDebugUI();

    protected:
        inline void PushNextScene(SceneGraph *scene);

        inline void PopLastScene(SceneGraph *scene);

    private:
        SceneGraph *m_root;
        SceneGraph *m_active;
        HeaderTech::Logging::Logger m_log;
        HeaderTech::Core::Runtime *m_runtime;
    };
}

#endif //HEADERTECH_SCENEMANAGER_H
