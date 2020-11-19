//
// Created by rogan2 on 5/11/2020.
//

#ifndef HEADERTECH_EVENTS_H
#define HEADERTECH_EVENTS_H

#include <Event.h>
#include <EventDispatcher.h>
#include <EventSubscription.h>

#if defined(HEADERTECH_EVENTS_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <Event.inl>
#include <EventDispatcher.inl>
#include <EventSubscription.inl>

#endif

#endif //HEADERTECH_EVENTS_H
