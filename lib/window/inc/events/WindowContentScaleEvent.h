//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_WINDOWCONTENTSCALEEVENT_H
#define HEADERTECH_WINDOWCONTENTSCALEEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct WindowContentScaleEvent {
        inline WindowContentScaleEvent(float x, float y) noexcept: scaleX(x), scaleY(y)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_EVENT_PRIORITY; }

        float scaleX;
        float scaleY;
    };
}

#endif //HEADERTECH_WINDOWCONTENTSCALEEVENT_H
