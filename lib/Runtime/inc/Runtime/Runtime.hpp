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

#ifndef HEADERTECH_RUNTIME_HPP
#define HEADERTECH_RUNTIME_HPP

#include <memory>
#include <span>
#include <string_view>

#include <Logging/Logging.hpp>
#include <FileSystem/FileSystem.hpp>
#include <Config/Config.hpp>
#include <Event/EventProcessor.hpp>
#include <Common/Clock.hpp>
#include <Runtime/Exports.h>


namespace HeaderTech::Runtime {
    class RuntimeContext {
    public:
        [[nodiscard]] inline const std::string_view &Name() const noexcept
        { return m_name; }

        [[nodiscard]] inline const std::string_view &Version() const noexcept
        { return m_version; }

        [[nodiscard]] inline const std::span<const char *> &Args() const noexcept
        { return m_args; }

        [[nodiscard]] inline const HeaderTech::Common::ClockPtr &Clock() const noexcept
        { return m_clock; }

        [[nodiscard]] inline const HeaderTech::Config::ConfigPtr &Config() const noexcept
        { return m_config; }

        [[nodiscard]] inline const HeaderTech::FileSystem::FileSystemPtr &FileSystem() const noexcept
        { return m_fileSystem; }

        [[nodiscard]] inline const HeaderTech::Logging::LoggingPtr &Logging() const noexcept
        { return m_logging; }

    private:
        std::string_view                      m_name;
        std::string_view                      m_version;
        std::span<const char *>               m_args;
        HeaderTech::Common::ClockPtr          m_clock;
        HeaderTech::Config::ConfigPtr         m_config;
        HeaderTech::FileSystem::FileSystemPtr m_fileSystem;
        HeaderTech::Logging::LoggingPtr       m_logging;

    public:
        HeaderTech_Runtime_Export inline static std::shared_ptr<RuntimeContext> MakeRuntimeContext(
                const std::string_view &name,
                const std::string_view &version,
                const std::span<const char *> &args
        ) noexcept
        {
            auto context = std::make_shared<RuntimeContext>();
            context->m_name       = name;
            context->m_version    = version;
            context->m_args       = args;
            context->m_clock      = std::make_shared<HeaderTech::Common::SystemClock>();
            context->m_config     = HeaderTech::Config::make_config(context);
            context->m_fileSystem = HeaderTech::FileSystem::make_file_system(context);
            context->m_logging    = HeaderTech::Logging::make_logging(context);
            return context;
        }
    };

    using RuntimeContextPtr = std::shared_ptr<RuntimeContext>;

}// namespace HeaderTech::Runtime


#endif//HEADERTECH_RUNTIME_HPP
