//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITYCOLLECTION_H
#define HEADERTECH_ENTITYCOLLECTION_H

#include <memory>
#include <queue>

#include <Entity.h>
#include <EntityBuilder.h>
#include <EntitySet.h>
#include <EntityComponentView.h>

#include <Logging.h>

#include <ctti/detailed_nameof.hpp>


namespace HeaderTech::EntityComponentSystem {
    namespace details {
        struct EntityIdStruct;

        struct EntityComponentData;
    }

    class EntityCollection {
        friend class Entity;

        friend class EntityBuilder;

    public:
        inline EntityCollection() noexcept;

        EntityCollection(EntityCollection &) = delete;

        inline EntityBuilder AddEntity() noexcept;

        [[nodiscard]] inline Entity GetEntity(EntityId id) const noexcept;

        inline void ReleaseEntity(EntityId id) noexcept;

        template<Component ComponentType>
        [[nodiscard]] inline std::uint64_t ComponentSize() const noexcept;

        template<Component ComponentType>
        [[nodiscard]] inline std::vector<ComponentType> *All() const noexcept;

        template<Component ComponentType>
        [[nodiscard]] inline EntityComponentDataSet<ComponentType> *AllSet() const noexcept;

        template<Component ComponentType>
        [[nodiscard]] inline ComponentType *AtUnsafe(EntityId id) const noexcept;

        template<Component...Includes, Component...Excludes>
        [[nodiscard]] inline std::shared_ptr<EntityComponentView<EntityComponentViewExcludes<Excludes...>, Includes...>>
        CreateView(EntityComponentViewExcludes<Excludes...> = {}) noexcept
        {
            using View = EntityComponentView<EntityComponentViewExcludes<Excludes...>, Includes...>;
            SPDLOG_LOGGER_INFO(m_log, "Creating entity view: {}", ctti::detailed_nameof<View>().full_name().str());
            return std::make_shared<View>(
                    AssureComponentData<Includes>()...,
                    AssureComponentData<Excludes>()...
            );
        }

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
