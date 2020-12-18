//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITYCOMPONENTVIEW_INL
#define HEADERTECH_ENTITYCOMPONENTVIEW_INL

#include <ecs/EntityComponentView.h>
#include <ecs/EntityCollection.h>
#include <ecs/EntitySet.h>

#include <utility>

namespace HeaderTech::Scene::ECS {
    namespace details {
        template<typename EntitySet1, typename EntitySet2, typename EntitySetOut = EntitySet1>
        EntitySetOut EntitySetIntersection(const EntitySet1 &in1, const EntitySet2 &in2)
        {
            if (in2.size() < in1.size()) {
                return EntitySetIntersection(in2, in1);
            }
            EntitySet out;
            auto end = in2.end();
            for (const auto &item : in1) {
                if (in2.find(item) != end) {
                    out.insert(item);
                }
            }
            return out;
        }

        template<typename Result, typename FirstSet, typename LastSet>
        Result EntitySetIntersection2(const FirstSet &first, const LastSet &last)
        {
            return EntitySetIntersection<FirstSet, LastSet, Result>(
                    first,
                    last
            );
        }

        template<typename Result, typename FirstSet, typename SecondSet, typename ThirdSet, typename...Sets>
        Result EntitySetIntersection2(
                FirstSet &&first,
                SecondSet &&second,
                ThirdSet &&third,
                Sets &&...rest
        )
        {
            return EntitySetIntersection2<Result, Result, Sets...>(
                    EntitySetIntersection<Result, Result, ThirdSet>(
                            EntitySetIntersection<FirstSet, SecondSet, Result>(first, second),
                            third
                    ),
                    rest...
            );
        }


        template<Component... ComponentTypes>
        using ComponentTypeTuple = std::tuple<EntityId, ComponentTypes * ...>;

        template<Component... ComponentTypes>
        class EntityComponentViewIterator {
        public:
            inline EntityComponentViewIterator(
                    EntityCollection *collection,
                    EntitySet &entities,
                    bool fromStart
            ) noexcept
                    : m_isEnd(!fromStart),
                      m_entities(entities),
                      m_collection(collection),
                      m_iterator(fromStart ? m_entities.begin() : m_entities.end())
            {}

            inline bool operator!=(const EntityComponentViewIterator &rhs) noexcept
            {
                if (m_isEnd) {
                    return m_entities.end() != rhs.m_iterator;
                }
                if (rhs.m_isEnd) {
                    return m_iterator != m_entities.end();
                }
                return m_iterator != rhs.m_iterator;
            }

            inline EntityComponentViewIterator &operator++() noexcept
            { return m_iterator++, *this; }

            inline ComponentTypeTuple<ComponentTypes...> operator*() noexcept
            {
                EntityId entity = *m_iterator;
                return std::make_tuple(
                        entity,
                        m_collection->AtUnsafe<ComponentTypes>(entity)...
                );
            }

        private:
            bool m_isEnd;
            EntitySet m_entities;
            EntityCollection *m_collection;
            EntitySet::iterator m_iterator;
        };

        template<Component ComponentType>
        struct ComponentToEntitySet {
            using type = EntitySet;
        };
    }

    template<Component... ComponentTypes>
    inline EntityComponentView<ComponentTypes...>::EntityComponentView(const EntityCollection *collection) noexcept
            : m_collection(const_cast<EntityCollection *>(collection)),
              m_entities()
    { UpdateEntities(); }

    template<Component... ComponentTypes>
    inline details::EntityComponentViewIterator<ComponentTypes...>
    EntityComponentView<ComponentTypes...>::begin() noexcept
    { return {m_collection, m_entities, true}; }

    template<Component... ComponentTypes>
    inline details::EntityComponentViewIterator<ComponentTypes...>
    EntityComponentView<ComponentTypes...>::end() noexcept
    { return {m_collection, m_entities, false}; }

    template<Component... ComponentTypes>
    void EntityComponentView<ComponentTypes...>::UpdateEntities() noexcept
    {
        m_entities = details::EntitySetIntersection2<
                details::EntitySet,
                typename details::ComponentToEntitySet<ComponentTypes>::type...
        >(
                m_collection->AllSet<ComponentTypes>()...
        );
    }

}

#endif //HEADERTECH_ENTITYCOMPONENTVIEW_INL
