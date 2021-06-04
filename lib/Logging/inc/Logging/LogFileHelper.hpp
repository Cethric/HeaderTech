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

#ifndef HEADERTECH_LOGFILEHELPER_HPP
#define HEADERTECH_LOGFILEHELPER_HPP

#include <Logging/Exports.h>

#include <string>

namespace HeaderTech::Logging {
    struct FileType;

    class HeaderTech_Logging_Export LogFileHelper final {
    public:
        LogFileHelper() noexcept;

        LogFileHelper(const LogFileHelper &other) = delete;

        ~LogFileHelper() noexcept;

        void Open(const std::string &fname, bool truncate = false) noexcept;

        void ReOpen(bool truncate) noexcept;

        void Flush() noexcept;

        void Close() noexcept;

        void Write(const spdlog::memory_buf_t &buf) noexcept;

        [[nodiscard]] size_t Size() const noexcept;

        [[nodiscard]] const std::string &Filename() const noexcept;

    private:
        std::string m_filename;
        FileType *m_file;

        const int m_open_tries    = 5;
        const int m_open_interval = 10;
    };
}// namespace HeaderTech::Logging


#endif//HEADERTECH_LOGFILEHELPER_HPP
