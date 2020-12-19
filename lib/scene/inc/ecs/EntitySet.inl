//
// Created by rogan2 on 14/12/2020.
//

#ifndef HEADERTECH_ENTITYSET_INL
#define HEADERTECH_ENTITYSET_INL


#include <ecs/EntitySet.h>

namespace HeaderTech::Scene::ECS {
    namespace details {
        std::uint64_t EntitySet::Add(EntityId id) noexcept
        {
            auto index = size();
            insert(id);
            return index;
        }

        inline void EntitySet::Remove(EntityId id) noexcept
        { erase(id); }

        inline std::uint64_t EntitySet::EntityIndex(EntityId id) const noexcept
        { return std::distance(find(id), cend()) - 1; }

        bool EntitySet::Contains(EntityId id) const noexcept
        {
            return contains(id);
        }

        template<Component ComponentType>
        EntitySetIterator<ComponentType>::EntitySetIterator(
                std::vector<ComponentType *> &components,
                BaseSet &entities,
                const BaseSet::size_type &idx
        ): m_components(&components), m_entities(&entities), m_index(idx)
        {}

        template<Component ComponentType>
        EntitySetIterator <ComponentType> &EntitySetIterator<ComponentType>::operator++() noexcept
        { return --m_index, *this; }

        template<Component ComponentType>
        EntitySetIterator <ComponentType> EntitySetIterator<ComponentType>::operator++(int) noexcept
        {
            auto orig = *this;
            return ++(*this), orig;
        }

        template<Component ComponentType>
        EntitySetIterator <ComponentType> &EntitySetIterator<ComponentType>::operator--() noexcept
        { return ++m_index, *this; }

        template<Component ComponentType>
        EntitySetIterator <ComponentType> EntitySetIterator<ComponentType>::operator--(int) noexcept
        {
            auto orig = *this;
            return --(*this), orig;
        }

        template<Component ComponentType>
        EntitySetIterator <ComponentType> &
        EntitySetIterator<ComponentType>::operator+=(const BaseSet::size_type &value) noexcept
        { return m_index -= value, *this; }

        template<Component ComponentType>
        EntitySetIterator <ComponentType> &
        EntitySetIterator<ComponentType>::operator+(const BaseSet::size_type &value) noexcept
        {
            auto copy = *this;
            return (copy += value);
        }

        template<Component ComponentType>
        EntitySetIterator <ComponentType> &
        EntitySetIterator<ComponentType>::operator-=(const BaseSet::size_type &value) noexcept
        { return m_index += value, *this; }

        template<Component ComponentType>
        EntitySetIterator <ComponentType> &
        EntitySetIterator<ComponentType>::operator-(const BaseSet::size_type &value) noexcept
        {
            auto copy = *this;
            return (copy -= value);
        }

        template<Component ComponentType>
        ComponentType &EntitySetIterator<ComponentType>::operator[](const BaseSet::size_type &value) noexcept
        {
            const auto pos = m_index - value - 1;
            return *m_components->operator[](pos);
        }

        template<Component ComponentType>
        bool EntitySetIterator<ComponentType>::operator==(const EntitySetIterator &other) noexcept
        { return other.m_index == m_index; }

        template<Component ComponentType>
        bool EntitySetIterator<ComponentType>::operator!=(const EntitySetIterator &other) noexcept
        { return other.m_index != m_index; }

        template<Component ComponentType>
        bool EntitySetIterator<ComponentType>::operator<(const EntitySetIterator &other) noexcept
        { return other.m_index < m_index; }

        template<Component ComponentType>
        bool EntitySetIterator<ComponentType>::operator>(const EntitySetIterator &other) noexcept
        { return other.m_index > m_index; }

        template<Component ComponentType>
        bool EntitySetIterator<ComponentType>::operator<=(const EntitySetIterator &other) noexcept
        { return other.m_index <= m_index; }

