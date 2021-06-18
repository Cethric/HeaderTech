/*==============================================================================
 = BSD 3-Clause License
 =
 = Copyright (c) 2021, Cethric
 = All rights reserved.
 =
 = Redistribution and use in source and binary forms, with or without
 = modification, are permitted provided that the following conditions are met:
 =
 = 1. Redistributions of source code must retain the above copyright notice, this
 =    list of conditions and the following disclaimer.
 =
 = 2. Redistributions in binary form must reproduce the above copyright notice,
 =    this list of conditions and the following disclaimer in the documentation
 =    and/or other materials provided with the distribution.
 =
 = 3. Neither the name of the copyright holder nor the names of its
 =    contributors may be used to endorse or promote products derived from
 =    this software without specific prior written permission.
 =
 = THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 = AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 = IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 = DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 = FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 = DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 = SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 = CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 = OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 = OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 =============================================================================*/

#ifndef HEADERTECH_EVENTHANDLER_HPP
#define HEADERTECH_EVENTHANDLER_HPP

#include <concepts>
#include <type_traits>
#include <functional>
#include <queue>
#include <memory>
#include <unordered_map>

#include <phmap.h>

#include <Event/Exports.h>
#include <Event/Event.hpp>


namespace HeaderTech::Event {
    using EventHandlerPriority = std::uint8_t;

    template<Event EventName>
    using EventHandlerCallbackFunction = std::function<bool( const EventName&)>;

    class HeaderTech_Event_Export EventHandler final {
        using EventHandlerCallerFunction = std::function<bool(const EventStorage *)>;
    public:
        EventHandler(const EventHandlerCallerFunction &caller, EventHandlerPriority priority) noexcept;

        ~EventHandler() noexcept;

        [[nodiscard]] inline EventHandlerPriority Priority() const noexcept
        { return m_priority; }

        bool HandleEvent(const EventStorage *storage) noexcept;

    protected:
        EventHandlerCallerFunction m_caller;
        EventHandlerPriority       m_priority;
        bool                       m_disabled;
    };

    using EventHandlerPtr = std::shared_ptr<EventHandler>;

    struct EventHandlerLess final {
        inline bool operator()(const EventHandlerPtr &lhs, const EventHandlerPtr &rhs) const
        { return lhs->Priority() < rhs->Priority(); }
    };

    class EventHandlerQueue final : public std::priority_queue<
            EventHandlerPtr,
            std::vector<EventHandlerPtr>,
            EventHandlerLess
    > {
    public:
        [[nodiscard]] inline auto data() const noexcept -> decltype(c)
        { return c; }
    };

    using EventHandlerMap = phmap::flat_hash_map<EventId, EventHandlerQueue>;

    namespace Binding {
        template<typename EventHandlerName, Event EventName>
        struct Binder {
            static inline auto Bind(
                    EventHandlerName &handler,
                    EventHandlerPriority priority
            ) noexcept -> HeaderTech::Event::EventHandlerPtr
            {
                return std::make_shared<EventHandler>(
                        [handler](const EventStorage *storage) {
                            using Handler = std::remove_cvref_t<decltype(handler)>;
                            if constexpr(std::is_pointer_v<Handler>) {
                                return handler->OnEvent(
                                        *storage->Cast<EventName>()
                                );
                            } else {
                                if constexpr(std::is_function_v<Handler> ||
                                             std::is_invocable<Handler, const EventName &>::value) {
                                    return handler(*storage->Cast<EventName>());
                                } else {
                                    return handler.OnEvent(
                                            *storage->Cast<EventName>()
                                    );
                                }
                            }
                        },
                        priority
                );
            }
        };

        template<typename EventHandlerName, typename EventName>
        concept BindableEventHandler = requires(EventHandlerName &&handler, EventName &&event) {
            {
            Binder<
                    std::remove_cvref_t<decltype(handler)>,
                    EventName
            >::Bind(handler, 0)
            } -> HeaderTech::Event::IsSameAs<HeaderTech::Event::EventHandlerPtr>;
        };
    };
}


#endif //HEADERTECH_EVENTHANDLER_HPP
