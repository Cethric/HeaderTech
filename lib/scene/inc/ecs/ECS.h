//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ECS_H
#define HEADERTECH_ECS_H

#include <ecs/Component.h>
#include <ecs/Entity.h>
#include <ecs/EntityBuilder.h>
#include <ecs/EntityCollection.h>
#include <ecs/EntityComponentView.h>
#include <ecs/EntitySet.h>
#include <ecs/System.h>

#if defined(HEADERTECH_SCENE_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <ecs/Entity.inl>
#include <ecs/EntityBuilder.inl>
#include <ecs/EntityCollection.inl>
#include <ecs/EntityComponentView.inl>
#include <ecs/EntitySet.inl>

#endif

#endif //HEADERTECH_ECS_H
