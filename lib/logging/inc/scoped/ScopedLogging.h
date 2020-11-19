//
// Created by rogan2 on 12/11/2020.
//

#ifndef HEADERTECH_SCOPEDLOGGING_H
#define HEADERTECH_SCOPEDLOGGING_H

#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include <spdlog/cfg/argv.h>
#include <spdlog/async.h>

#include <Logging.h>

namespace HeaderTech::Logging::Scoped {
    class ScopedLogging {
    public:
        inline ScopedLogging(int argc, const char **argv)
        {
            HeaderTech::Logging::create_sinks();
            spdlog::init_thread_pool(8192, 1);
            spdlog::cfg::load_env_levels();
            spdlog::cfg::load_argv_levels(argc, argv);
            spdlog::set_default_logger(make_logger("console"));
            spdlog::info("Created Scoped Logging");
        }

        inline ~ScopedLogging()
        {
            spdlog::info("Destroyed Scoped Logging");
            spdlog::shutdown();
            spdlog::drop_all();
            HeaderTech::Logging::clear_sinks();
        }
    };
}

#endif //HEADERTECH_SCOPEDLOGGING_H
