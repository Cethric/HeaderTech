//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_CHAREVENT_H
#define HEADERTECH_CHAREVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct CharEvent {
        explicit inline CharEvent(unsigned int code) noexcept: code(code)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_PRIORITY; }

        unsigned int code;
    };
}

#endif //HEADERTECH_CHAREVENT_H
