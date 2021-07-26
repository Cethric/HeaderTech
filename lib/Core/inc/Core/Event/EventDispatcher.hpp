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

#ifndef HEADERTECH_EVENTDISPATCHER_HPP
#define HEADERTECH_EVENTDISPATCHER_HPP

#include <queue>
#include <array>
#include <memory>
#include <utility>
#include <vector>
#include <concepts>
#include <functional>
#include <type_traits>
#include <iostream>

#include <phmap.h>
#include <ctti/type_id.hpp>

#include <Core/Exports.h>
#include <Core/Event/Event.hpp>
#include <Core/Event/EventQueue.hpp>
#include <Core/Event/EventHandler.hpp>
#include <Core/Event/EventHandlerQueue.hpp>

namespace HeaderTech::Core::Event {
    class HeaderTech_Core_Export EventDispatcher : public std::enable_shared_from_this<EventDispatcher> {
    public:
        inline EventDispatcher() noexcept;

        inline ~EventDispatcher() noexcept;

        void ProcessEvent() noexcept;

        template<Event AnEvent, EventPriority Priority, typename...Args>
        inline void Dispatch(Args &&...args) noexcept;

        template<Event AnEvent, typename...Args>
        inline void DispatchNow(Args &&...args) noexcept;

        template<Event AnEvent, EventPriority Priority>
        inline void Bind(EventHandler<AnEvent> auto &&handler) noexcept;

        inline auto Shared() noexcept
        { return shared_from_this(); }

    protected:
        void ProcessEvent(const EventPtr &event) noexcept;

    private:
        EventQueue        m_queue;
        EventHandlerQueue m_handlerQueue;
    };

    using EventDispatcherPtr = std::shared_ptr<EventDispatcher>;
}

#endif //HEADERTECH_EVENTDISPATCHER_HPP
