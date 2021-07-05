/*==============================================================================
 = BSD 3-Clause License
 =
 = Copyright (c) 2021, Cethric
 = All rights reserved.
 =
 = Redistribution and use in source and binary forms, with or without
 = modification, are permitted provided that the following conditions are met:
 =
 = 1. Redistributions of source code must retain the above copyright notice, this
 =    list of conditions and the following disclaimer.
 =
 = 2. Redistributions in binary form must reproduce the above copyright notice,
 =    this list of conditions and the following disclaimer in the documentation
 =    and/or other materials provided with the distribution.
 =
 = 3. Neither the name of the copyright holder nor the names of its
 =    contributors may be used to endorse or promote products derived from
 =    this software without specific prior written permission.
 =
 = THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 = AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 = IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 = DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 = FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 = DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 = SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 = CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 = OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 = OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 =============================================================================*/

#ifndef HEADERTECH_LOGGING_HPP
#define HEADERTECH_LOGGING_HPP

#include <Logging/Exports.h>
#include <Logging/LoggingConcepts.hpp>

#include <Config/Config.hpp>
#include <FileSystem/FileSystem.hpp>

#include <ctti/detailed_nameof.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <memory>
#include <iostream>


namespace HeaderTech::Logging {
    class Sink {
    public:
        explicit inline Sink(LogLevel maxLevel) : m_maxLevel(maxLevel)
        {}

        inline auto LogIt(const LogDetails &details, const std::string &msg) noexcept -> void
        {
            if (details.level <= m_maxLevel) {
                SinkIt(details, msg);
            }
        }

    protected:
        virtual void SinkIt(const LogDetails &details, const std::string &msg) noexcept = 0;

    private:
        LogLevel m_maxLevel;
    };

    class StdoutSink : public Sink {
    public:
        StdoutSink() : Sink(LogLevelVerbose)
        {}

    protected:
        void SinkIt(const LogDetails &details, const std::string &msg) noexcept override
        {
            fmt::print(std::cout, "{:m} - {:d} [{:c}]: {}\n", details.eventTime, details.sourceLocation, details.level, msg);
        }
    };

    class StderrSink : public Sink {};

    class FileSink : public Sink {};

    using SinkPtr = std::shared_ptr<Sink>;

    class Logger final : private std::enable_shared_from_this<Logger> {
    public:
        Logger(const std::string_view &name, const std::vector<SinkPtr> &sinks) :
                m_name(name),
                m_sinks(sinks),
                m_enabled(true)
        {}

        ~Logger() = default;

        void Flush()
        {}

        template<LogStringType MsgType, LogStringArgType...Args>
        inline void Log(
                const LogDetails &details,
                const MsgType &msg,
                Args &&... args
        ) noexcept
        {
            LogIt(
                    details,
                    std::forward<decltype(msg)>(msg),
                    std::forward<decltype(args)>(args)...
            );
        }

