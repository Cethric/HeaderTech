//
// Created by rogan2 on 13/11/2020.
//

#ifndef HEADERTECH_CURSORPOSITIONEVENT_H
#define HEADERTECH_CURSORPOSITIONEVENT_H

#include <Event.h>

namespace HeaderTech::Window::Events {
    struct CursorPositionEvent {
        inline CursorPositionEvent(double x, double y, double dX, double dY) noexcept
                : posX(x),
                  posY(y),
                  deltaPosX(dX),
                  deltaPosY(dY)
        {}

        [[nodiscard]] inline HeaderTech::Events::EventPriority
        GetPriority() const noexcept// NOLINT(readability-convert-member-functions-to-static)
        { return HeaderTech::Events::MAX_EVENT_PRIORITY; }

        double posX;
        double posY;
        double deltaPosX;
        double deltaPosY;
    };
}

#endif //HEADERTECH_CURSORPOSITIONEVENT_H
