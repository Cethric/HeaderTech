//
// Created by Blake Rogan on 22/04/2021.
//

#ifndef HEADERTECH_LOGFILEHELPER_HPP
#define HEADERTECH_LOGFILEHELPER_HPP

#include <Logging/Exports.h>

#include <string>

namespace HeaderTech::Logging {
    struct FileType;

    class LogFileHelper final {
    public:
        HeaderTech_Logging_Export LogFileHelper() noexcept;

        HeaderTech_Logging_Export ~LogFileHelper() noexcept;

        HeaderTech_Logging_Export void Open(const std::string &fname, bool truncate = false) noexcept;

        HeaderTech_Logging_Export void ReOpen(bool truncate) noexcept;

        HeaderTech_Logging_Export void Flush() noexcept;

        HeaderTech_Logging_Export void Close() noexcept;

        HeaderTech_Logging_Export void Write(const spdlog::memory_buf_t &buf) noexcept;

        [[nodiscard]] HeaderTech_Logging_Export size_t Size() const noexcept;

        [[nodiscard]] HeaderTech_Logging_Export const std::string &Filename() const noexcept;

    private:
        std::string m_filename;
        FileType    *m_file;

        const int m_open_tries    = 5;
        const int m_open_interval = 10;
    };
}


#endif //HEADERTECH_LOGFILEHELPER_HPP
