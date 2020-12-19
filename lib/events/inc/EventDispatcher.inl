//
// Created by rogan2 on 29/10/2020.
//

#ifndef HEADERTECH_EVENTDISPATCHER_INL
#define HEADERTECH_EVENTDISPATCHER_INL

#include <memory>
#include <algorithm>
#include <iterator>

#include <EventDispatcher.h>

namespace HeaderTech::Events {
    inline EventDispatcher::EventDispatcher() noexcept: m_eventMutex(), m_subscriptionMutex()
    {}

    template<EventType EventClass, typename... Args>
    inline void EventDispatcher::Dispatch(Args... args) noexcept
    {
        ProfileCpuScoped(event_dispatcher);
        std::lock_guard<std::mutex> lock(m_eventMutex);

        auto event = Event::MakeEvent<EventClass, Args...>(std::forward<Args>(args)...);
        m_eventQueue.push(std::move(event));
    }

    inline void EventDispatcher::ProcessNextEvent() noexcept
    {
        ProfileCpuScoped(next_event_processor);
        if (!m_eventQueue.empty() && m_eventMutex.try_lock()) {
            const EventPtr event = m_eventQueue.top();
            m_eventQueue.pop();
            m_eventMutex.unlock();
            ProcessEvent(event);
        }
    }

    template<EventType EventClass, typename EventFunction>
    EventSubscriptionPtr EventDispatcher::Subscribe(const EventFunction &function) noexcept
    {
        std::lock_guard<std::mutex> lock(m_subscriptionMutex);

        auto subscription = EventSubscription::CreateSubscription<EventClass, EventFunction>(function);
        constexpr auto id = EventIdChecker<EventClass>{}();
        const auto search = m_subscriptions.find(id);
        if (search == m_subscriptions.cend()) {
            EventSubscriptionList list{subscription};
            m_subscriptions[id] = list;
        } else {
            search->second.push_back(subscription);
        }
        return subscription;
    }

    template<EventType EventClass>
    void EventDispatcher::Unsubscribe(const EventSubscriptionPtr &subscription) noexcept
    {
        std::lock_guard<std::mutex> lock(m_subscriptionMutex);

        constexpr auto id = EventIdChecker<EventClass>{}();
        const auto search = m_subscriptions.find(id);
        if (search != m_subscriptions.cend()) {
            search->second.remove_if(
                    [&subscription](const EventSubscriptionPtr &other) { return other == subscription; }
            );
        }
    }

    template<EventType EventClass>
    void EventDispatcher::Unsubscribe() noexcept
    {
        std::lock_guard<std::mutex> lock(m_subscriptionMutex);

        constexpr auto id = EventIdChecker<EventClass>{}();
        m_subscriptions.erase(id);
    }

    inline void EventDispatcher::ProcessEvent(const EventPtr &event) noexcept
    {
        ProfileCpuScoped(event_processor);
        std::lock_guard<std::mutex> lock(m_subscriptionMutex);

        const auto subscriptions = m_subscriptions.find(event->GetId());
        if (subscriptions != m_subscriptions.end()) {
            for (const EventSubscriptionPtr &subscription : subscriptions->second) {
                subscription->Handle(event);
            }
        }
    }
}

#endif //HEADERTECH_EVENTDISPATCHER_INL
