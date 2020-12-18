//
// Created by rogan2 on 17/11/2020.
//

#ifndef HEADERTECH_RUNTIMECONFIG_H
#define HEADERTECH_RUNTIMECONFIG_H

namespace HeaderTech::Config {
    enum RenderConfigApi {
        RenderConfigApi_OpenGL,
        RenderConfigApi_Vulkan,
        RenderConfigApi_Metal,
        RenderConfigApi_Direct3D,
    };

    struct RenderConfig {
        RenderConfigApi api;
    };

    struct WindowConfig {
        int width;
        int height;
        const char *title;
        RenderConfig render;
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
                        .title = "Sandbox",
                        .render = {
                                .api = RenderConfigApi_OpenGL,
                        }
                }
        };
    }
}

#endif //HEADERTECH_RUNTIMECONFIG_H
