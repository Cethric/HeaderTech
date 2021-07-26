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

#ifndef HEADERTECH_EVENTDISPATCHER_INL
#define HEADERTECH_EVENTDISPATCHER_INL

#include <Core/Event/EventDispatcher.hpp>

#include <Core/Exports.h>
#include <Core/Event/impl/Event.inl>
#include <Core/Event/impl/EventQueue.inl>
#include <Core/Event/impl/EventHandler.inl>
#include <Core/Event/impl/EventHandlerQueue.inl>

#include <iostream>

namespace HeaderTech::Core::Event {
    inline EventDispatcher::EventDispatcher() noexcept: std::enable_shared_from_this<EventDispatcher>()
    {}

    inline EventDispatcher::~EventDispatcher() noexcept = default;

    template<Event AnEvent, EventPriority Priority, typename...Args>
    inline void EventDispatcher::Dispatch(Args &&... args) noexcept
    { m_queue.Push<AnEvent, Priority>(std::forward<Args>(args)...); }

    template<Event AnEvent, typename... Args>
    inline void EventDispatcher::DispatchNow(Args &&... args) noexcept
    { ProcessEvent(AnyEvent::MakeEvent<AnEvent>(std::forward<Args>(args)...)); }

    template<Event AnEvent, EventPriority Priority>
    inline void EventDispatcher::Bind(EventHandler<AnEvent> auto &&handler) noexcept
    { m_handlerQueue.Bind<AnEvent, Priority, decltype(handler)>(std::forward<decltype(handler)>(handler)); }
}

#endif //HEADERTECH_EVENTDISPATCHER_INL
