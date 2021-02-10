//
// Created by rogan2 on 9/02/2021.
//

#ifndef HEADERTECH_SCOPEDLOGGING_INL
#define HEADERTECH_SCOPEDLOGGING_INL

#include <scoped/ScopedLogging.h>

#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include <spdlog/cfg/argv.h>
#include <spdlog/async.h>

#include <Logger.h>
#include <Logger.inl>

namespace HeaderTech::Logging::Scoped {
    ScopedLogging::ScopedLogging(int argc, const char **argv)
    {
        HeaderTech::Logging::create_sinks();
        spdlog::init_thread_pool(8192, 1);
        spdlog::cfg::load_env_levels();
        spdlog::cfg::load_argv_levels(argc, argv);
        spdlog::set_default_logger(make_logger("console"));
        spdlog::info("Created Scoped Logging");
    }

    ScopedLogging::~ScopedLogging()
    {
        spdlog::info("Destroyed Scoped Logging");
        spdlog::shutdown();
        spdlog::drop_all();
        HeaderTech::Logging::clear_sinks();
    }
}

#endif //HEADERTECH_SCOPEDLOGGING_INL
