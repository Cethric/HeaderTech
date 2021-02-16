//
// Created by rogan2 on 5/11/2020.
//

#ifndef HEADERTECH_LOGGINGINCLUDES_H
#define HEADERTECH_LOGGINGINCLUDES_H

#include <Logger.h>
#include <ProfilerSink.h>
#include <FileSink.h>
#include <scoped/ScopedLogging.h>

#if defined(HEADERTECH_LOGGING_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <Logger.inl>
#include <ProfilerSink.inl>
#include <FileSink.inl>
#include <scoped/ScopedLogging.inl>

#endif

namespace HeaderTech::Logging {
    int LoggingVersion();
}

#endif //HEADERTECH_LOGGINGINCLUDES_H
