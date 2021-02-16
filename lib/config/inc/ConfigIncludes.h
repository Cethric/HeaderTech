//
// Created by rogan2 on 17/11/2020.
//

#ifndef HEADERTECH_CONFIGINCLUDES_H
#define HEADERTECH_CONFIGINCLUDES_H


#include <HeaderTech_Config_Export.h>
#include <HeaderTech_Config_Version.h>
#include <RuntimeConfig.h>

#if defined(HEADERTECH_CONFIG_IMPL) && DEFINE_IMPLEMENTATION == 1


#endif

namespace HeaderTech::Config {
    HEADERTECH_CONFIG_EXPORT int ConfigVersion();
}

#endif //HEADERTECH_CONFIGINCLUDES_H
