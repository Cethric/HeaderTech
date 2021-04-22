//
// Created by Blake Rogan on 22/04/2021.
//

#ifndef HEADERTECH_ROTATINGSINK_HPP
#define HEADERTECH_ROTATINGSINK_HPP

#include <Logging/LogFileHelper.hpp>

#include <spdlog/sinks/base_sink.h>

namespace HeaderTech::Logging {
    template<typename Mutex>
    class RotatingSink final : public spdlog::sinks::base_sink<Mutex> {
    public:
        inline RotatingSink(
                const HeaderTech::Config::Config &config,
                const HeaderTech::FileSystem::FileSystem &fileSystem
        ) noexcept;

    private:
        inline std::string CalculateFilename(const std::string &filename, std::size_t index) noexcept;

        inline void Rotate() noexcept;

        inline bool RenameFile(const std::string &src, const std::string &target);

    protected:
        inline void sink_it_(const spdlog::details::log_msg &msg) noexcept final;

        inline void flush_() noexcept final;

    protected:
        std::string                        m_base_filename;
        HeaderTech::Logging::LogFileHelper m_file_helper;
        std::size_t                        m_current_size;
        std::size_t                        m_max_size;
        std::size_t                        m_max_files;
    };

    using RotatingSinkMT = RotatingSink<std::mutex>;
    using RotatingSinkST = RotatingSink<spdlog::details::null_mutex>;
}

#endif //HEADERTECH_ROTATINGSINK_HPP
