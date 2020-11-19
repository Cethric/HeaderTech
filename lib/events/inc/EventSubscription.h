//
// Created by rogan2 on 30/10/2020.
//

#ifndef HEADERTECH_EVENTSUBSCRIPTION_H
#define HEADERTECH_EVENTSUBSCRIPTION_H

#include <Event.h>

#include <concepts>
#include <memory>
#include <vector>
#include <unordered_map>

namespace HeaderTech::Events {

    class __declspec(novtable) EventSubscription {
    public:
        inline EventSubscription() noexcept;

        inline ~EventSubscription() noexcept;

        inline void Handle(const EventPtr &event) const noexcept;

        template<EventType EventClass, typename EventFunction>
        [[nodiscard]] static inline std::shared_ptr<class EventSubscription>
        CreateSubscription(const EventFunction &function) noexcept;

    protected:
        template<EventType EventClass, typename EventFunction>
        constexpr inline void Prepare(const EventFunction &function) noexcept;

    private:
        void *m_subscription;
        std::function<void(void *)> m_destructor;
        std::function<void(void *, const EventPtr &)> m_handler;
    };

    using EventSubscriptionPtr = std::shared_ptr<EventSubscription>;
    using EventSubscriptionList = std::vector<EventSubscriptionPtr>;
    using EventSubscriptionMap = std::unordered_map<EventId, EventSubscriptionList>;
}

#endif //HEADERTECH_EVENTSUBSCRIPTION_H
