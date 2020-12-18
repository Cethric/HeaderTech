//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_WINDOWREFRESHEVENT_H
#define HEADERTECH_WINDOWREFRESHEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct WindowRefreshEvent {
        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_EVENT_PRIORITY; }
    };
}

#endif //HEADERTECH_WINDOWREFRESHEVENT_H
