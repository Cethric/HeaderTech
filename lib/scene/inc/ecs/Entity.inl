//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITY_INL
#define HEADERTECH_ENTITY_INL

#include <ecs/Entity.h>
#include <ecs/EntityCollection.h>

namespace HeaderTech::Scene::ECS {
    Entity::Entity(EntityId id, EntityCollection *entityCollection) noexcept
            : m_id(id),
              m_collection(entityCollection)
    {}

    template<Component ComponentType, typename... Args>
    Entity &Entity::AddComponent(Args... args) noexcept
    {
        m_collection->SetEntityComponentValue<ComponentType>(m_id, std::forward<Args>(args)...);
        return *this;
    }

    template<Component ComponentType>
    Entity &Entity::RemoveComponent() noexcept
    {
        m_collection->RemoveEntityComponentValue<ComponentType>(m_id);
        return *this;
    }

    void Entity::Release()
    { m_collection->ReleaseEntity(m_id); }

    EntityId Entity::GetId() const noexcept
    { return m_id; }
}

#endif //HEADERTECH_ENTITY_INL