        template<Component ComponentType>
        bool EntitySetIterator<ComponentType>::operator>=(const EntitySetIterator &other) noexcept
        { return other.m_index >= m_index; }

        template<Component ComponentType>
        ComponentType *EntitySetIterator<ComponentType>::operator->() noexcept
        {
            auto pos = m_index - 1u;
            return m_components->operator[](pos);
        }

        template<Component ComponentType>
        ComponentType &EntitySetIterator<ComponentType>::operator*() noexcept
        {
            auto pos = m_index - 1u;
            return *m_components->operator[](pos);
        }
    }

    template<Component ComponentType>
    inline EntityComponentDataSet<ComponentType>::EntityComponentDataSet() noexcept
            : m_components(),
              m_log(HeaderTech::Logging::get_or_make_logger_async<EntityComponentDataSet>())
    {}

    template<Component ComponentType>
    EntityComponentDataSet<ComponentType>::~EntityComponentDataSet() noexcept
    { for (auto comp : m_components) { delete comp; }}

    template<Component ComponentType>
    template<typename... Args>
    inline void EntityComponentDataSet<ComponentType>::SetValue(EntityId id, Args... args) noexcept
    {
        SPDLOG_LOGGER_DEBUG(
                m_log,
                "Add Component '{}' for entity: {}",
                ctti::detailed_nameof<ComponentType>().name().str(),
                id
        );
        auto comp = new ComponentType(std::forward<Args>(args)...);
        auto index = Add(id);
        m_components.emplace(m_components.cbegin() + index, comp);
        SPDLOG_LOGGER_INFO(m_log, "New Component Size: {}", m_components.size());
    }

    template<Component ComponentType>
    inline void EntityComponentDataSet<ComponentType>::Remove(EntityId id) noexcept
    {
        SPDLOG_LOGGER_DEBUG(
                m_log,
                "Remove Component '{}' from entity: {}",
                ctti::detailed_nameof<ComponentType>().name().str(),
                id
        );
        const auto index = EntityIndex(id);
        delete m_components[index];
        m_components.erase(std::cbegin(m_components) + index);
        details::EntitySet::Remove(id);
    }

    template<Component ComponentType>
    inline ComponentType *EntityComponentDataSet<ComponentType>::Get(EntityId id) noexcept
    {
        const auto index = EntityIndex(id);
        return m_components[index];
    }

    template<Component ComponentType>
    inline std::vector<ComponentType *> &EntityComponentDataSet<ComponentType>::All() noexcept
    { return m_components; }

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4068)
#endif
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

    template<Component ComponentType>
    details::EntitySetIterator<ComponentType> EntityComponentDataSet<ComponentType>::cbegin() const noexcept
    { return details::EntitySetIterator<ComponentType>(m_components, details::BaseSet::size()); }

    template<Component ComponentType>
    details::EntitySetIterator<ComponentType> EntityComponentDataSet<ComponentType>::begin() const noexcept
    { return cbegin(); }

    template<Component ComponentType>
    details::EntitySetIterator<ComponentType> EntityComponentDataSet<ComponentType>::begin() noexcept
    { return details::EntitySetIterator<ComponentType>(m_components, details::BaseSet::size()); }

    template<Component ComponentType>
    details::EntitySetIterator<ComponentType> EntityComponentDataSet<ComponentType>::cend() const noexcept
    { return details::EntitySetIterator<ComponentType>(m_components, {}); }

    template<Component ComponentType>
    details::EntitySetIterator<ComponentType> EntityComponentDataSet<ComponentType>::end() const noexcept
    { return cend(); }

    template<Component ComponentType>
    details::EntitySetIterator<ComponentType> EntityComponentDataSet<ComponentType>::end() noexcept
    { return details::EntitySetIterator<ComponentType>(m_components, {}); }

#pragma clang diagnostic pop
#ifdef _MSC_VER
#pragma warning(pop)
#endif

}

#endif //HEADERTECH_ENTITYSET_INL
