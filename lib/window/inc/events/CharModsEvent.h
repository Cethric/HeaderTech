//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_CHARMODSEVENT_H
#define HEADERTECH_CHARMODSEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct CharModsEvent {
        inline CharModsEvent(unsigned int code, int mods) noexcept: code(code), mods(mods)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_EVENT_PRIORITY; }

        unsigned int code;
        int mods;
    };
}

#endif //HEADERTECH_CHARMODSEVENT_H
