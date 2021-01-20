//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITYCOMPONENTVIEW_H
#define HEADERTECH_ENTITYCOMPONENTVIEW_H

#include <EntitySet.h>
#include <Component.h>
#include <EntityCollection.h>
#include <EntityComponentView.h>

#include <tuple>
#include <memory>
#include <algorithm>
#include <iterator>

namespace HeaderTech::EntityComponentSystem {
    namespace details {
    }

    template<Component...Excludes>
    struct EntityComponentViewExcludes final {
        using T = EntityComponentViewExcludes;
        static constexpr auto size = sizeof...(Excludes);
    };

    template<Component ComponentType>
    using DataSet = EntityComponentDataSet<ComponentType>;
    template<Component...Components>
    using DataSetTuple = std::tuple<DataSet<Components> *...>;

    template<typename...>
    class EntityComponentView;

    template<Component...Excludes, Component...Includes>
    class EntityComponentView<EntityComponentViewExcludes<Excludes...>, Includes...> final {
    protected:
        using view_iterator_category = std::bidirectional_iterator_tag;
        using view_iterator_value_type = std::tuple<EntityId, Includes * ...>;
        using view_iterator_difference_type = size_t;
        using view_iterator_pointer = view_iterator_value_type *;
        using view_iterator_reference = view_iterator_value_type;
        using view_iterator_base = std::iterator<
                view_iterator_category,
                view_iterator_value_type,
                view_iterator_difference_type,
                view_iterator_pointer,
                view_iterator_reference
        >;

        class view_iterator final : public view_iterator_base {
            friend class EntityComponentView<EntityComponentViewExcludes<Excludes...>, Includes...>;

            using SetIterator = details::EntitySet::iterator;

        private:
            view_iterator(
                    const SetIterator &setBegin,
                    const SetIterator &setEnd,
                    const SetIterator &setCurrent,
                    DataSetTuple<Includes...> includes,
                    DataSetTuple<Excludes...> excludes
            ) noexcept
                    : m_includes(includes),
                      m_excludes(excludes),
                      m_setBegin(setBegin),
                      m_setEnd(setEnd),
                      m_setCurrent(setCurrent)
            {
                if (m_setCurrent != m_setEnd && !IsValid()) {
                    ++(*this);
                }
            }

        protected:
            [[nodiscard]] inline bool IsValid() const noexcept
            {
                const EntityId entity = (*m_setCurrent).id;
                const auto includes = (std::get<DataSet<Includes> *>(m_includes)->Contains(entity) && ...);
                const auto excludes = (!std::get<DataSet<Excludes> *>(m_excludes)->Contains(entity) && ...);
                return includes && excludes;
            }

        public:
            view_iterator &operator++() noexcept
            {
                while (++m_setCurrent != m_setEnd && !IsValid());
                return *this;
            }

            view_iterator operator++(int) noexcept
            {
                auto retval = *this;
                ++(*this);
                return retval;
            }

            view_iterator &operator--() noexcept
            {
                while (--m_setCurrent != m_setEnd && !IsValid());
                return *this;
            }

            view_iterator operator--(int) noexcept
            {
                auto retval = *this;
                ++(*this);
                return retval;
            }

            bool operator==(view_iterator other)
            { return m_setCurrent == other.m_setCurrent; }

            bool operator!=(view_iterator other)
            { return m_setCurrent != other.m_setCurrent; }

            view_iterator_reference operator*() const
            {
                EntityId entity = (*m_setCurrent).id;
                return std::make_tuple(entity, std::get<DataSet<Includes> *>(m_includes)->Get(entity)...);
            };

        private:
            DataSetTuple<Includes...> m_includes;
            DataSetTuple<Excludes...> m_excludes;
            SetIterator m_setBegin;
            SetIterator m_setEnd;
            SetIterator m_setCurrent;
        };

    public:
        inline EntityComponentView(DataSet<Includes> *...includes, DataSet<Excludes> *...excludes) noexcept
                : m_includes(includes...),
                  m_excludes(excludes...),
                  m_entities()
        {
            m_entities = Candidate();
        }

        inline ~EntityComponentView() noexcept
        {}

