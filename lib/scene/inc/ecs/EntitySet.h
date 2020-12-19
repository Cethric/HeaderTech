//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITYSET_H
#define HEADERTECH_ENTITYSET_H


#include <concepts>
#include <type_traits>
#include <unordered_set>
#include <ctti/detailed_nameof.hpp>
#include <phmap.h>

#include <ecs/Component.h>
#include <Logging.h>

namespace HeaderTech::Scene::ECS {
    namespace details {
        using BaseSet = phmap::flat_hash_set<EntityId>;
//        using BaseSet = std::unordered_set<EntityId>;

        class EntitySet : public BaseSet {
        public:
            [[nodiscard]] inline std::uint64_t Add(EntityId id) noexcept;

            virtual inline void Remove(EntityId id) noexcept;

            [[nodiscard]] inline std::uint64_t EntityIndex(EntityId id) const noexcept;

            [[nodiscard]] inline bool Contains(EntityId id) const noexcept;
        };

        template<Component ComponentType>
        class EntitySetIterator final {
        public:
            EntitySetIterator(
                    std::vector<ComponentType *> &components,
                    BaseSet &entities,
                    const BaseSet::size_type &idx
            );

            EntitySetIterator &operator++() noexcept;

            EntitySetIterator operator++(int) noexcept;

            EntitySetIterator &operator--() noexcept;

            EntitySetIterator operator--(int) noexcept;

            EntitySetIterator &operator+=(const BaseSet::size_type &value) noexcept;

            EntitySetIterator &operator+(const BaseSet::size_type &value) noexcept;

            EntitySetIterator &operator-=(const BaseSet::size_type &value) noexcept;

            EntitySetIterator &operator-(const BaseSet::size_type &value) noexcept;

            [[nodiscard]] ComponentType &operator[](const BaseSet::size_type &value) noexcept;

            [[nodiscard]] bool operator==(const EntitySetIterator &other) noexcept;

            [[nodiscard]] bool operator!=(const EntitySetIterator &other) noexcept;

            [[nodiscard]] bool operator<(const EntitySetIterator &other) noexcept;

            [[nodiscard]] bool operator>(const EntitySetIterator &other) noexcept;

            [[nodiscard]] bool operator<=(const EntitySetIterator &other) noexcept;

            [[nodiscard]] bool operator>=(const EntitySetIterator &other) noexcept;

            [[nodiscard]] ComponentType *operator->() noexcept;

            [[nodiscard]] ComponentType &operator*() noexcept;

        private:
            BaseSet *m_entities;
            BaseSet::size_type m_index;
            std::vector<ComponentType *> *m_components;
        };
    }

    template<Component ComponentType>
    class EntityComponentDataSet final : public details::EntitySet {
    public:
        inline EntityComponentDataSet() noexcept;

        inline ~EntityComponentDataSet() noexcept;

        template<typename...Args>
        inline void SetValue(EntityId id, Args...args) noexcept;

        inline void Remove(EntityId id) noexcept final;

        [[nodiscard]] inline ComponentType *Get(EntityId id) noexcept;

        [[nodiscard]] inline std::vector<ComponentType *> &All() noexcept;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4068)
#endif
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

        [[nodiscard]] inline details::EntitySetIterator<ComponentType> cbegin() const noexcept;

        [[nodiscard]] inline details::EntitySetIterator<ComponentType> begin() const noexcept;

        [[nodiscard]] inline details::EntitySetIterator<ComponentType> begin() noexcept;

        [[nodiscard]] inline details::EntitySetIterator<ComponentType> cend() const noexcept;

        [[nodiscard]] inline details::EntitySetIterator<ComponentType> end() const noexcept;

        [[nodiscard]] inline details::EntitySetIterator<ComponentType> end() noexcept;

#pragma clang diagnostic pop
#ifdef _MSC_VER
#pragma warning(pop)
#endif

    private:
        HeaderTech::Logging::Logger m_log;
        std::vector<ComponentType *> m_components;
    };


    template<Component ComponentType>
    using EntityComponentDataSetPtr = EntityComponentDataSet<ComponentType> *;

}

#endif //HEADERTECH_ENTITYSET_H
