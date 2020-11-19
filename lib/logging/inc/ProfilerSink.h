//
// Created by rogan2 on 10/11/2020.
//

#ifndef HEADERTECH_PROFILERSINK_H
#define HEADERTECH_PROFILERSINK_H

#include <spdlog/sinks/base_sink.h>
#include <mutex>


namespace HeaderTech::Logging {
    template<class Mutex>
    class ProfilerSink final : public spdlog::sinks::base_sink<Mutex> {
    public:
        ProfilerSink();

        explicit ProfilerSink(std::unique_ptr<spdlog::formatter> formatter);

    protected:
        void sink_it_(const spdlog::details::log_msg &msg) final;

        void flush_() final;
    };

    using ProfilerSinkMt = ProfilerSink<std::mutex>;
}

#endif //HEADERTECH_PROFILERSINK_H
