//
// Created by rogan2 on 5/11/2020.
//

#ifndef HEADERTECH_PROFILERINCLUDES_H
#define HEADERTECH_PROFILERINCLUDES_H

#include <LogDispatcher.h>
#include <ProfileDispatcher.h>
#include <ProfilerTypes.h>
#include <Types.h>
#include <ProfilerManager.h>

#if defined(HEADERTECH_PROFILER_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <LogDispatcher.inl>
#include <ProfileDispatcher.inl>
#include <ProfilerManager.inl>

#endif
#endif //HEADERTECH_PROFILERINCLUDES_H
