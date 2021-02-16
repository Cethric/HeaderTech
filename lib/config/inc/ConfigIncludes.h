//
// Created by rogan2 on 17/11/2020.
//

#ifndef HEADERTECH_CONFIGINCLUDES_H
#define HEADERTECH_CONFIGINCLUDES_H

#include <RuntimeConfig.h>

#if defined(HEADERTECH_CONFIG_IMPL) && DEFINE_IMPLEMENTATION == 1


#endif

namespace HeaderTech::Config {
    int ConfigVersion();
}

#endif //HEADERTECH_CONFIGINCLUDES_H
