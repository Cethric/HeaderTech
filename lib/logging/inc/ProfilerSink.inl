//
// Created by rogan2 on 10/11/2020.
//

#ifndef HEADERTECH_PROFILERSINK_INL
#define HEADERTECH_PROFILERSINK_INL

#include <chrono>
#include <thread>

#include <ProfilerSink.h>
#include <scoped/ScopedProfilerIncludes.h>

#include <spdlog/sinks/base_sink-inl.h>

namespace HeaderTech::Logging {
    template<class Mutex>
    ProfilerSink<Mutex>::ProfilerSink()
            : spdlog::sinks::base_sink<Mutex>()
    {}

    template<class Mutex>
    ProfilerSink<Mutex>::ProfilerSink(std::unique_ptr<spdlog::formatter> formatter)
            : spdlog::sinks::base_sink<Mutex>(formatter)
    {}

    template<class Mutex>
    void ProfilerSink<Mutex>::sink_it_(const spdlog::details::log_msg &msg)
    {
        spdlog::memory_buf_t formatted;
        spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
        rmt_LogText(formatted.data());
    }

    template<class Mutex>
    void ProfilerSink<Mutex>::flush_()
    {}
}

#endif //HEADERTECH_PROFILERSINK_INL