        [[nodiscard]] inline view_iterator begin() noexcept
        { return view_iterator{m_entities.begin(), m_entities.end(), m_entities.begin(), m_includes, m_excludes}; }

        [[nodiscard]] inline view_iterator end() noexcept
        { return view_iterator{m_entities.begin(), m_entities.end(), m_entities.end(), m_includes, m_excludes}; }

    protected:
        [[nodiscard]] inline details::EntitySet Candidate() const noexcept
        {
            auto set = std::min(
                    {static_cast<const details::EntitySet *>(std::get<DataSet<Includes> *>(m_includes))...},
                    [](const auto *lhs, const auto *rhs) { return lhs->size() < rhs->size(); }
            );
            return *set;
        }

        [[nodiscard]] inline bool Contains(EntityId entity) noexcept
        {
            return (
                    std::get<DataSet<Includes> *>(m_includes)->Contains(entity) && ...
            );
        }

    private:
        details::EntitySet m_entities;
        DataSetTuple<Includes...> m_includes;
        DataSetTuple<Excludes...> m_excludes;
    };

    template<Component Include>
    class EntityComponentView<EntityComponentViewExcludes<>, Include>  final {
    protected:
        using view_iterator_category = std::bidirectional_iterator_tag;
        using view_iterator_value_type = std::tuple<EntityId, Include *>;
        using view_iterator_difference_type = size_t;
        using view_iterator_pointer = view_iterator_value_type *;
        using view_iterator_reference = view_iterator_value_type;
        using view_iterator_base = std::iterator<
                view_iterator_category,
                view_iterator_value_type,
                view_iterator_difference_type,
                view_iterator_pointer,
                view_iterator_reference
        >;

        class view_iterator final : public view_iterator_base {
            friend class EntityComponentView<EntityComponentViewExcludes<>, Include>;

            using SetIterator = details::EntitySet::iterator;

        private:
            view_iterator(
                    const SetIterator &begin,
                    const SetIterator &end,
                    const SetIterator &current,
                    DataSet<Include> *includes
            ) noexcept
                    : m_setBegin(begin),
                      m_setEnd(end),
                      m_setCurrent(current),
                      m_includes(includes)
            {
                if (m_setCurrent != m_setEnd && !IsValid()) {
                    ++(*this);
                }
            }

        protected:
            [[nodiscard]] inline bool IsValid() const noexcept
            {
                const EntityId entity = (*m_setCurrent).id;
                const auto includes = m_includes->Contains(entity);
                return includes;
            }

        public:
            view_iterator &operator++() noexcept
            {
                while (++m_setCurrent != m_setEnd && !IsValid());
                return *this;
            }

            view_iterator operator++(int) noexcept
            {
                auto retval = *this;
                ++(*this);
                return retval;
            }
            view_iterator &operator--() noexcept
            {
                while (--m_setCurrent != m_setEnd && !IsValid());
                return *this;
            }

            view_iterator operator--(int) noexcept
            {
                auto retval = *this;
                --(*this);
                return retval;
            }

            bool operator==(view_iterator other)
            { return m_setCurrent == other.m_setCurrent; }

            bool operator!=(view_iterator other)
            { return m_setCurrent != other.m_setCurrent; }

            view_iterator_reference operator*() const
            {
                EntityId entity = (*m_setCurrent).id;
                return std::make_tuple(entity, m_includes->Get(entity));
            };

        private:
            DataSet<Include> *m_includes;
            SetIterator m_setBegin;
            SetIterator m_setEnd;
            SetIterator m_setCurrent;
        };

    public:
        inline explicit EntityComponentView(DataSet<Include> *include) noexcept
                : m_include(include)
        {}

        inline ~EntityComponentView() noexcept
        {}

        [[nodiscard]] inline view_iterator begin() noexcept
        { return view_iterator(m_include->begin(), m_include->end(), m_include->begin(), m_include); }

        [[nodiscard]] inline view_iterator end() noexcept
        { return view_iterator(m_include->begin(), m_include->end(), m_include->end(), m_include); }

    private:
        DataSet<Include> *m_include;
    };
}

#endif //HEADERTECH_ENTITYCOMPONENTVIEW_H
