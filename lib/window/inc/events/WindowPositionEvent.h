//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_WINDOWPOSITIONEVENT_H
#define HEADERTECH_WINDOWPOSITIONEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct WindowPositionEvent {
        explicit inline WindowPositionEvent(int x, int y) noexcept: posX(x), posY(y)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_PRIORITY; }

        int posX;
        int posY;
    };
}

#endif //HEADERTECH_WINDOWPOSITIONEVENT_H
