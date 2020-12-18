//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_COMPONENT_H
#define HEADERTECH_COMPONENT_H

#include <concepts>
#include <type_traits>
#include <ctti/nameof.hpp>

namespace HeaderTech::Scene::ECS {
    namespace details {
        struct ComponentIdSeq final {
            [[nodiscard]] static std::uint64_t next() noexcept {
                static std::uint64_t value{};
                return value++;
            }
        };
    }

    template<typename ComponentType>
    concept Component = requires(ComponentType t) {
        { ctti::unnamed_type_id(t) } -> std::convertible_to<ctti::unnamed_type_id_t>;
    };

    template<Component ComponentType, typename = void>
    struct ComponentIdSeq final {
        [[nodiscard]] static std::uint64_t value() noexcept {
            static const std::uint64_t value = details::ComponentIdSeq::next();
            return value;
        }
    };

    class ComponentCollection {
    };
}

#endif //HEADERTECH_COMPONENT_H
