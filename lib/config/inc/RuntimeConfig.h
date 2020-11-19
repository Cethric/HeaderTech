//
// Created by rogan2 on 17/11/2020.
//

#ifndef HEADERTECH_RUNTIMECONFIG_H
#define HEADERTECH_RUNTIMECONFIG_H

namespace HeaderTech::Config {
    struct WindowConfig {
        int width;
        int height;
        const char *title;
    };

    struct RuntimeConfig {
        WindowConfig window;
    };

    inline RuntimeConfig BuildConfiguration(int argc, const char **argv)
    {
        return {
                .window = {
                        .width = 800,
                        .height = 600,
                        .title = "Sandbox"
                }
        };
    }
}

#endif //HEADERTECH_RUNTIMECONFIG_H
