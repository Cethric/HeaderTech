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

#include <Runtime/Exports.h>

#include <Config/Config.hpp>
#include <FileSystem/FileSystem.hpp>
#include <Logging/Logging.hpp>

#include <memory>

namespace HeaderTech::Runtime {
    class Runtime : public std::enable_shared_from_this<Runtime> {
    public:
        HeaderTech_Runtime_Export Runtime(
                const std::string_view &name,
                const std::string_view &version,
                int argc,
                const char **argv
        ) noexcept;

        HeaderTech_Runtime_Export ~Runtime() noexcept;

        HeaderTech_Runtime_Export int MainLoop() noexcept;

        HeaderTech_Runtime_Export inline bool IsRunning() const noexcept
        { return m_running; }

        HeaderTech_Runtime_Export void StopRunning() noexcept;

        HeaderTech_Runtime_Export inline const HeaderTech::Config::ConfigPtr &Config() const noexcept
        { return m_config; }

        HeaderTech_Runtime_Export inline const HeaderTech::FileSystem::FileSystemPtr &FileSystem() const noexcept
        { return m_fileSystem; }

        HeaderTech_Runtime_Export inline const HeaderTech::Logging::LoggingPtr &Logging() const noexcept
        { return m_logging; }

    protected:
        HeaderTech_Runtime_Export virtual void VersionCheck() noexcept;

        HeaderTech_Runtime_Export virtual void OnMainLoopWillStart() noexcept;

        HeaderTech_Runtime_Export virtual void OnMainLoopDidStart() noexcept;

        HeaderTech_Runtime_Export virtual void OnMainLoopWillEnd() noexcept;

        HeaderTech_Runtime_Export virtual void OnMainLoopDidEnd() noexcept;

        HeaderTech_Runtime_Export virtual void OnMainLoopTick() noexcept;

    private:
        HeaderTech::Config::ConfigPtr         m_config;
        HeaderTech::FileSystem::FileSystemPtr m_fileSystem;
        HeaderTech::Logging::LoggingPtr       m_logging;

    private:
        HeaderTech::Logging::Logger m_log;
        bool                        m_running;
    };
}// namespace HeaderTech::Runtime


#endif//HEADERTECH_RUNTIME_HPP
