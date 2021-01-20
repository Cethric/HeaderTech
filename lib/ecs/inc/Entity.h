//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITY_H
#define HEADERTECH_ENTITY_H

#include <Component.h>

namespace HeaderTech::EntityComponentSystem {
    class EntityCollection;

    using EntityId = std::uint64_t;

    class Entity {
    private:
        friend class HeaderTech::EntityComponentSystem::EntityCollection;

        inline explicit Entity(
                EntityId id,
                const EntityCollection *entityCollection
        ) noexcept;

    public:
        template<Component ComponentType, typename... Args>
        inline Entity &AddComponent(Args...args) noexcept;


        template<Component ComponentType>
        inline Entity &RemoveComponent() noexcept;

        inline void Release();

        [[nodiscard]] inline EntityId GetId() const noexcept;

    private:
        EntityId m_id;
        EntityCollection *m_collection;
    };
}

#endif //HEADERTECH_ENTITY_H
