//
// Created by rogan2 on 17/11/2020.
//

#define HEADERTECH_CONFIG_IMPL 1
#define DEFINE_IMPLEMENTATION 1

#include <ConfigIncludes.h>

namespace HeaderTech::Config {
    HEADERTECH_CONFIG_EXPORT int ConfigVersion()
    { return HeaderTech_Config_Version; }
}
