//
// Created by Blake Rogan on 22/04/2021.
//

#include "Logging/Logging.hpp"

#include <spdlog/cfg/env.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/file_helper.h>

#ifndef __EMSCRIPTEN__

#include <spdlog/async.h>

#endif // !defined(EMSCRIPTEN)

#include <Logging/RotatingSink.inl>


static inline std::shared_ptr<spdlog::sinks::dup_filter_sink_mt> CreateSinks(
        const HeaderTech::Config::ConfigPtr &config,
        const HeaderTech::FileSystem::FileSystemPtr &fileSystem
)
{
    auto dup_sink = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(5));
    dup_sink->add_sink(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    dup_sink->add_sink(std::make_shared<HeaderTech::Logging::RotatingSinkMT>(config, fileSystem));

    return dup_sink;
}

HeaderTech_Logging_Export HeaderTech::Logging::Logging::Logging(
        const HeaderTech::Config::ConfigPtr &config,
        const HeaderTech::FileSystem::FileSystemPtr &fileSystem
) noexcept: std::enable_shared_from_this<Logging>(),
            m_sink(CreateSinks(config, fileSystem))
{
    spdlog::cfg::load_env_levels();
#ifndef __EMSCRIPTEN__
    spdlog::init_thread_pool(8192, 16);
#endif // __EMSCRIPTEN__
    spdlog::set_default_logger(CreateLogger("console"));
    spdlog::info("Logging Initialised");
}

HeaderTech_Logging_Export HeaderTech::Logging::Logging::~Logging() noexcept
{ spdlog::shutdown(); }

HeaderTech_Logging_Export HeaderTech::Logging::Logger HeaderTech::Logging::Logging::CreateLogger(
        const std::string_view &name
) noexcept
{
#ifdef __EMSCRIPTEN__
    auto logger = std::make_shared<spdlog::logger>(std::string(name.data()), m_sink);
#else
    auto pool   = spdlog::thread_pool();
    auto logger = std::make_shared<spdlog::async_logger>(
            std::string(name.data()),
            m_sink,
            std::move(pool),
            spdlog::async_overflow_policy::block
    );
#endif // __EMSCRIPTEN__
    spdlog::initialize_logger(logger);
    return logger;
}

HeaderTech_Logging_Export HeaderTech::Logging::Logger HeaderTech::Logging::Logging::GetOrCreateLogger(
        const std::string_view &name
) noexcept
{
    if (auto logger = spdlog::get(name.data())) {
        return logger;
    }
    return CreateLogger(name);
}
