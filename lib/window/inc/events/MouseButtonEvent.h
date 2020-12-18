//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_MOUSEBUTTONEVENT_H
#define HEADERTECH_MOUSEBUTTONEVENT_H

#include <Event.h>
#include <GLFW/glfw3.h>

namespace HeaderTech::Window::Events {
    enum MouseButtonAction : std::uint8_t {
        MouseButtonAction_RELEASED = GLFW_RELEASE,
        MouseButtonAction_PRESSED = GLFW_PRESS
    };

    struct MouseButtonEvent {
        inline MouseButtonEvent(int button, MouseButtonAction action, int mods) noexcept
                : button(button),
                  action(action),
                  mods(mods)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_EVENT_PRIORITY; }

        int button;
        MouseButtonAction action;
        int mods;
    };
}

#endif //HEADERTECH_MOUSEBUTTONEVENT_H
