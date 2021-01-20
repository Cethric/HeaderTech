//
// Created by rogan2 on 29/10/2020.
//

#ifndef HEADERTECH_EVENTDISPATCHER_H
#define HEADERTECH_EVENTDISPATCHER_H

#include <Event.h>
#include <EventSubscription.h>

#include <concepts>
#include <memory>
#include <mutex>

namespace HeaderTech::Events {
    class EventDispatcher {
    public:
        inline EventDispatcher() noexcept;

        virtual inline ~EventDispatcher() noexcept = default;

        template<EventType EventClass, typename...Args>
        inline void Dispatch(Args...args) noexcept;

        template<EventType EventClass, typename...Args>
        inline void DispatchNow(Args...args) noexcept;

        inline void ProcessNextEvent() noexcept;

        inline void DrainEvents() noexcept;

        template<EventType EventClass, typename EventFunction>
        inline EventSubscriptionPtr Subscribe(const EventFunction &function) noexcept;

        template<EventType EventClass>
        inline void Unsubscribe(const EventSubscriptionPtr &subscription) noexcept;

        template<EventType EventClass>
        inline void Unsubscribe() noexcept;

    private:
        inline void ProcessEvent(const EventPtr &event) noexcept;

    private:
        EventQueue m_eventQueue;
        EventSubscriptionMap m_subscriptions;
        std::mutex m_eventMutex;
        std::mutex m_subscriptionMutex;
    };
}

#endif //HEADERTECH_EVENTDISPATCHER_H
