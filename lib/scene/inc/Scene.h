//
// Created by rogan2 on 18/11/2020.
//

#ifndef HEADERTECH_SCENE_H
#define HEADERTECH_SCENE_H

#include <memory>

namespace HeaderTech::Scene {
    class Scene {
    public:
        virtual void Tick(double delta)
        {}

        virtual void Render(double offset)
        {}
    };

    using ScenePtr = std::shared_ptr<Scene>;
}

#endif //HEADERTECH_SCENE_H
