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

#include <Component.h>
#include <Logging.h>

namespace HeaderTech::EntityComponentSystem {
    namespace details {
        struct BaseSetContent {
            EntityId id;
            std::uint64_t index;
        };

        struct BaseSetHash {
            inline size_t operator()(const BaseSetContent &val) const
            { return phmap::HashState::combine(phmap::Hash<EntityId>{}(val.id)/*, phmap::Hash<EntityId>{}(val.index)*/); }
        };

        struct BaseSetEq {
            inline bool operator()(const BaseSetContent &a, const BaseSetContent &b) const
            { return std::equal_to<>()(a.id, b.id)/* && std::equal_to<>()(a.index, b.index)*/; }
        };

        using BaseSet = phmap::flat_hash_set<BaseSetContent, BaseSetHash, BaseSetEq>;
//        using BaseSet = std::unordered_set<EntityId>;

        class EntitySet : public BaseSet {
        public:
            EntitySet() noexcept = default;

            virtual ~EntitySet() noexcept = default;

            [[nodiscard]] inline std::uint64_t Add(EntityId id) noexcept;

            virtual inline void Remove(EntityId id) noexcept;

            [[nodiscard]] inline std::uint64_t EntityIndex(EntityId id) const noexcept;

            [[nodiscard]] inline bool Contains(EntityId id) const noexcept;

        protected:
            [[nodiscard]] inline BaseSet::const_iterator Find(EntityId id) const noexcept;
        };

        template<Component ComponentType>
        class EntitySetIterator final {
        public:
            inline EntitySetIterator(
                    std::vector<ComponentType *> &components,
                    BaseSet &entities,
                    const BaseSet::size_type &idx
            );

            inline EntitySetIterator &operator++() noexcept;

            inline EntitySetIterator &operator--() noexcept;

            inline EntitySetIterator &operator+=(const BaseSet::size_type &value) noexcept;

            inline EntitySetIterator &operator+(const BaseSet::size_type &value) noexcept;

            inline EntitySetIterator &operator-=(const BaseSet::size_type &value) noexcept;

            inline EntitySetIterator &operator-(const BaseSet::size_type &value) noexcept;

            [[nodiscard]] inline ComponentType &operator[](const BaseSet::size_type &value) noexcept;

            [[nodiscard]] inline bool operator==(const EntitySetIterator &other) noexcept;

            [[nodiscard]] inline bool operator!=(const EntitySetIterator &other) noexcept;

            [[nodiscard]] inline bool operator<(const EntitySetIterator &other) noexcept;

            [[nodiscard]] inline bool operator>(const EntitySetIterator &other) noexcept;

            [[nodiscard]] inline bool operator<=(const EntitySetIterator &other) noexcept;

            [[nodiscard]] inline bool operator>=(const EntitySetIterator &other) noexcept;

            [[nodiscard]] inline ComponentType *operator->() noexcept;

            [[nodiscard]] inline ComponentType &operator*() noexcept;

        private:
            BaseSet *m_entities;
            BaseSet::size_type m_index;
            std::vector<ComponentType *> *m_components;
        };
    }

    template<Component ComponentType>
    class EntityComponentDataSet final : public details::EntitySet {
    public:
        using iterator = details::EntitySetIterator<ComponentType>;
    public:
        inline EntityComponentDataSet() noexcept;

        inline ~EntityComponentDataSet() noexcept final;

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

//        [[nodiscard]] inline details::EntitySetIterator<ComponentType> cbegin() const noexcept;

//        [[nodiscard]] inline details::EntitySetIterator<ComponentType> begin() const noexcept;

//        [[nodiscard]] inline details::EntitySetIterator<ComponentType> begin() noexcept;

//        [[nodiscard]] inline details::EntitySetIterator<ComponentType> cend() const noexcept;

//        [[nodiscard]] inline details::EntitySetIterator<ComponentType> end() const noexcept;

//        [[nodiscard]] inline details::EntitySetIterator<ComponentType> end() noexcept;

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
