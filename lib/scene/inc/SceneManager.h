//
// Created by rogan2 on 18/11/2020.
//

#ifndef HEADERTECH_SCENEMANAGER_H
#define HEADERTECH_SCENEMANAGER_H

#include <LoggingIncludes.h>
#include <thread>
#include <vector>
#include <SceneGraph.h>

namespace HeaderTech::Runtime {
    class Runtime;
}

namespace HeaderTech::Scene {
    class SceneManager {
    public:
        inline explicit SceneManager(HeaderTech::Runtime::Runtime *runtime) noexcept;

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
        HeaderTech::Runtime::Runtime *m_runtime;
    };
}

#endif //HEADERTECH_SCENEMANAGER_H
