//
// Created by rogan2 on 29/10/2020.
//

#ifndef HEADERTECH_LOGGER_INL
#define HEADERTECH_LOGGER_INL

#include <Logger.h>
#include <ProfilerSink.h>
#include <FileSink.h>
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
#include <spdlog/sinks/dist_sink.h>

#include <ctti/detailed_nameof.hpp>

namespace HeaderTech::Logging {
    namespace detail {
        using SinkArray = std::vector<spdlog::sink_ptr>;

        struct SinkStruct {
            SinkArray sinksA;
            SinkArray sinksB;
        };

        static SinkStruct *activeSinks = nullptr;

        static inline void create_sinks() noexcept
        {
            activeSinks = new SinkStruct{
                    .sinksA = {
#ifdef USE_WIN_COLOR
                            std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>(),
#else
                            std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
#endif
                            std::make_shared<FileSinkMt>("HeaderTechA.log"),
                            std::make_shared<ProfilerSinkMt>(),
                    },
                    .sinksB = {
#ifdef USE_WIN_COLOR
                            std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>(),
#else
                            std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
#endif
                            std::make_shared<FileSinkMt>("HeaderTech.log"),
                    },
            };
        }

        static inline void clear_sinks() noexcept
        {
            delete activeSinks;
            activeSinks = nullptr;
        }

        [[nodiscard]] inline static SinkStruct *get_sinks() noexcept
        {
            return activeSinks;
        }

        [[nodiscard]] inline static SinkArray sinks()
        {
            return get_sinks()->sinksA;
        }

        [[nodiscard]] inline static SinkArray sinks2()
        {
            return get_sinks()->sinksB;
        }
    }

    static inline void create_sinks() noexcept
    {
        detail::create_sinks();
    }

    static inline void clear_sinks() noexcept
    {
        detail::clear_sinks();
    }

    [[nodiscard]] inline Logger make_logger_async(const std::string &name)
    {
        auto sinks = detail::sinks();
        return spdlog::create_async<spdlog::sinks::dist_sink_mt>(name, sinks);
    }

    Logger get_or_make_logger_async(const std::string &name)
    {
        auto logger = spdlog::get(name);
        if (logger == nullptr) {
            return make_logger_async(name);
        }
        return logger;
    }

    template<typename Name>
    [[nodiscard]] inline Logger Logging::get_or_make_logger_async()
    {
        return get_or_make_logger_async(ctti::detailed_nameof<Name>().name().str());
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
            return make_logger(name);
        }
        return logger;
    }

    template<typename Name>
    Logger get_or_make_logger()
    {
        return get_or_make_logger(ctti::detailed_nameof<Name>().name().str());
    }

    template<typename Name>
    [[nodiscard]] inline Logger Logging::make_logger()
    {
        return make_logger(ctti::detailed_nameof<Name>().name().str());
    }
}

#endif //HEADERTECH_LOGGER_INL
