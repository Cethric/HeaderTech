//
// Created by Blake Rogan on 22/04/2021.
//

#include <Logging/RotatingSink.hpp>
#include <physfs.h>

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
    m_current_size = m_file_helper.Size(); // expensive. called only once
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
    if (index == 0u) {
        return filename;
    }

    std::string basename, ext;
    std::tie(basename, ext) = spdlog::details::file_helper::split_by_extension(filename);
    return fmt::format(SPDLOG_FILENAME_T("{}.{}{}"), basename, index, ext);
}

template<typename Mutex>
inline void HeaderTech::Logging::RotatingSink<Mutex>::Rotate() noexcept
{
    m_file_helper.Close();
    for (auto i = m_max_files; i > 0; --i) {
        std::string src = CalculateFilename(m_base_filename, i - 1);
        if (!PHYSFS_exists(src.data())) {
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
                        errno
                );
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
{ m_file_helper.Flush(); }
