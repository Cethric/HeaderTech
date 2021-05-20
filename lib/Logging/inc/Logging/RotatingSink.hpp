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

#ifndef HEADERTECH_ROTATINGSINK_HPP
#define HEADERTECH_ROTATINGSINK_HPP

#include <Logging/LogFileHelper.hpp>

#include <spdlog/sinks/base_sink.h>

namespace HeaderTech::Logging {
    template<typename Mutex>
    class RotatingSink final : public spdlog::sinks::base_sink<Mutex> {
    public:
        inline RotatingSink(
                const HeaderTech::Config::ConfigPtr &config,
                const HeaderTech::FileSystem::FileSystemPtr &fileSystem
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
}// namespace HeaderTech::Logging

#endif//HEADERTECH_ROTATINGSINK_HPP
