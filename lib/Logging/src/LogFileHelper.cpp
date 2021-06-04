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

#include <Logging/LogFileHelper.hpp>

#include <physfs.h>

#include <string>

struct HeaderTech::Logging::FileType final : public PHYSFS_File {
};

HeaderTech_Logging_Export HeaderTech::Logging::LogFileHelper::LogFileHelper() noexcept : m_filename(), m_file(nullptr)
{}

HeaderTech_Logging_Export HeaderTech::Logging::LogFileHelper::~LogFileHelper() noexcept
{
    if (m_file != nullptr) {
        Close();
    }
}

HeaderTech_Logging_Export void HeaderTech::Logging::LogFileHelper::Open(
    const std::string &fname,
    bool truncate) noexcept
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
{
    PHYSFS_flush(m_file);
}

HeaderTech_Logging_Export void HeaderTech::Logging::LogFileHelper::Close() noexcept
{
    PHYSFS_close(m_file);
}

HeaderTech_Logging_Export void HeaderTech::Logging::LogFileHelper::Write(const spdlog::memory_buf_t &buf) noexcept
{
    size_t msg_size = buf.size();
    auto data       = buf.data();
    if (PHYSFS_writeBytes(m_file, data, msg_size) != msg_size) {
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
{
    return m_filename;
}
