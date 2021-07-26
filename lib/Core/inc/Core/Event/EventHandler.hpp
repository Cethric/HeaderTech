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

#include <memory>
#include <vector>
#include <functional>
#include <iostream>

#include <phmap.h>

#include <Core/Exports.h>
#include <Core/Event/Event.hpp>


namespace HeaderTech::Core::Event {
    template<typename EventHandlerType, typename AnEvent>
    concept EventHandlerFunction = requires(EventHandlerType handler, const AnEvent &evt) {
        requires Event<AnEvent>;
        { handler(evt) } -> std::convertible_to<bool>;
    };

    template<typename EventHandlerType, typename AnEvent>
    concept EventHandlerClassPtr = requires(EventHandlerType handler, const AnEvent &evt) {
        requires Event<AnEvent>;
        { handler->OnEvent(evt) } -> std::convertible_to<bool>;
    };

    template<typename EventHandlerType, typename AnEvent>
    concept EventHandlerClassRef = requires(EventHandlerType &handler, const AnEvent &evt) {
        requires Event<AnEvent>;
        { handler.OnEvent(evt) } -> std::convertible_to<bool>;
    };

    template<typename EventHandlerType, typename AnEvent>
    concept EventHandler = EventHandlerFunction<EventHandlerType, AnEvent> ||
                           EventHandlerClassPtr<EventHandlerType, AnEvent> ||
                           EventHandlerClassRef<EventHandlerType, AnEvent>;

    class HeaderTech_Core_Export AnyEventHandler {
        using HandlerFunction = std::function<bool(const EventPtr &)>;
    public:
        template<Event AnEvent>
        static inline auto MakeHandlerFunction(EventHandlerFunction<AnEvent> auto &&handler) noexcept -> HandlerFunction
        {
            return [&handler](const EventPtr &event) {
                auto evt = event->Convert<AnEvent>();
                if (evt != nullptr) {
                    return handler(*evt);
                }
                return false;
            };
        }

        template<Event AnEvent>
        static inline auto MakeHandlerFunction(EventHandlerClassPtr<AnEvent> auto &&handler) noexcept -> HandlerFunction
        {
            return [&handler](const EventPtr &event) {
                auto evt = event->Convert<AnEvent>();
                if (evt != nullptr) {
                    return handler->OnEvent(*evt);
                }
                return false;
            };
        }

        template<Event AnEvent>
        static inline auto MakeHandlerFunction(EventHandlerClassRef<AnEvent> auto &&handler) noexcept -> HandlerFunction
        {
            return [&handler](const EventPtr &event) {
                auto evt = event->Convert<AnEvent>();
                if (evt != nullptr) {
                    return handler.OnEvent(*evt);
                }
                return false;
            };
        }

    public:
        explicit AnyEventHandler(EventPriority priority, HandlerFunction handler) noexcept;

        bool Handle(const EventPtr &event);

    private:
        EventPriority   m_priority;
        HandlerFunction m_handler;
    };

    using EventHandlerPtr = std::shared_ptr<AnyEventHandler>;
    using EventHandlerVector = std::vector<EventHandlerPtr>;
    using EventHandlerMap = phmap::flat_hash_map<EventId, EventHandlerVector, std::hash<EventId>>;
}

#endif //HEADERTECH_EVENTHANDLER_HPP
