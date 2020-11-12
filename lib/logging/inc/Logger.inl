//
// Created by rogan2 on 29/10/2020.
//

#ifndef HEADERTECH_LOGGER_INL
#define HEADERTECH_LOGGER_INL

#include <Logger.h>
#include <ProfilerSink.h>
#include <vector>

#ifdef WIN32
#define USE_WIN_COLOR 1
#endif

#include <spdlog/async.h>

#ifdef USE_WIN_COLOR

#include <spdlog/sinks/wincolor_sink.h>

#else
#include <spdlog/sinks/stdout_color_sinks.h>
#endif

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/cfg/env.h>
#include <spdlog/sinks/dist_sink.h>

#include <ctti/detailed_nameof.hpp>

namespace HeaderTech::Logging {
    namespace detail {
        using SinkArray = std::vector<spdlog::sink_ptr>;

        [[nodiscard]] inline static SinkArray sinks()
        {
            static SinkArray result{
#ifdef USE_WIN_COLOR
                    std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>(),
#else
                    std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
#endif
                    std::make_shared<spdlog::sinks::basic_file_sink_mt>("HeaderTechA.log", true),
                    std::make_shared<ProfilerSinkMt>(),
            };
            return result;
        }

        [[nodiscard]] inline static SinkArray sinks2()
        {
            static SinkArray result{
#ifdef USE_WIN_COLOR
                    std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>(),
#else
                    std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
#endif
                    std::make_shared<spdlog::sinks::basic_file_sink_mt>("HeaderTech.log", true),
            };
            return result;
        }
    }

    void init_logger()
    {
        spdlog::init_thread_pool(8192, 1);
        spdlog::cfg::load_env_levels();
        spdlog::set_default_logger(make_logger_async("console"));
    }

    [[nodiscard]] inline Logger make_logger_async(const std::string &name)
    {
        auto sinks = detail::sinks();
        return spdlog::create_async<spdlog::sinks::dist_sink_mt>(name, sinks);
    }

    template<typename Name>
    [[nodiscard]] inline Logger Logging::make_logger_async()
    {
        return make_logger_async(ctti::detailed_nameof<Name>().name().str());
    }

    [[nodiscard]] inline Logger make_logger(const std::string &name)
    {
        auto sinks = detail::sinks2();
        return spdlog::create<spdlog::sinks::dist_sink_mt>(name, sinks);
    }

    Logger get_or_make_logger(const std::string &name)
    {
        auto logger = spdlog::get(name);
        if (logger == nullptr) {
            auto sinks = detail::sinks2();
            return spdlog::create<spdlog::sinks::dist_sink_mt>(name, sinks);
        }
        return logger;
    }

    template<typename Name>
    [[nodiscard]] inline Logger Logging::make_logger()
    {
        return make_logger(ctti::detailed_nameof<Name>().name().str());
    }
}

#endif //HEADERTECH_LOGGER_INL
