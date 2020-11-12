//
// Created by rogan2 on 5/11/2020.
//

#ifndef HEADERTECH_PROFILER_H
#define HEADERTECH_PROFILER_H

#include <ProfileDisplayThread.h>
#include <ProfilerManager.h>
#include <ScopedProfileMark.h>

#if defined(HEADERTECH_PROFILER_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <ProfilerManager.inl>
#include <LogDispatcher.inl>
#include <ProfileDispatcher.inl>

#endif
#endif //HEADERTECH_PROFILER_H
