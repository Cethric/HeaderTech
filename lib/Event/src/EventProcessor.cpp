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

#include <Event/EventProcessor.hpp>

using namespace HeaderTech::Event;

EventProcessor::EventProcessor(const HeaderTech::Common::ClockPtr &clock) noexcept:
        m_bindings(),
        m_eventPriorityQueue(clock)
{

}

EventProcessor::~EventProcessor() noexcept
{
    m_bindings.clear();
}

void EventProcessor::ProcessTick()
{
    auto event = m_eventPriorityQueue.Pop();
    if (event != nullptr) {
        auto id = event->Id();

        auto bindings = m_bindings.find(id);
        if (bindings != m_bindings.end()) {
            for (const auto &binding :bindings->second.data()) {
                binding->HandleEvent(event);
            }
        }
    }
}

EventHandlerPtr EventProcessor::Bind(EventHandlerPtr handler, const EventId &eventId) noexcept
{
    m_bindings[eventId].emplace(handler);
    auto bindings = m_bindings.find(eventId);
    if (bindings == m_bindings.end()) {
        bindings = m_bindings.insert({eventId, {}}).first;
    }
    bindings->second.emplace(handler);
    return handler;
}

void EventProcessor::Dispatch(EventStorage *event) noexcept
{

}
