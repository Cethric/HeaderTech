//
// Created by rogan2 on 13/12/2020.
//

#ifndef HEADERTECH_ECSINCLUDES_H
#define HEADERTECH_ECSINCLUDES_H

#include <Component.h>
#include <Entity.h>
#include <EntityBuilder.h>
#include <EntityCollection.h>
#include <EntityComponentView.h>
#include <EntitySet.h>

#if defined(HEADERTECH_ECS_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <Entity.inl>
#include <EntityBuilder.inl>
#include <EntityCollection.inl>
#include <EntityComponentView.inl>
#include <EntitySet.inl>

#endif

#endif //HEADERTECH_ECSINCLUDES_H
