//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_WINDOWCLOSEEVENT_H
#define HEADERTECH_WINDOWCLOSEEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct WindowCloseEvent {
        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_PRIORITY; }
    };
}

#endif //HEADERTECH_WINDOWCLOSEEVENT_H
