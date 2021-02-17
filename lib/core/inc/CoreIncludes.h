//
// Created by rogan2 on 5/11/2020.
//

#ifndef HEADERTECH_COREINCLUDES_H
#define HEADERTECH_COREINCLUDES_H

#include <scoped/ScopedGLFW.h>
#include <WindowTypes.h>

#include <ReactiveProperty.h>

#include <api/window/WindowApiIncludes.h>
#include <api/render/RenderApiIncludes.h>

#include <HeaderTech_Core_Export.h>
#include <HeaderTech_Core_Version.h>


#if defined(HEADERTECH_CORE_IMPL) && DEFINE_IMPLEMENTATION == 1

#endif

namespace HeaderTech::Core {
    HEADERTECH_CORE_EXPORT int CoreVersion();
}

#endif //HEADERTECH_COREINCLUDES_H
