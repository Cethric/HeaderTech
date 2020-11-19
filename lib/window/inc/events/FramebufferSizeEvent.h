//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_FRAMEBUFFERSIZEEVENT_H
#define HEADERTECH_FRAMEBUFFERSIZEEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct FramebufferSizeEvent {
        inline FramebufferSizeEvent(int width, int height) noexcept: width(width), height(height)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept // NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_PRIORITY; }

        int width;
        int height;
    };
}

#endif //HEADERTECH_FRAMEBUFFERSIZEEVENT_H
