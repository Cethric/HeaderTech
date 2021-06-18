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

#include <concepts>
#include <functional>
#include <type_traits>

#include <ctti/type_id.hpp>

#include <Event/Exports.h>

namespace HeaderTech::Event {
    template<typename A, typename B>
    concept IsSameAs = std::same_as<
            std::remove_cvref<std::remove_all_extents<A>>,
            std::remove_cvref<std::remove_all_extents<A>>
    >;

    using EventId = ctti::type_id_t;

    using EventPriority = std::uint32_t;

    template<typename EventName>
    struct EventIdentifier {
        constexpr static auto id = ctti::type_id<EventName>();

        constexpr static auto Id() -> EventId
        { return ctti::type_id<EventName>(); }
    };

    template<typename EventName>
    concept Event = requires(EventName e) {
        { EventIdentifier<EventName>::id } -> IsSameAs<ctti::type_id_t>;
        { EventIdentifier<EventName>::Id() } -> IsSameAs<EventId>;
    };

    class EventStorage final {
        using EventDestructor = std::function<void(void *)>;
    private:
        HeaderTech_Event_Export EventStorage(void *event, EventId eventId, EventDestructor destructor) noexcept;

    public:
        template<Event EventName>
        inline static auto MakeEvent(auto &&...args) noexcept -> EventStorage *
        {
            return new(std::nothrow) EventStorage(
                    new(std::nothrow) EventName{args...},
                    EventIdentifier<EventName>::Id(),
                    [](void *evt) { delete reinterpret_cast<EventName *>(evt); }
            );
        }

    public:
        HeaderTech_Event_Export ~EventStorage() noexcept;

        template<Event EventName>
        [[nodiscard]] inline auto Cast() const noexcept -> EventName *
        { return EventIdentifier<EventName>::Id() == m_eventId ? CastDangerous<EventName>() : nullptr; }

        template<Event EventName>
        [[nodiscard]] inline auto CastDangerous() const noexcept -> EventName *
        { return reinterpret_cast<EventName *>(m_event); }

        [[nodiscard]] inline const EventId &Id() const noexcept
        { return m_eventId; }

    private:
        void            *m_event;
        EventId         m_eventId;
        EventDestructor m_destructor;
    };

    using EventStoragePtr = EventStorage *;
}


#endif //HEADERTECH_EVENT_HPP
