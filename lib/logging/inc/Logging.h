//
// Created by rogan2 on 5/11/2020.
//

#ifndef HEADERTECH_LOGGING_H
#define HEADERTECH_LOGGING_H

#include <Logger.h>

#if defined(HEADERTECH_LOGGING_IMPL) && DEFINE_IMPLEMENTATION == 1
#include <Logger.inl>
#include <ProfilerSink.inl>
#endif

#endif //HEADERTECH_LOGGING_H
