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

#ifndef HEADERTECH_EVENTPROCESSOR_HPP
#define HEADERTECH_EVENTPROCESSOR_HPP

#include <memory>
#include <concepts>
#include <type_traits>

#include <Event/Exports.h>
#include <Event/Event.hpp>
#include <Event/EventHandler.hpp>
#include <Event/EventPriorityQueue.hpp>
#include <Common/Clock.hpp>

namespace HeaderTech::Event {
    class HeaderTech_Event_Export EventProcessor : private std::enable_shared_from_this<EventProcessor> {
    public:
        EventProcessor(const HeaderTech::Common::ClockPtr &clock) noexcept;

        virtual ~EventProcessor() noexcept;

        template<Event EventName>
        inline auto Bind(
                Binding::BindableEventHandler<EventName> auto &&handler,
                EventHandlerPriority priority
        ) -> EventHandlerPtr
        {
            return Bind(
                    Binding::Binder<std::remove_cvref_t<decltype(handler)>, EventName>::Bind(handler, priority),
                    EventIdentifier<EventName>::Id()
            );
        }

        template<Event EventName, EventPriority EventPriority>
        inline auto Dispatch(auto &&...args) noexcept
        { return m_eventPriorityQueue.Push<EventName, EventPriority>(args...); }

    protected:
        void ProcessTick();

    private:
        EventHandlerPtr Bind(
                EventHandlerPtr handler,
                const EventId &eventId
        ) noexcept;

        void Dispatch(EventStorage *event) noexcept;

    protected:
        [[nodiscard]] inline auto SharedEventProcessor() const noexcept
        { return this->shared_from_this(); }

    private:
        EventHandlerMap        m_bindings;
        EventPriorityQueue<32> m_eventPriorityQueue;
    };

    using EventProcessorPtr = std::shared_ptr<EventProcessor>;
}


#endif //HEADERTECH_EVENTPROCESSOR_HPP
