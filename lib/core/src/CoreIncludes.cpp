//
// Created by rogan2 on 15/10/2020.
//

#define HEADERTECH_CORE_IMPL 1
#define HEADERTECH_LOGGING_IMPL 1
#define HEADERTECH_PROFILER_IMPL 1
#define HEADERTECH_EVENTS_IMPL 1
#define DEFINE_IMPLEMENTATION 1

#include "CoreIncludes.h"

namespace HeaderTech::Core {
    HEADERTECH_CORE_EXPORT int CoreVersion()
    { return HeaderTech_Core_Version; }
}
