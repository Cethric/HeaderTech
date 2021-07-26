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

#ifndef HEADERTECH_LOGGINGCONCEPTS_HPP
#define HEADERTECH_LOGGINGCONCEPTS_HPP

#include <Logging/Exports.h>

#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

#include <concepts>
#include <type_traits>
#include <string>
#include <string_view>
#include <chrono>
#include <version>


#if __has_include(<source_location>) && defined(__cpp_lib_source_location)
#include <source_location>
#elif __has_include(<experimental/source_location>) && defined(__cpp_lib_source_location)
#include <experimental/source_location>
#endif

namespace HeaderTech::Logging {
#if __has_include(<source_location>) && defined(__cpp_lib_source_location)
    using SourceLocation = std::source_location;
#define SOURCE_LOCATION HeaderTech::Logging::SourceLocation::current()
#elif __has_include(<experimental/source_location>) && defined(__cpp_lib_source_location)
    using SourceLocation = std::experimental::source_location;
#define SOURCE_LOCATION HeaderTech::Logging::SourceLocation::current()
#else

    class HeaderTech_Logging_Export SourceLocation final {
    public:
        inline SourceLocation(const char *file, const char *func, std::uint_least32_t line) noexcept:
                m_file(file),
                m_function(func),
                m_line(line)
        {}

        inline const char *file_name() const
        { return m_file; }

        inline const char *function_name() const
        { return m_function; }

        inline std::uint_least32_t line() const
        { return m_line; }

    private:
        const char          *m_file;
        const char          *m_function;
        std::uint_least32_t m_line;
    };

#if defined(_MSC_VER)
#define HEADERTECH_FUNCTION_NAME __FUNCSIG__
#elif defined(__clang_major__) || defined(__GNUC__)
#define HEADERTECH_FUNCTION_NAME __PRETTY_FUNCTION__
#else
#define HEADERTECH_FUNCTION_NAME __FUNCTION__
#endif
#define HEADERTECH_FILE_NAME __FILE__
#define HEADERTECH_LINE_NUMBER __LINE__
#define SOURCE_LOCATION HeaderTech::Logging::SourceLocation(HEADERTECH_FILE_NAME, HEADERTECH_FUNCTION_NAME, std::uint_least32_t{HEADERTECH_LINE_NUMBER})
#endif


    enum LogLevel : std::int_least16_t {
        LogLevelOff,
        LogLevelCritical,
        LogLevelException,
        LogLevelError,
        LogLevelWarning,
        LogLevelInformation,
        LogLevelDebug,
        LogLevelTrace,
        LogLevelVerbose,
    };

    template<typename StrType>
    concept LogStringContainerType = std::is_base_of_v<std::string_view, std::remove_cvref_t<std::decay_t<StrType>>> ||
                                     std::is_base_of_v<std::string, std::remove_cvref_t<std::decay_t<StrType>>> ||
                                     std::is_base_of_v<std::wstring_view, std::remove_cvref_t<std::decay_t<StrType>>> ||
                                     std::is_base_of_v<std::wstring, std::remove_cvref_t<std::decay_t<StrType>>>;

    template<typename StrType>
    concept LogStringCharType =
    std::is_same_v<
            char,
            std::remove_cvref_t<
                    std::remove_pointer_t<
                            std::decay_t<
                                    StrType
                            >
                    >
            >
    > ||
    std::is_same_v<
            wchar_t,
            std::remove_cvref_t<
                    std::remove_pointer_t<
                            std::decay_t<
                                    StrType
                            >
                    >
            >
    >;

    template<typename StrType>
    concept LogStringType = LogStringContainerType<StrType> || LogStringCharType<StrType>;

    template<typename ArgType>
    concept LogStringArgType = not std::is_base_of_v<std::exception, ArgType>;

    template<typename StringArgType>
    concept LogStringOrArgType = LogStringArgType<StringArgType> || LogStringType<StringArgType>;

    using LoggingClock = std::chrono::system_clock;
    using LoggingTimePoint = LoggingClock::time_point;

    struct LogDetails {
        LogLevel         level;
        SourceLocation   sourceLocation;
        LoggingTimePoint eventTime;
    };
}


template<>
struct fmt::formatter<HeaderTech::Logging::LogLevel> {
    constexpr auto parse(fmt::format_parse_context &ctx) -> decltype(ctx.begin())
    {
        auto it  = ctx.begin();
        auto end = ctx.end();
        if (it != end && (*it == 'p' || *it == 'c')) {
            presentation = *it++;
        }
        if (it != end && *it != '}') {
            throw fmt::format_error("invalid format");
        }
        return it;
    }

