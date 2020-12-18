//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ENTITYCOMPONENTVIEW_H
#define HEADERTECH_ENTITYCOMPONENTVIEW_H

#include <ecs/Component.h>
#include <ecs/EntitySet.h>

#include <tuple>
#include <memory>

namespace HeaderTech::Scene::ECS {
    namespace details {
        template<Component... ComponentTypes>
        class EntityComponentViewIterator;
    }

    template<Component...ComponentTypes>
    class EntityComponentView {
    public:
        inline explicit EntityComponentView(const EntityCollection *collection) noexcept;

        inline details::EntityComponentViewIterator<ComponentTypes...> begin() noexcept;

        inline details::EntityComponentViewIterator<ComponentTypes...> end() noexcept;

    protected:
        inline void UpdateEntities() noexcept;

    private:
        details::EntitySet m_entities;
        EntityCollection *m_collection;
    };

    template<Component...ComponentTypes>
    using EntityComponentViewPtr = std::shared_ptr<EntityComponentView<ComponentTypes...>>;
}

#endif //HEADERTECH_ENTITYCOMPONENTVIEW_H
