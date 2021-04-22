//
// Created by Blake Rogan on 22/04/2021.
//

#include <Logging/LogFileHelper.hpp>

#include <physfs.h>

struct HeaderTech::Logging::FileType final : public PHYSFS_File {};

HeaderTech_Logging_Export HeaderTech::Logging::LogFileHelper::LogFileHelper() noexcept: m_filename(), m_file(nullptr)
{}

HeaderTech_Logging_Export HeaderTech::Logging::LogFileHelper::~LogFileHelper() noexcept
{ if (m_file != nullptr) { Close(); }}

HeaderTech_Logging_Export void HeaderTech::Logging::LogFileHelper::Open(const std::string &fname, bool truncate) noexcept
{
    Close();
    m_filename = fname;

    for (int tries = 0; tries < m_open_tries; ++tries) {
        PHYSFS_mkdir(spdlog::details::os::dir_name(fname).data());
        if (truncate) {
            if (auto file = PHYSFS_openWrite(fname.data())) {
                PHYSFS_close(file);
            } else {
                continue;
            }
        }
        if ((m_file = (HeaderTech::Logging::FileType *) PHYSFS_openAppend(fname.data()))) {
            return;
        }

        spdlog::details::os::sleep_for_millis(m_open_interval);
    }
}

HeaderTech_Logging_Export void HeaderTech::Logging::LogFileHelper::ReOpen(bool truncate) noexcept
{
    if (m_filename.empty()) {
        spdlog::throw_spdlog_ex("Failed re opening file - was not opened before");
    }
    Open(m_filename, truncate);
}

HeaderTech_Logging_Export void HeaderTech::Logging::LogFileHelper::Flush() noexcept
{ PHYSFS_flush(m_file); }

HeaderTech_Logging_Export void HeaderTech::Logging::LogFileHelper::Close() noexcept
{ PHYSFS_close(m_file); }

HeaderTech_Logging_Export void HeaderTech::Logging::LogFileHelper::Write(const spdlog::memory_buf_t &buf) noexcept
{
    size_t msg_size = buf.size();
    auto   data     = buf.data();
    if (PHYSFS_write(m_file, data, 1, msg_size) != msg_size) {
        spdlog::throw_spdlog_ex("Failed writing to file " + m_filename, errno);
    }
}

HeaderTech_Logging_Export size_t HeaderTech::Logging::LogFileHelper::Size() const noexcept
{
    if (m_file == nullptr) {
        spdlog::throw_spdlog_ex("Cannot use size() on closed file " + m_filename);
    }
    return PHYSFS_fileLength(m_file);
}

HeaderTech_Logging_Export const std::string &HeaderTech::Logging::LogFileHelper::Filename() const noexcept
{ return m_filename; }
