//
// Created by rogan2 on 30/10/2020.
//

#ifndef HEADERTECH_EVENTSUBSCRIPTION_INL
#define HEADERTECH_EVENTSUBSCRIPTION_INL

#include <EventSubscription.h>
#include <type_traits>

namespace HeaderTech::Events {
    namespace detail {
        template<EventType EventName, typename EventCallback>
        struct __declspec(novtable) SubscriptionBase {
            using Event = EventName;
        public:
            EventCallback m_callback;
            using EventCallbackType = typename std::remove_reference<std::remove_pointer<EventCallback>>::type;

            __declspec(noalias) constexpr inline void Handle(Event *event) const
            {
                Handle(
                        std::integral_constant<
                                bool,
                                std::conjunction_v<
                                        std::is_class<EventCallbackType>,
                                        std::is_pointer<EventCallback>
                                >
                        >{},
                        event
                );
            }

        private:
            [[maybe_unused]] __declspec(noalias) constexpr inline void Handle(std::true_type, Event *event) const
            { m_callback->OnEvent(event); }

            [[maybe_unused]] __declspec(noalias) constexpr inline void Handle(std::false_type, Event *event) const
            { m_callback(event); }
        };


        template<EventType EventName, typename EventFunction>
        __declspec(noalias) static constexpr inline void subscription_destructor(void *function) noexcept
        {
            using Caller = SubscriptionBase<EventName, EventFunction>;

            auto base = static_cast<Caller *>(function);
            delete base;
        }

        template<EventType EventName, typename EventFunction>
        __declspec(noalias) static constexpr inline void
        subscription_handler(void *function, const EventPtr &event) noexcept
        {
            using Caller = SubscriptionBase<EventName, EventFunction>;

            auto base = static_cast<Caller *>(function);
            auto cast = event->Cast<EventName>();
            [[likely]] if (cast) {
                base->Handle(cast);
            }
        }
    }

    inline EventSubscription::EventSubscription() noexcept: m_subscription(nullptr),
                                                            m_destructor(nullptr),
                                                            m_handler(nullptr)
    {}

    inline EventSubscription::~EventSubscription() noexcept
    {
        if (m_subscription) {
            m_destructor(m_subscription);
        }
    }

    inline void EventSubscription::Handle(const EventPtr &event) const noexcept
    { m_handler(m_subscription, event); }

    template<EventType EventClass, typename EventFunction>
    [[nodiscard]] inline std::shared_ptr<EventSubscription>
    EventSubscription::CreateSubscription(const EventFunction &function) noexcept
    {
        auto subscription = std::make_shared<EventSubscription>();
        subscription->Prepare<EventClass, EventFunction>(std::move(function));
        return subscription;
    }

    template<EventType EventClass, typename EventFunction>
    constexpr inline void EventSubscription::Prepare(const EventFunction &function) noexcept
    {
        using Caller = detail::SubscriptionBase<EventClass, EventFunction>;

        auto subscription = new Caller{.m_callback=std::move(function)};

        m_subscription = subscription;
        m_destructor = detail::subscription_destructor<EventClass, EventFunction>;
        m_handler = detail::subscription_handler<EventClass, EventFunction>;
    }
}

#endif //HEADERTECH_EVENTSUBSCRIPTION_INL