    template<typename FormatContext>
    auto format(const HeaderTech::Logging::LogLevel &lvl, FormatContext &ctx) -> decltype(ctx.out())
    {
        switch (lvl) {
            case HeaderTech::Logging::LogLevelCritical:
                return fmt::format_to(
                        ctx.out(),
                        presentation == 'p' ?
                        fmt::text_style() :
                        fmt::emphasis::bold | fmt::fg(fmt::color::orange_red),
                        "Critical"
                );
            case HeaderTech::Logging::LogLevelException:
                return fmt::format_to(
                        ctx.out(),
                        presentation == 'p' ?
                        fmt::text_style() :
                        fmt::emphasis::bold | fmt::fg(fmt::color::indian_red),
                        "Exception"
                );
            case HeaderTech::Logging::LogLevelError:
                return fmt::format_to(
                        ctx.out(),
                        presentation == 'p' ?
                        fmt::text_style() :
                        fmt::emphasis::bold | fmt::fg(fmt::color::red),
                        "Error"
                );
            case HeaderTech::Logging::LogLevelWarning:
                return fmt::format_to(
                        ctx.out(),
                        presentation == 'p' ?
                        fmt::text_style() :
                        fmt::emphasis::bold | fmt::fg(fmt::color::yellow),
                        "Warning"
                );
            case HeaderTech::Logging::LogLevelInformation:
                return fmt::format_to(
                        ctx.out(),
                        presentation == 'p' ?
                        fmt::text_style() :
                        fmt::emphasis::bold | fmt::fg(fmt::color::light_blue),
                        "Information"
                );
            case HeaderTech::Logging::LogLevelDebug:
                return fmt::format_to(
                        ctx.out(),
                        presentation == 'p' ?
                        fmt::text_style() :
                        fmt::emphasis::bold | fmt::fg(fmt::color::old_lace),
                        "Debug"
                );
            case HeaderTech::Logging::LogLevelTrace:
                return fmt::format_to(
                        ctx.out(),
                        "Trace"
                );
            case HeaderTech::Logging::LogLevelVerbose:
                return fmt::format_to(
                        ctx.out(),
                        presentation == 'p' ?
                        fmt::text_style() :
                        fmt::emphasis::bold | fmt::fg(fmt::color::green_yellow),
                        "Verbose"
                );
            default:
                return ctx.out();
        }
    }

private:
    char presentation = 'p';
};

template<>
struct fmt::formatter<HeaderTech::Logging::SourceLocation> {
    constexpr auto parse(fmt::format_parse_context &ctx) -> decltype(ctx.begin())
    {
        auto it  = ctx.begin();
        auto end = ctx.end();
        if (it != end && (*it == 'c' || *it == 'd')) {
            presentation = *it++;
        }
        if (it != end && *it != '}') {
            throw fmt::format_error("invalid format");
        }
        return it;
    }

    template<typename FormatContext>
    auto format(const HeaderTech::Logging::SourceLocation &sl, FormatContext &ctx) -> decltype(ctx.out())
    {
        std::string_view function = sl.function_name();
        auto             fend     = function.find_first_of('(');
        auto             reduced  = function.substr(0U, fend);
        auto             fstart   = reduced.find_last_of("::") == std::string_view::npos ?
                                    0U :
                                    reduced.find_last_of("::", 0U, reduced.find_last_of("::")) + 1U;
        return fmt::format_to(
                ctx.out(),
                "{}:{}:{}",
                sl.file_name(),
                reduced.substr(fstart),
                sl.line()
        );
    }

private:
    char presentation = 'd';
};

template<>
struct fmt::formatter<HeaderTech::Logging::LoggingTimePoint> {
    constexpr auto parse(fmt::format_parse_context &ctx) -> decltype(ctx.begin())
    {
        auto it  = ctx.begin();
        auto end = ctx.end();
        if (it != end && (*it == 's' || *it == 'm')) {
            presentation = *it++;
        }
        if (it != end && *it != '}') {
            throw fmt::format_error("invalid format");
        }
        return it;
    }

    template<typename FormatContext>
    auto format(const HeaderTech::Logging::LoggingTimePoint &tp, FormatContext &ctx) -> decltype(ctx.out())
    {
        auto t    = HeaderTech::Logging::LoggingClock::to_time_t(tp);
        auto next = fmt::format_to(ctx.out(), "{:%Y-%m-%d %H:%M:%S}", fmt::localtime(t));

        if (presentation == 'm') {
            auto seconds      = std::chrono::time_point_cast<std::chrono::seconds>(tp);
            auto fraction     = tp - seconds;
            auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(fraction);
            return fmt::format_to(next, ".{:03d}", microseconds.count());
        }
        return next;
    }

private:
    char presentation = 'd';
};

#endif //HEADERTECH_LOGGINGCONCEPTS_HPP
