//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITYBUILDER_INL
#define HEADERTECH_ENTITYBUILDER_INL

#include <EntityBuilder.h>
#include <EntityCollection.h>

namespace HeaderTech::EntityComponentSystem {
    inline EntityBuilder::EntityBuilder(EntityId id, EntityCollection *entityCollection) noexcept
            : m_id(id),
              m_collection(entityCollection)
    {}

    template<Component ComponentType, typename... Args>
    inline EntityBuilder &EntityBuilder::WithComponent(Args... args) noexcept
    {
        m_collection->SetEntityComponentValue<ComponentType>(m_id, std::forward<Args>(args)...);
        return *this;
    }

    inline void EntityBuilder::Release()
    { m_collection->ReleaseEntity(m_id); }
}

#endif //HEADERTECH_ENTITYBUILDER_INL
