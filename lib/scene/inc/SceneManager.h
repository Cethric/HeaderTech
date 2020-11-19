//
// Created by rogan2 on 18/11/2020.
//

#ifndef HEADERTECH_SCENEMANAGER_H
#define HEADERTECH_SCENEMANAGER_H


#include <Logging.h>
#include <thread>
#include <vector>
#include <Scene.h>

namespace HeaderTech::Scene {

    class SceneManager {
    public:
        SceneManager() : m_log(HeaderTech::Logging::make_logger_async<SceneManager>()), m_scenes()
        {}

        inline void PushScene(const ScenePtr &scene) noexcept
        {
            m_scenes.push_back(scene);
        }

        inline void PopScene() noexcept
        {
            m_scenes.pop_back();
        }

        void ProcessNextTick(double delta, double lag)
        {
            m_log->info("Process Tick: {} ({})", delta, lag);
            std::this_thread::sleep_for(std::chrono::milliseconds(6));
            for (auto &scene : m_scenes) scene->Tick(delta);
        }

        void ProcessNextFrame(double offset)
        {
            m_log->info("Render with offset: {}", offset);
            std::this_thread::sleep_for(std::chrono::milliseconds(8));
            for (auto &scene : m_scenes) scene->Render(offset);
        }

    private:
        HeaderTech::Logging::Logger m_log;
        std::vector<ScenePtr> m_scenes;
    };
}

#endif //HEADERTECH_SCENEMANAGER_H
