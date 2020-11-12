#include <iostream>

#define DEFINE_IMPLEMENTATION 1

#include <Logging.h>
#include <Profiler.h>
#include <Events.h>
#include <Core.h>

using Runtime = HeaderTech::Core::Runtime;

int main(int argc, const char **argv)
{
    int returnCode = 0;
    HeaderTech::Logging::init_logger();
    {
        auto &profiler = HeaderTech::Profiler::ProfilerManager::Get();
        {
            Runtime runtime(argc, argv, {
                    .window = {
                            .width = 800,
                            .height = 600,
                            .title = "Sandbox"
                    }
            });
            returnCode = runtime.Launch();
        }
    }
    return returnCode;
}
