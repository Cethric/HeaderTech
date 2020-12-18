//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_WINDOWFOCUSEVENT_H
#define HEADERTECH_WINDOWFOCUSEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct WindowFocusEvent {
        explicit inline WindowFocusEvent(bool focused) noexcept: focused(focused)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_EVENT_PRIORITY; }

        bool focused;
    };
}

#endif //HEADERTECH_WINDOWFOCUSEVENT_H
