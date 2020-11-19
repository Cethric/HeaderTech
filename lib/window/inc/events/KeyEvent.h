//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_KEYEVENT_H
#define HEADERTECH_KEYEVENT_H

#include <Event.h>
#include <GLFW/glfw3.h>

namespace HeaderTech::Window::Events {
    enum KeyAction : std::uint8_t {
        KeyAction_RELEASED = GLFW_RELEASE,
        KeyAction_PRESSED = GLFW_PRESS,
        KeyAction_REPEATED = GLFW_REPEAT
    };

    struct KeyEvent {
        inline KeyEvent(int key, int scanCode, KeyAction action, int mods) noexcept
                : key(key),
                  scanCode(scanCode),
                  action(action),
                  mods(mods)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_PRIORITY; }

        int key;
        int scanCode;
        KeyAction action;
        int mods;
    };
}

#endif //HEADERTECH_KEYEVENT_H
