//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_SYSTEM_H
#define HEADERTECH_SYSTEM_H

#include <functional>
#include <vector>

#include <ecs/EntityCollection.h>

namespace HeaderTech::Scene::ECS {
    using SystemTickingCallback = std::function<void(double, double, const EntityCollection &)>;
    using SystemRenderingCallback = std::function<void(double, const EntityCollection &)>;
}

#endif //HEADERTECH_SYSTEM_H
