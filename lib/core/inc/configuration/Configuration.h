//
// Created by rogan2 on 12/11/2020.
//

#ifndef HEADERTECH_CONFIGURATION_H
#define HEADERTECH_CONFIGURATION_H

namespace HeaderTech::Core::Configuration {

    struct WindowConfig {
        int width;
        int height;
        const char* title;
    };

    struct RuntimeConfig {
        WindowConfig window;
    };
}

#endif //HEADERTECH_CONFIGURATION_H
