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

#ifndef HEADERTECH_EVENTQUEUE_INL
#define HEADERTECH_EVENTQUEUE_INL

#include <Core/Event/Event.hpp>
#include <Core/Event/EventQueue.hpp>

namespace HeaderTech::Core::Event {
    template<Event AnEvent, EventPriority Priority, typename... Args>
    inline void EventQueue::Push(Args &&... args)
    {
        static_assert(Priority < Priority_Queue_Size);
        Push(
                m_queues[Priority].emplace(
                        AnyEvent::MakeEvent<AnEvent>(
                                std::forward<Args>(args)...
                        )
                )
        );
    }

    [[nodiscard]] inline auto EventQueue::Top() -> EventPtr
    {
        EventPriority idx = 0U;
        for (; idx < Priority_Queue_Size && m_queues[idx].empty(); ++idx) {
        }
        if (m_queues[idx].empty()) { return nullptr; }
        auto event = m_queues[idx].front();
        m_queues[idx].pop();
        for (++idx; idx < Priority_Queue_Size; ++idx) {
            if (!m_queues[idx].empty()) {
                m_queues[idx - 1U].push(std::move(m_queues[idx].front()));
                m_queues[idx].pop();
            }
        }
        return event;
    }

    [[nodiscard]] inline bool EventQueue::IsEmpty() const
    {
        for (EventPriority idx = 0U; idx < Priority_Queue_Size; ++idx) {
            if (!m_queues[idx].empty()) { return false; }
        }
        return true;
    }
}

#endif //HEADERTECH_EVENTQUEUE_INL