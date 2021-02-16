//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_SANDBOX_H
#define HEADERTECH_SANDBOX_H

#define DEFINE_IMPLEMENTATION 1
#define GLFW_INCLUDE_NONE 1

#ifdef _CPPRTTI
#error runtime type information has been enabled
#endif

#include <iostream>

#include <imgui.h>

#include <LoggingIncludes.h>
#include <ProfilerIncludes.h>
#include <EventsIncludes.h>
#include <CoreIncludes.h>
#include <FileSystemIncludes.h>
#include <ConfigIncludes.h>
#include <SceneIncludes.h>
#include <UIIncludes.h>
#include <RenderIncludes.h>
#include <ECSIncludes.h>

using SceneGraph = HeaderTech::Scene::SceneGraph;
using SceneManager = HeaderTech::Scene::SceneManager;
using Runtime = HeaderTech::Runtime::Runtime;
using ScopedGlfw = HeaderTech::Core::Scoped::ScopedGlfw;
using ScopedProfiler = HeaderTech::Profiler::Scoped::ScopedProfiler;
using ScopedLogging = HeaderTech::Logging::Scoped::ScopedLogging;
using ScopedFileSystem = HeaderTech::FileSystem::Scoped::ScopedFileSystem;
using HeaderTech::Config::BuildConfiguration;
using RenderSurface = HeaderTech::Render::RenderSurface;
using EntityId = HeaderTech::EntityComponentSystem::EntityId;

#endif //HEADERTECH_SANDBOX_H
