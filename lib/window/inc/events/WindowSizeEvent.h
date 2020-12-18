//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_WINDOWSIZEEVENT_H
#define HEADERTECH_WINDOWSIZEEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct WindowSizeEvent {
        inline WindowSizeEvent(int width, int height) noexcept: width(width), height(height)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept // NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_EVENT_PRIORITY; }

        int width;
        int height;
    };
}

#endif //HEADERTECH_WINDOWSIZEEVENT_H
