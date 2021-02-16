//
// Created by rogan2 on 18/11/2020.
//

#ifndef HEADERTECH_SCENEINCLUDES_H
#define HEADERTECH_SCENEINCLUDES_H

#include <SceneManager.h>
#include <SceneGraph.h>

#if defined(HEADERTECH_SCENE_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <SceneGraph.inl>
#include <SceneGraphManagement.inl>
#include <SceneManager.inl>

#endif

namespace HeaderTech::Scene {
    int SceneVersion();
}

#endif //HEADERTECH_SCENEINCLUDES_H
