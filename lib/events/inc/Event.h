//
// Created by rogan2 on 29/10/2020.
//

#ifndef HEADERTECH_EVENT_H
#define HEADERTECH_EVENT_H

#include <queue>
#include <vector>
#include <memory>
#include <concepts>

#include <ctti/type_id.hpp>

namespace HeaderTech::Events {
    using EventId = std::uint64_t;
    using EventPriority = std::uint8_t;
    const EventPriority MAX_EVENT_PRIORITY = 0xff;

    class Event;

    using EventPtr = std::shared_ptr<Event>;

    template<class EventClass>
    struct EventIdChecker {
        [[nodiscard]] inline constexpr EventId operator()(const EventClass &event)
        { return this->operator()(); }

        [[nodiscard]] inline constexpr EventId operator()()
        { return ctti::unnamed_type_id<EventClass>().hash(); }
    };

    template<class EventClass>
    struct EventPriorityChecker {
        [[nodiscard]] inline EventPriority operator()(const EventClass &event)
        { return event.GetPriority(); }

        [[nodiscard]] inline EventPriority operator()(EventClass *event)
        { return this->operator()(*event); }

        [[nodiscard]] inline EventPriority operator()(const EventPtr &event)
        { return this->operator()(event.get()); }
    };

    template<class EventClass>
    concept EventType = requires(EventClass event) {
        { EventIdChecker<EventClass>{}(event) } -> std::convertible_to<EventId>;
        { EventPriorityChecker<EventClass>{}(event) } -> std::convertible_to<EventPriority>;
    };

    class __declspec(novtable) Event {
    public:
        inline Event() noexcept;

        inline ~Event() noexcept;

        [[nodiscard]] constexpr inline EventId GetId() const noexcept;

        [[nodiscard]] constexpr inline EventPriority GetPriority() const noexcept;

        template<EventType EventClass>
        [[nodiscard]] __declspec(restrict) constexpr inline EventClass *Cast() const noexcept;

        template<EventType EventClass, typename...Args>
        [[nodiscard]] static inline std::shared_ptr<Event> MakeEvent(Args...args) noexcept;

    protected:
        template<EventType EventClass, typename...EventArgs>
        constexpr inline void Prepare(EventArgs...args) noexcept;

    protected:
        void *m_event;
        std::function<void(void *)> m_destructor;
        EventId m_id;
        EventPriority m_priority;
    };

    struct EventLess {
        bool operator()(const EventPtr &lhs, const EventPtr &rhs) const
        { return lhs->GetPriority() < rhs->GetPriority(); }
    };

    using EventQueue = std::priority_queue<EventPtr, std::vector<EventPtr>, EventLess>;
}

#endif //HEADERTECH_EVENT_H
