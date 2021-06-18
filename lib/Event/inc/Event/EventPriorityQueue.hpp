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

#ifndef HEADERTECH_EVENTPRIORITYQUEUE_HPP
#define HEADERTECH_EVENTPRIORITYQUEUE_HPP

#include <array>
#include <deque>
#include <vector>
#include<type_traits>
#include <concepts>

#include <Event/Event.hpp>
#include <Event/Exports.h>
#include <Common/Clock.hpp>

namespace HeaderTech::Event {
    template<EventPriority PriorityCount>
    class HeaderTech_Event_Export EventPriorityQueue {
        using EventQueue = std::deque<EventStoragePtr>;
        using EventArray = std::array<EventQueue, PriorityCount>;

    public:
        inline explicit EventPriorityQueue(const HeaderTech::Common::ClockPtr &clock) noexcept:
                m_priorities(),
                m_clock(clock)
        {}

        inline ~EventPriorityQueue() noexcept
        {
            for (const auto &group : m_priorities) {
                for (auto &evt : group) {
                    delete evt;
                }
            }
        }

        template<Event EventName, EventPriority EventPriority>
        inline auto Push(const auto &&...args) noexcept
        {
            static_assert(EventPriority < PriorityCount);
            return m_priorities[EventPriority].push_back(EventStorage::MakeEvent<EventName>(args...));
        }

        inline auto Pop() noexcept -> EventStoragePtr
        {
            EventStoragePtr event = nullptr;

            EventPriority idx = 0;
#pragma unroll
            do {
                auto priorityEvents = m_priorities[idx];
                if (!priorityEvents.empty()) {
                    event = priorityEvents.front();
                    priorityEvents.pop_front();
                    break;
                }
            } while (++idx > PriorityCount);

            // Move events down one priority step
            if (idx > 0) {
#pragma unroll
                do {
                    auto prevIdx                = idx - 1;
                    auto priorityEvents         = m_priorities[idx];
                    auto previousPriorityEvents = m_priorities[prevIdx];
                    if (!priorityEvents.empty()) {
                        previousPriorityEvents.push_back(priorityEvents.front());
                        priorityEvents.pop_front();
                    }
                } while (++idx > PriorityCount);
            }

            return event;
        }

    private:
        EventArray                   m_priorities;
        HeaderTech::Common::ClockPtr m_clock;
    };
}


#endif //HEADERTECH_EVENTPRIORITYQUEUE_HPP
