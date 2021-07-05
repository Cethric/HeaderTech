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

#include "Runtime/Runtime.hpp"

#include <Config/Version.hpp>
#include <FileSystem/Version.hpp>
#include <Logging/Version.hpp>
#include <Runtime/Version.hpp>

#include <memory>

HeaderTech_Runtime_Export HeaderTech::Runtime::Runtime::Runtime(
        const std::string_view &name,
        const std::string_view &version,
        const std::span<const char *>& args
) noexcept
        : std::enable_shared_from_this<Runtime>(),
          m_config(nullptr),
          m_fileSystem(nullptr),
          m_logging(nullptr),
          m_log(nullptr),
          m_running(false)
{
    m_config     = std::make_shared<HeaderTech::Config::Config>(name, version, args);
    m_fileSystem = std::make_shared<HeaderTech::FileSystem::FileSystem>(m_config, args[0U]);
    m_logging    = std::make_shared<HeaderTech::Logging::Logging>(m_config, m_fileSystem);
    m_log        = m_logging->GetLogger<HeaderTech::Runtime::Runtime>();
}

HeaderTech_Runtime_Export HeaderTech::Runtime::Runtime::~Runtime() noexcept
{
    m_log->Information(SOURCE_LOCATION, "Runtime has been {}", "destroyed");
    m_log        = nullptr;
    m_logging    = nullptr;
    m_fileSystem = nullptr;
    m_config     = nullptr;
}

HeaderTech_Runtime_Export int HeaderTech::Runtime::Runtime::MainLoop() noexcept
{
    OnMainLoopWillStart();
    VersionCheck();
    m_running = true;
    OnMainLoopDidStart();
    m_log->Information(SOURCE_LOCATION, "Entering main loop");
    while (m_running) {
        OnMainLoopTick();
    }
    OnMainLoopDidEnd();
    return 0;
}

void HeaderTech::Runtime::Runtime::StopRunning() noexcept
{
    OnMainLoopWillEnd();
    m_running = false;
}

void HeaderTech::Runtime::Runtime::VersionCheck() noexcept
{
    m_log->Information(SOURCE_LOCATION, "Versions:");
    m_log->Information(SOURCE_LOCATION, "\tConfig {}", HeaderTech::Config::VersionString);
    m_log->Information(SOURCE_LOCATION, "\tFileSystem {}", HeaderTech::FileSystem::VersionString);
    m_log->Information(SOURCE_LOCATION, "\tLogging {}", HeaderTech::Logging::VersionString);
    m_log->Information(SOURCE_LOCATION, "\tRuntime {}", HeaderTech::Runtime::VersionString);
}

void HeaderTech::Runtime::Runtime::OnMainLoopWillStart() noexcept
{
}

void HeaderTech::Runtime::Runtime::OnMainLoopDidStart() noexcept
{
}

void HeaderTech::Runtime::Runtime::OnMainLoopWillEnd() noexcept
{
}

void HeaderTech::Runtime::Runtime::OnMainLoopDidEnd() noexcept
{
}

void HeaderTech::Runtime::Runtime::OnMainLoopTick() noexcept
{
}
