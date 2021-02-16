//
// Created by rogan2 on 22/01/2021.
//

#ifndef HEADERTECH_GLFWKEYMAPPING_H
#define HEADERTECH_GLFWKEYMAPPING_H

#define GLFW_INCLUDE_NONE 1

#include <GLFW/glfw3.h>
#include <WindowTypes.h>

namespace HeaderTech::Window::Api::GLFW {
    inline static std::int32_t KeyMapping[] = {
            GLFW_KEY_A,
            GLFW_KEY_B,
            GLFW_KEY_C,
            GLFW_KEY_D,
            GLFW_KEY_E,
            GLFW_KEY_F,
            GLFW_KEY_G,
            GLFW_KEY_H,
            GLFW_KEY_I,
            GLFW_KEY_J,
            GLFW_KEY_K,
            GLFW_KEY_L,
            GLFW_KEY_M,
            GLFW_KEY_N,
            GLFW_KEY_O,
            GLFW_KEY_P,
            GLFW_KEY_Q,
            GLFW_KEY_R,
            GLFW_KEY_S,
            GLFW_KEY_T,
            GLFW_KEY_U,
            GLFW_KEY_V,
            GLFW_KEY_W,
            GLFW_KEY_X,
            GLFW_KEY_Y,
            GLFW_KEY_Z,

            GLFW_KEY_UP,
            GLFW_KEY_DOWN,
            GLFW_KEY_LEFT,
            GLFW_KEY_RIGHT,

            GLFW_KEY_SPACE,
            GLFW_KEY_LEFT_SHIFT,
            GLFW_KEY_RIGHT_SHIFT,
    };
}

#endif //HEADERTECH_GLFWKEYMAPPING_H
