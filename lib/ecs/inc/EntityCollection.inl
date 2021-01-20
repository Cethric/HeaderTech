//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITYCOLLECTION_INL
#define HEADERTECH_ENTITYCOLLECTION_INL

#include <algorithm>
#include <unordered_set>

#include <EntityCollection.h>

namespace HeaderTech::EntityComponentSystem {
    namespace details {
        struct EntityIdStruct final {
            std::uint32_t m_generation;
            std::uint32_t m_count;

            inline EntityIdStruct() noexcept
                    : m_generation(0),
                      m_count(0),
                      m_log(HeaderTech::Logging::get_or_make_logger_async<EntityIdStruct>())
            {}

            inline EntityIdStruct(std::uint32_t generation, std::uint32_t count) noexcept
                    : m_generation(generation),
                      m_count(count),
                      m_log(HeaderTech::Logging::get_or_make_logger_async<EntityIdStruct>())
            {}

            inline explicit EntityIdStruct(EntityId id) noexcept
                    : m_generation((id & 0xFFFFFFFF00000000ULL) >> 32),
                      m_count(id & 0xFFFFFFFFULL),
                      m_log(HeaderTech::Logging::get_or_make_logger_async<EntityIdStruct>())
            {}

            [[nodiscard]] inline EntityIdStruct &NextGeneration() noexcept
            {
                [[unlikely]] if (m_generation == 0xffffffffULL) {
                    SPDLOG_LOGGER_WARN(
                            m_log,
                            "EntityBuilder {} has been recycled {} times causing the generation to reset to 0",
                            m_count,
                            0xffffffffULL
                    );
                }
                m_generation++;
                return *this;
            }

            [[nodiscard]] inline EntityId ToEntityId() const noexcept
            { return ((EntityId) m_generation) << 32 | m_count; }

        private:
            HeaderTech::Logging::Logger m_log;
        };

        struct EntityComponentData final {
            std::unique_ptr<EntitySet> components;
        };
    }

    inline EntityCollection::EntityCollection() noexcept
            : m_activeEntities(),
              m_releasedEntities(),
              m_activeEntityData(),
              m_log(HeaderTech::Logging::get_or_make_logger_async<EntityCollection>())
    {}

    inline EntityBuilder EntityCollection::AddEntity() noexcept
    {
        auto id = GetNextId();
        SPDLOG_LOGGER_DEBUG(
                m_log,
                "The next available entity has been registered: {}:{} ({:064b})",
                id.m_count,
                id.m_generation,
                id.ToEntityId()
        );
        return EntityBuilder(m_activeEntities.emplace_back(id.ToEntityId()), this);
    }

    inline Entity EntityCollection::GetEntity(EntityId id) const noexcept
    {
        return Entity(id, this);
    }

    inline void EntityCollection::ReleaseEntity(EntityId id) noexcept
    {
        auto entity = details::EntityIdStruct(id);
        SPDLOG_LOGGER_DEBUG(
                m_log,
                "Released entity: {}:{} ({:064b})",
                entity.m_count,
                entity.m_generation,
                id
        );
        m_activeEntities.erase(
                std::remove(std::begin(m_activeEntities), std::end(m_activeEntities), id),
                std::end(m_activeEntities)
        );
        RemoveEntity(id);
        m_releasedEntities.push(id);
    }

    template<Component ComponentType>
    inline std::uint64_t EntityCollection::ComponentSize() const noexcept
    {
        const auto pool = AssureComponentData<ComponentType>();
        return pool ? pool->size() : 0;
    }

    template<Component ComponentType>
    inline std::vector<ComponentType> *EntityCollection::All() const noexcept
    {
        const auto index = ComponentIdSeq<ComponentType>::value();
        return index < m_activeEntityData.size() && m_activeEntityData[index].components
               ? &static_cast<EntityComponentDataSetPtr<ComponentType>>(m_activeEntityData[index].components.get())->All()
               : nullptr;
    }

    template<Component ComponentType>
    inline EntityComponentDataSet <ComponentType> *EntityCollection::AllSet() const noexcept
    {
        const auto index = ComponentIdSeq<ComponentType>::value();
        if (index < m_activeEntityData.size() && m_activeEntityData[index].components) {
            auto set = m_activeEntityData[index].components.get();
            return static_cast<EntityComponentDataSetPtr<ComponentType>>(set);
        }
        return nullptr;
    }

    template<Component ComponentType>
    ComponentType *EntityCollection::AtUnsafe(EntityId id) const noexcept
    {
        const auto index = ComponentIdSeq<ComponentType>::value();
        return static_cast<EntityComponentDataSetPtr<ComponentType>>(
                m_activeEntityData[index].components.get()
        )->Get(id);
    }

    inline details::EntityIdStruct EntityCollection::GetNextId() noexcept
    {
        if (m_releasedEntities.empty()) {
            return details::EntityIdStruct(0, m_activeEntities.size());
        }
        auto entity = m_releasedEntities.front();
        m_releasedEntities.pop();
        return details::EntityIdStruct(entity).NextGeneration();
    }

    inline void EntityCollection::RemoveEntity(EntityId id) noexcept
    {
        for (auto &compData : m_activeEntityData) {
            if (compData.components && compData.components->Contains(id)) {
                compData.components->Remove(id);
            }
        }
    }

    template<Component ComponentType>
    inline EntityComponentDataSetPtr <ComponentType> EntityCollection::AssureComponentData() noexcept
    {
        const auto index = ComponentIdSeq<ComponentType>::value();

        SPDLOG_LOGGER_DEBUG(m_log, "Assure Component at index exists: {}", index);

        if (index >= m_activeEntityData.size()) {
            SPDLOG_LOGGER_DEBUG(m_log, "Resize for component: {}", index);
            m_activeEntityData.resize(index + 1);
        }

        if (auto &&data = m_activeEntityData[index]; !data.components) {
            SPDLOG_LOGGER_DEBUG(m_log, "Reset for component: {}", index);
            auto result = new EntityComponentDataSet<ComponentType>();
            data.components.reset(result);
            return result;
        }

        return static_cast<EntityComponentDataSetPtr<ComponentType>>(m_activeEntityData[index].components.get());
    }

    template<Component ComponentType>
    inline EntityComponentDataSetPtr <ComponentType> EntityCollection::AssureComponentData() const noexcept
    {
        const auto index = ComponentIdSeq<ComponentType>::value();
        SPDLOG_LOGGER_DEBUG(m_log, "Assure Component at index exists: {} -> {}", index,
                            index < m_activeEntityData.size() && m_activeEntityData[index].components);
        return index < m_activeEntityData.size() && m_activeEntityData[index].components
               ? static_cast<EntityComponentDataSetPtr<ComponentType>>(m_activeEntityData[index].components.get())
               : nullptr;
    }

    template<Component ComponentType, typename... Args>
    inline void EntityCollection::SetEntityComponentValue(EntityId id, Args... args) noexcept
    { AssureComponentData<ComponentType>()->SetValue(id, std::forward<Args>(args)...); }

    template<Component ComponentType>
    void EntityCollection::RemoveEntityComponentValue(EntityId id) noexcept
    { AssureComponentData<ComponentType>()->Remove(id); }
}

#endif //HEADERTECH_ENTITYCOLLECTION_INL
