//
// Created by rogan2 on 15/10/2020.
//

#ifndef HEADERTECH_RUNTIME_H
#define HEADERTECH_RUNTIME_H

#include <memory>
#include <Logging.h>
#include <EventDispatcher.h>
#include <events/LaunchEvent.h>
#include <Window.h>
#include <configuration/Configuration.h>

namespace HeaderTech::Core {
    class Runtime : public HeaderTech::Events::EventDispatcher {
    public:
        Runtime(int argc, const char **argv, const Configuration::RuntimeConfig &config);

        ~Runtime();

        int Launch();

        void OnEvent(HeaderTech::Core::Events::LaunchEvent *event)
        { m_log->info("Launch Event Called"); }

    protected:
        void ProcessNextTick();

        void RenderNextFrame(double offset);

    protected:
        bool m_running;
        HeaderTech::Logging::Logger m_log;

        Window m_window;
    };
}

#endif //HEADERTECH_RUNTIME_H
