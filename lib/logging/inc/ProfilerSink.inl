//
// Created by rogan2 on 10/11/2020.
//

#ifndef HEADERTECH_PROFILERSINK_INL
#define HEADERTECH_PROFILERSINK_INL

#include <chrono>
#include <ProfilerSink.h>
#include <scoped/ScopedProfiler.h>
#include <spdlog/sinks/base_sink-inl.h>
#include <thread>

namespace HeaderTech::Logging {
    template<class Mutex>
    ProfilerSink<Mutex>::ProfilerSink()
            : spdlog::sinks::base_sink<Mutex>()
    {

    }

    template<class Mutex>
    ProfilerSink<Mutex>::ProfilerSink(std::unique_ptr<spdlog::formatter> formatter)
            : spdlog::sinks::base_sink<Mutex>(formatter)
    {

    }

    template<class Mutex>
    void ProfilerSink<Mutex>::sink_it_(const spdlog::details::log_msg &msg)
    {
        using MilliSecondDuration = std::chrono::duration<std::uint64_t, std::milli>;

        HeaderTech::Profiler::Scoped::ScopedProfiler::GetProfiler()->LogMessage(
                {
                        .name = {msg.logger_name.begin(), msg.logger_name.end()},
                        .data = {msg.payload.begin(), msg.payload.end()},
                        .time = std::chrono::duration_cast<MilliSecondDuration>(msg.time.time_since_epoch()).count(),
                        .thread = msg.thread_id,
                        .level = static_cast<std::uint16_t>(msg.level)
                }
        );
    }

    template<class Mutex>
    void ProfilerSink<Mutex>::flush_()
    {

    }
}

#endif //HEADERTECH_PROFILERSINK_INL
