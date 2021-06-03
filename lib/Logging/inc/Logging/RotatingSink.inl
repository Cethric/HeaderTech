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

#include <physfs.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <spdlog/spdlog-inl.h>
#include <spdlog/sinks/base_sink-inl.h>
#include <spdlog/sinks/rotating_file_sink-inl.h>

#include <string>

template<typename Mutex>
inline HeaderTech::Logging::RotatingSink<Mutex>::RotatingSink(
        const Config::ConfigPtr &config,
        const FileSystem::FileSystemPtr &fileSystem
) noexcept
        : m_base_filename(config->LogConfig().logName),
          m_file_helper(),
          m_current_size(0),
          m_max_size(config->LogConfig().maxLogSize),
          m_max_files(config->LogConfig().maxLogFiles)
{
    m_file_helper.Open(CalculateFilename(m_base_filename, 0));
    m_current_size = m_file_helper.Size();// expensive. called only once
    if (m_current_size > 0) {
        Rotate();
    }
}

template<typename Mutex>
inline std::string HeaderTech::Logging::RotatingSink<Mutex>::CalculateFilename(
        const std::string &filename,
        std::size_t index
) noexcept
{
    if (index == 0U) {
        return filename;
    }

    std::string basename;
    std::string ext;
    std::tie(basename, ext) = spdlog::details::file_helper::split_by_extension(filename);
    return fmt::format(SPDLOG_FILENAME_T("{}.{}{}"), basename, index, ext);
}

template<typename Mutex>
inline void HeaderTech::Logging::RotatingSink<Mutex>::Rotate() noexcept
{
    m_file_helper.Close();
    for (auto i = m_max_files; i > 0; --i) {
        std::string src = CalculateFilename(m_base_filename, i - 1);
        if (PHYSFS_exists(src.data()) == 0) {
            continue;
        }
        std::string target = CalculateFilename(m_base_filename, i);

        if (!RenameFile(src, target)) {
            spdlog::details::os::sleep_for_millis(100);
            if (!RenameFile(src, target)) {
                m_file_helper.ReOpen(true);
                m_current_size = 0;
                spdlog::throw_spdlog_ex(
                        fmt::format("rotating_file_sink: failed renaming {} to {}", src, target),
                        errno);
            }
        }
    }
    m_file_helper.ReOpen(true);
}

template<typename Mutex>
inline bool HeaderTech::Logging::RotatingSink<Mutex>::RenameFile(const std::string &src, const std::string &target)
{
    PHYSFS_delete(target.data());
    return spdlog::details::os::rename(PHYSFS_getWriteDir() + src, PHYSFS_getWriteDir() + target) == 0;
}

template<typename Mutex>
inline void HeaderTech::Logging::RotatingSink<Mutex>::sink_it_(const spdlog::details::log_msg &msg) noexcept
{
    spdlog::memory_buf_t formatted;
    spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
    m_current_size += formatted.size();
    if (m_current_size > m_max_size) {
        Rotate();
        m_current_size = formatted.size();
    }
    m_file_helper.Write(formatted);
}

template<typename Mutex>
inline void HeaderTech::Logging::RotatingSink<Mutex>::flush_() noexcept
{
    m_file_helper.Flush();
}
