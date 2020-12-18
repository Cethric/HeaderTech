//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITYBUILDER_H
#define HEADERTECH_ENTITYBUILDER_H

#include <Logging.h>
#include <ecs/Entity.h>
#include <ecs/Component.h>

namespace HeaderTech::Scene::ECS {
    class EntityCollection;

    class EntityBuilder {
    private:
        friend class HeaderTech::Scene::ECS::EntityCollection;

        inline explicit EntityBuilder(
                EntityId id,
                EntityCollection *entityCollection
        ) noexcept;

    public:
        template<Component ComponentType, typename...Args>
        inline EntityBuilder &WithComponent(Args...args) noexcept;

        inline void Release();

        inline EntityId ToEntityId() const noexcept
        { return m_id; }

    protected:
        EntityId m_id;
        EntityCollection *m_collection;
    };
}
#endif //HEADERTECH_ENTITYBUILDER_H
