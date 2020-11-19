//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_SCROLLEVENT_H
#define HEADERTECH_SCROLLEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct ScrollEvent {
        inline ScrollEvent(double x, double y) noexcept: scrollX(x), scrollY(y)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_PRIORITY; }

        double scrollX;
        double scrollY;
    };
}

#endif //HEADERTECH_SCROLLEVENT_H
