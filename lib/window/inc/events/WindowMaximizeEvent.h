//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_WINDOWMAXIMIZEEVENT_H
#define HEADERTECH_WINDOWMAXIMIZEEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct WindowMaximizeEvent {
        explicit inline WindowMaximizeEvent(bool maximized) noexcept: maximized(maximized)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_PRIORITY; }

        bool maximized;
    };
}

#endif //HEADERTECH_WINDOWMAXIMIZEEVENT_H
