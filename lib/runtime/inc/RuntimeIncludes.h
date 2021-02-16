//
// Created by rogan2 on 9/02/2021.
//

#ifndef HEADERTECH_RUNTIMEINCLUDES_H
#define HEADERTECH_RUNTIMEINCLUDES_H

#include <Runtime.h>

#include <events/LaunchEvent.h>


#if defined(HEADERTECH_RUNTIME_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <Runtime.inl>

#endif

namespace HeaderTech::Runtime {
    int RuntimeVersion();
}

#endif //HEADERTECH_RUNTIMEINCLUDES_H
