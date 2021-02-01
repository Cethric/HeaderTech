//
// Created by rogan2 on 30/10/2020.
//

#ifndef HEADERTECH_EVENT_INL
#define HEADERTECH_EVENT_INL

#include <Event.h>

namespace HeaderTech::Events {
    namespace detail {
        template<EventType EventClass>
        __declspec(noalias)  static inline void event_destructor(void *event) noexcept
        {
            auto base = static_cast<EventClass *>(event);
            delete base;
        }
    }

    inline Event::Event() noexcept: m_event(nullptr),
                                    m_destructor(nullptr),
                                    m_id(0),
                                    m_priority(0)
    {
    }

    inline Event::~Event() noexcept
    {
        if (m_destructor) {
            m_destructor(m_event);
        }
    }

    [[nodiscard]] constexpr inline EventId Event::GetId() const noexcept
    {
        return m_id;
    }

    [[nodiscard]] constexpr inline EventPriority Event::GetPriority() const noexcept
    {
        return m_priority;
    }

    template<EventType EventClass>
    [[nodiscard]] __declspec(restrict) constexpr inline EventClass *Event::Cast() const noexcept
    {
        [[likely]] if (m_id == EventIdChecker<EventClass>{}()) {
            return static_cast<EventClass *>(m_event);
        }
        return nullptr;
    }

    template<EventType EventClass, typename... Args>
    [[nodiscard]] inline std::shared_ptr<Event> Event::MakeEvent(Args... args) noexcept
    {
        auto event = std::make_shared<Event>();
        event->Prepare<EventClass, Args...>(std::forward<Args>(args)...);
        return event;
    }

    template<EventType EventClass, typename... EventArgs>
    constexpr inline void Event::Prepare(EventArgs... args) noexcept
    {
        auto base = new EventClass(std::forward<EventArgs>(args)...);
        m_event = base;
        m_destructor = detail::event_destructor<EventClass>;
        m_id = EventIdChecker < EventClass > {}(*base);
        m_priority = EventPriorityChecker < EventClass > {}(*base);
    }
}

#endif //HEADERTECH_EVENT_INL
