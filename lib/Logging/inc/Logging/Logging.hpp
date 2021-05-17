//
// Created by Blake Rogan on 22/04/2021.
//

#ifndef HEADERTECH_LOGGING_HPP
#define HEADERTECH_LOGGING_HPP

#include <Logging/Exports.h>

#include <Config/Config.hpp>
#include <FileSystem/FileSystem.hpp>

#include <ctti/detailed_nameof.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/dup_filter_sink.h>

#include <memory>

namespace HeaderTech::Logging {
    using Logger = std::shared_ptr<spdlog::logger>;

    class Logging : public std::enable_shared_from_this<Logging> {
    public:
        HeaderTech_Logging_Export explicit Logging(
                const HeaderTech::Config::ConfigPtr &config,
                const HeaderTech::FileSystem::FileSystemPtr &fileSystem
        ) noexcept;

        HeaderTech_Logging_Export ~Logging() noexcept;

        template<typename Target>
        Logger CreateLogger() noexcept
        {
            constexpr auto details = ctti::detailed_nameof<Target>();
            return CreateLogger({details.name().begin(), details.name().end()});
        }

        template<typename Target>
        Logger GetOrCreateLogger() noexcept
        {
            constexpr auto details = ctti::detailed_nameof<Target>();
            return GetOrCreateLogger({details.name().begin(), details.name().end()});
        }

        HeaderTech_Logging_Export Logger CreateLogger(const std::string_view &name) noexcept;

        HeaderTech_Logging_Export Logger GetOrCreateLogger(const std::string_view &name) noexcept;

    private:
        std::shared_ptr<spdlog::sinks::dup_filter_sink_mt> m_sink;
    };

    using LoggingPtr = std::shared_ptr<Logging>;
    using LoggingWeakPtr = std::weak_ptr<Logging>;
}


#endif //HEADERTECH_LOGGING_HPP
