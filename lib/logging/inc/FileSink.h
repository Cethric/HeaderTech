//
// Created by rogan2 on 16/11/2020.
//

#ifndef HEADERTECH_FILESINK_H
#define HEADERTECH_FILESINK_H

#include <spdlog/sinks/base_sink.h>
#include <mutex>
#include <string_view>

#include <physfs.h>

namespace HeaderTech::Logging {
    namespace details {

        class FileSinkHelper {
        public:
            explicit inline FileSinkHelper(const std::string_view &filename);

            inline ~FileSinkHelper();

            inline void Open(const std::string_view &filename);

            inline void Write(const spdlog::memory_buf_t &formatted);

            inline void Flush();

            inline void Close();

        private:
            PHYSFS_File *m_handle;
        };
    }

    template<class Mutex>
    class FileSink final : public spdlog::sinks::base_sink<Mutex> {
    public:
        explicit inline FileSink(const std::string_view &filename);

    protected:
        void sink_it_(const spdlog::details::log_msg &msg) final;

        void flush_() final;

    private:
        details::FileSinkHelper helper;
    };


    using FileSinkMt = FileSink<std::mutex>;
}

#endif //HEADERTECH_FILESINK_H
