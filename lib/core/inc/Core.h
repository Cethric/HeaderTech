//
// Created by rogan2 on 5/11/2020.
//

#ifndef HEADERTECH_CORE_H
#define HEADERTECH_CORE_H

#include <Engine.h>
#include <Runtime.h>

#include <events/LaunchEvent.h>


#if defined(HEADERTECH_CORE_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <Runtime.inl>
#include <Window.inl>

#endif

#endif //HEADERTECH_CORE_H
