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

#ifndef HEADERTECH_CONFIG_HPP
#define HEADERTECH_CONFIG_HPP

#include <Config/Exports.h>

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace HeaderTech::Config {
    struct LoggingConfig {
        std::string logName;
        std::size_t maxLogFiles;
        std::size_t maxLogSize;
    };

    class Config : public std::enable_shared_from_this<Config> {
    public:
        HeaderTech_Config_Export Config(
                const std::string_view &name,
                const std::string_view &version,
                int argc,
                const char **argv
        ) noexcept;

        [[nodiscard]] HeaderTech_Config_Export const std::vector<std::string> &SearchPaths() const noexcept;

        [[nodiscard]] HeaderTech_Config_Export const LoggingConfig &LogConfig() const noexcept;

    private:
        std::vector<std::string> m_searchPaths;
        LoggingConfig            m_logConfig;
    };

    using ConfigPtr = std::shared_ptr<Config>;
    using ConfigWeakPtr = std::weak_ptr<Config>;
}// namespace HeaderTech::Config


#endif//HEADERTECH_CONFIG_HPP
