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

#ifndef HEADERTECH_EVENT_HPP
#define HEADERTECH_EVENT_HPP

#include <memory>
#include <type_traits>
#include <concepts>

#include <ctti/type_id.hpp>

#include <Core/Exports.h>

namespace HeaderTech::Core::Event {
    using EventId = ctti::type_id_t;

    using EventPriority = std::uint_least8_t;

    const EventPriority Priority_Queue_Size = 16U;

    template<typename EventType>
    concept Event = requires(EventType e) {
        { ctti::type_id(e) } -> std::same_as<EventId>;
    };

    template<Event AnEvent>
    constexpr EventId make_event_id()
    { return ctti::type_id<AnEvent>(); }

    class HeaderTech_Core_Export AnyEvent {
        using RealEventPtr = void *;
        using EventDeleter = std::function<void(RealEventPtr)>;
    public:
        template<Event AnEvent, typename...Args>
        static inline auto MakeEvent(Args...args) noexcept
        {
            return std::make_shared<AnyEvent>(
                    make_event_id<AnEvent>(),
                    new AnEvent(std::forward<Args>(args)...),
                    [](void *ev) {
                        auto evt = static_cast<AnEvent *>(ev);
                        delete evt;
                    }
            );
        }

    public:
        AnyEvent(EventId id, RealEventPtr event, EventDeleter deleter) noexcept;

        ~AnyEvent() noexcept;

        template<Event AnEvent>
        auto Convert() const noexcept -> AnEvent *;

        template<Event AnEvent>
        [[nodiscard]] bool IsEvent() const noexcept;

        [[nodiscard]] EventId Id() const noexcept;

    private:
        EventId      m_id;
        RealEventPtr m_event;
        EventDeleter m_eventDeleter;
    };

    using EventPtr = std::shared_ptr<AnyEvent>;
}

#endif //HEADERTECH_EVENT_HPP
