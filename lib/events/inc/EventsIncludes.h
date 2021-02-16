//
// Created by rogan2 on 5/11/2020.
//

#ifndef HEADERTECH_EVENTSINCLUDES_H
#define HEADERTECH_EVENTSINCLUDES_H

#include <Event.h>
#include <EventDispatcher.h>
#include <EventSubscription.h>

#if defined(HEADERTECH_EVENTS_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <Event.inl>
#include <EventDispatcher.inl>
#include <EventSubscription.inl>

#endif

namespace HeaderTech::Events {
    int EventsVersion();
}

#endif //HEADERTECH_EVENTSINCLUDES_H
