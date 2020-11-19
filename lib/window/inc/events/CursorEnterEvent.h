//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_CURSORENTEREVENT_H
#define HEADERTECH_CURSORENTEREVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct CursorEnterEvent {
        explicit inline CursorEnterEvent(bool entered) noexcept: entered(entered)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept // NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_PRIORITY; }

        bool entered;
    };
}

#endif //HEADERTECH_CURSORENTEREVENT_H
