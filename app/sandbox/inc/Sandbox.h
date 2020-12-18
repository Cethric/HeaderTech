//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_SANDBOX_H
#define HEADERTECH_SANDBOX_H

#define DEFINE_IMPLEMENTATION 1
#define GLFW_INCLUDE_NONE 1

#include <iostream>

#include <Logging.h>
#include <Profiler.h>
#include <Events.h>
#include <Core.h>
#include <FileSystem.h>
#include <Config.h>
#include <Scene.h>
#include <UserInterface.h>
#include <Render.h>

using SceneGraph = HeaderTech::Scene::SceneGraph;
using SceneManager = HeaderTech::Scene::SceneManager;
using Runtime = HeaderTech::Core::Runtime;
using ScopedGlfw = HeaderTech::Core::Scoped::ScopedGlfw;
using ScopedProfiler = HeaderTech::Profiler::Scoped::ScopedProfiler;
using ScopedLogging = HeaderTech::Logging::Scoped::ScopedLogging;
using ScopedFileSystem = HeaderTech::FileSystem::Scoped::ScopedFileSystem;
using HeaderTech::Config::BuildConfiguration;
using RenderSurface = HeaderTech::Render::RenderSurface;
using EntityId = HeaderTech::Scene::ECS::EntityId;

#endif //HEADERTECH_SANDBOX_H
