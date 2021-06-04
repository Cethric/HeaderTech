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

#ifndef HEADERTECH_LOGGING_HPP
#define HEADERTECH_LOGGING_HPP

#include <Logging/Exports.h>

#include <Config/Config.hpp>
#include <FileSystem/FileSystem.hpp>

#include <ctti/detailed_nameof.hpp>
#include <spdlog/sinks/dup_filter_sink.h>
#include <spdlog/spdlog.h>

#include <memory>

namespace HeaderTech::Logging {
using Logger = std::shared_ptr<spdlog::logger>;

class HeaderTech_Logging_Export Logging final : public std::enable_shared_from_this<Logging> {
public:
    explicit Logging(
        const HeaderTech::Config::ConfigPtr &config,
        const HeaderTech::FileSystem::FileSystemPtr &fileSystem) noexcept;

    ~Logging() noexcept;

    template<typename Target>
    [[nodiscard]] inline Logger CreateLogger() noexcept
    {
        constexpr auto details = ctti::detailed_nameof<Target>();
        return CreateLogger({ details.name().begin(), details.name().end() });
    }

    template<typename Target>
    [[nodiscard]] inline Logger GetOrCreateLogger() noexcept
    {
        constexpr auto details = ctti::detailed_nameof<Target>();
        return GetOrCreateLogger({ details.name().begin(), details.name().end() });
    }

    Logger CreateLogger(const std::string_view &name) noexcept;

    Logger GetOrCreateLogger(const std::string_view &name) noexcept;

private:
    std::shared_ptr<spdlog::sinks::dup_filter_sink_mt> m_sink;
};

using LoggingPtr     = std::shared_ptr<Logging>;
using LoggingWeakPtr = std::weak_ptr<Logging>;
}// namespace HeaderTech::Logging


#endif//HEADERTECH_LOGGING_HPP
