//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITYCOLLECTION_H
#define HEADERTECH_ENTITYCOLLECTION_H

#include <memory>

#include <ecs/Entity.h>
#include <ecs/EntityBuilder.h>
#include <ecs/EntitySet.h>
#include <ecs/EntityComponentView.h>

#include <Logging.h>


namespace HeaderTech::Scene::ECS {
    namespace details {
        struct EntityIdStruct;

        struct EntityComponentData;
    }

    class EntityCollection {
        friend class EntityBuilder;

        friend class Entity;

    public:
        inline EntityCollection() noexcept;

        EntityCollection(EntityCollection &) = delete;

        inline EntityBuilder NextEntity() noexcept;

        inline Entity GetEntity(EntityId id) noexcept;

        inline void ReleaseEntity(EntityId id) noexcept;

        template<Component ComponentType>
        [[nodiscard]] inline std::uint64_t ComponentSize() const noexcept;

        template<Component ComponentType>
        [[nodiscard]] inline std::vector<ComponentType> *All() const noexcept;

        template<Component ComponentType>
        [[nodiscard]] inline details::EntitySet AllSet() const noexcept;

        template<Component ComponentType>
        [[nodiscard]] inline ComponentType *AtUnsafe(EntityId id) const noexcept;

        template<Component...ComponentTypes>
        [[nodiscard]]  inline EntityComponentViewPtr<ComponentTypes...> View() const noexcept;

    protected:
        inline details::EntityIdStruct GetNextId() noexcept;

        inline void RemoveEntity(EntityId id) noexcept;

    private:
        template<Component ComponentType>
        [[nodiscard]] inline EntityComponentDataSetPtr<ComponentType> AssureComponentData() noexcept;

        template<Component ComponentType>
        [[nodiscard]] inline EntityComponentDataSetPtr<ComponentType> AssureComponentData() const noexcept;

        template<Component ComponentType, typename...Args>
        inline void SetEntityComponentValue(EntityId id, Args...args) noexcept;

        template<Component ComponentType>
        inline void RemoveEntityComponentValue(EntityId id) noexcept;

    private:
        HeaderTech::Logging::Logger m_log;
        std::queue<EntityId> m_releasedEntities;
        std::vector<EntityId> m_activeEntities;
        std::vector<details::EntityComponentData> m_activeEntityData;
    };
}

#endif //HEADERTECH_ENTITYCOLLECTION_H