        auto AsShared() -> std::shared_ptr<Logger>
        { return this->shared_from_this(); }

#define DEFINE_LOG_MESSAGE(Level)\
        template<LogStringType MsgType, LogStringArgType...Args>\
        inline void Level(\
                const SourceLocation &sourceLoc,\
                const MsgType &msg,\
                Args &&... args\
        ) noexcept\
        {\
            return Log(\
                    {.level = LogLevel##Level, .sourceLocation = sourceLoc, .eventTime = LoggingClock::now()},\
                    std::forward<decltype(msg)>(msg),\
                    std::forward<decltype(args)>(args)...\
            );\
        }

        DEFINE_LOG_MESSAGE(Critical)

        DEFINE_LOG_MESSAGE(Exception)

        DEFINE_LOG_MESSAGE(Error)

        DEFINE_LOG_MESSAGE(Warning)

        DEFINE_LOG_MESSAGE(Information)

        DEFINE_LOG_MESSAGE(Debug)

        DEFINE_LOG_MESSAGE(Trace)

        DEFINE_LOG_MESSAGE(Verbose)

#undef DEFINE_LOG_MESSAGE

    protected:
        template<LogStringContainerType StringType, LogStringArgType...Args>
        constexpr inline auto MessageToChar(
                const StringType &msg,
                Args &&... /*args*/
        ) -> decltype(fmt::runtime(msg.c_str()))
        { return fmt::runtime(msg.c_str()); }

        template<LogStringCharType StringType, LogStringArgType...Args>
        constexpr inline auto MessageToChar(const StringType &msg, Args &&... /*args*/) -> decltype(fmt::runtime(msg))
        { return fmt::runtime(msg); }

        template<LogStringOrArgType...StringOrArgType>
        constexpr inline auto MessageToChar(
                const fmt::format_string<StringOrArgType...> &msg,
                StringOrArgType &&... /*args*/
        ) -> decltype(msg)
        { return msg; }

        template<typename Buffer, LogStringType MsgType, LogStringArgType...Args>
        inline auto FormatIt(
                const Buffer &buffer,
                const MsgType &msg,
                Args &&... args
        ) -> decltype(fmt::format_to(
                buffer,
                MessageToChar(std::forward<decltype(msg)>(msg), std::forward<decltype(args)>(args)...),
                std::forward<decltype(args)>(args)...
        ))
        {
            return fmt::format_to(
                    buffer,
                    MessageToChar(std::forward<decltype(msg)>(msg), std::forward<decltype(args)>(args)...),
                    std::forward<decltype(args)>(args)...
            );
        }

        template<LogStringType MsgType, LogStringArgType...Args>
        void LogIt(
                const LogDetails &details,
                const MsgType &msg,
                Args &&... args
        ) noexcept
        {
            if (m_enabled) {
                std::string buffer;
                FormatIt(
                        std::back_inserter(buffer),
                        std::forward<decltype(msg)>(msg),
                        std::forward<decltype(args)>(args)...
                );
                for (auto &sink : m_sinks) {
                    sink->LogIt(details, buffer);
                }
            }
        }

    private:
        std::string          m_name;
        std::vector<SinkPtr> m_sinks;
        bool                 m_enabled;
    };

    using LogPtr = std::shared_ptr<Logger>;

    class LogRegistry final {
    public:
        LogRegistry() : m_defaultSinks({std::make_shared<StdoutSink>()}), m_defaultFormat("{}")
        {}

        auto GetLogger(const std::string_view &name) -> LogPtr
        { return std::make_shared<Logger>(name, m_defaultSinks); }

    private:
        std::vector<SinkPtr> m_defaultSinks;
        std::string          m_defaultFormat;
    };

    class Logging final : private std::enable_shared_from_this<Logging> {
    public:
        Logging(
                const HeaderTech::Config::ConfigPtr &config,
                const HeaderTech::FileSystem::FileSystemPtr &fileSystem
        ) :
                m_registry(),
                m_config(config),
                m_fileSystem(fileSystem)
        {}

        template<typename LogClassName>
        auto GetLogger() -> LogPtr
        {
            constexpr auto details = ctti::detailed_nameof<LogClassName>();
            constexpr auto name    = details.full_homogeneous_name();
            return m_registry.GetLogger({name.begin(), name.end()});
        }

        auto GetLogger(const std::string_view &name) -> LogPtr
        { return m_registry.GetLogger(name); }

    private:
        LogRegistry                           m_registry;
        HeaderTech::Config::ConfigPtr         m_config;
        HeaderTech::FileSystem::FileSystemPtr m_fileSystem;
    };

    using LoggingPtr = std::shared_ptr<Logging>;

    inline static LoggingPtr MakeLogging(
            const HeaderTech::Config::ConfigPtr &config,
            const HeaderTech::FileSystem::FileSystemPtr &fileSystem
    ) noexcept
    { return std::make_shared<Logging>(config, fileSystem); }
}// namespace HeaderTech::Logging


#endif//HEADERTECH_LOGGING_HPP
