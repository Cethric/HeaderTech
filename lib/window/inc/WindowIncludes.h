//
// Created by rogan2 on 19/11/2020.
//

#ifndef HEADERTECH_WINDOWINCLUDES_H
#define HEADERTECH_WINDOWINCLUDES_H

#include <Window.h>

#include <api/WindowApiIncludes.h>

#if defined(HEADERTECH_WINDOW_IMPL) && DEFINE_IMPLEMENTATION == 1

#include <Window.inl>

#endif

namespace HeaderTech::Window {
    int WindowVersion();
}

#endif //HEADERTECH_WINDOWINCLUDES_H
