//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_WINDOWICONIFYEVENT_H
#define HEADERTECH_WINDOWICONIFYEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct WindowIconifyEvent {
        explicit inline WindowIconifyEvent(bool iconified) noexcept: iconified(iconified)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_EVENT_PRIORITY; }

        bool iconified;
    };
}

#endif //HEADERTECH_WINDOWICONIFYEVENT_H
