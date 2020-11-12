//
// Created by rogan2 on 29/10/2020.
//

#ifndef HEADERTECH_LAUNCHEVENT_H
#define HEADERTECH_LAUNCHEVENT_H

#include <Event.h>

namespace HeaderTech::Core::Events {
    class LaunchEvent {
    public:
        explicit LaunchEvent(HeaderTech::Events::EventPriority priority) : m_priority(priority)
        {}

        ~LaunchEvent() = default;

        [[nodiscard]] HeaderTech::Events::EventPriority GetPriority() const
        { return m_priority; }

    protected:
        std::uint8_t m_priority;
    };
}

#endif //HEADERTECH_LAUNCHEVENT_H
