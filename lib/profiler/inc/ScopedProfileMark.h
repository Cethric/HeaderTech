//
// Created by rogan2 on 11/11/2020.
//

#ifndef HEADERTECH_SCOPEDPROFILEMARK_H
#define HEADERTECH_SCOPEDPROFILEMARK_H

#include <ProfilerManager.h>
#include <GLFW/glfw3.h>
#include <string>
#include <utility>

namespace HeaderTech::Profiler {
    class ScopedProfileMark final {
    public:
        inline explicit ScopedProfileMark(std::string name) : m_name(std::move(name)), m_start(glfwGetTime())
        {}

        inline ~ScopedProfileMark()
        {
            Stop();
        }

        inline void Stop()
        {
            ProfilerManager::Get().ProfileMark(m_name, glfwGetTime() - m_start);
        }

    private:
        std::string m_name;
        double m_start;
    };
}

#endif //HEADERTECH_SCOPEDPROFILEMARK_H
