//
// Created by rogan2 on 16/11/2020.
//

#ifndef HEADERTECH_FILESINK_INL
#define HEADERTECH_FILESINK_INL

#include <FileSink.h>

namespace HeaderTech::Logging {
    namespace details {
        FileSinkHelper::FileSinkHelper(const std::string_view &filename) : m_handle(nullptr)
        {
            Open(filename);
        }

        FileSinkHelper::~FileSinkHelper()
        {
            Close();
        }

        void FileSinkHelper::Open(const std::string_view &filename)
        {
            auto file = PHYSFS_openWrite(filename.data());
            if (file) {
                m_handle = file;
            }
        }

        void FileSinkHelper::Write(const spdlog::memory_buf_t &formatted)
        {
            PHYSFS_writeBytes(m_handle, formatted.data(), formatted.size());
        }

        void FileSinkHelper::Flush()
        {
            PHYSFS_flush(m_handle);
        }

        void FileSinkHelper::Close()
        {
            auto handle = m_handle;
            m_handle = nullptr;
            PHYSFS_close(handle);
        }
    }


    template<class Mutex>
    FileSink<Mutex>::FileSink(const std::string_view &filename): helper(filename)
    {

    }

    template<class Mutex>
    void FileSink<Mutex>::sink_it_(const spdlog::details::log_msg &msg)
    {
        spdlog::memory_buf_t formatted;
        spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
        helper.Write(formatted);
    }

    template<class Mutex>
    void FileSink<Mutex>::flush_()
    {
        helper.Flush();
    }

}

#endif //HEADERTECH_FILESINK_INL
