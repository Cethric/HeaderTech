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

#include "Runtime/Application.hpp"

using namespace HeaderTech::Runtime;

Application::Application(
        const std::string_view &name,
        const std::string_view &version,
        const std::span<const char *> &args,
        const HeaderTech::Common::ClockPtr &clock
) noexcept:
        HeaderTech::Event::EventProcessor(clock),
        m_config(HeaderTech::Config::MakeConfig(name, version, args)),
        m_fileSystem(HeaderTech::FileSystem::MakeFileSystem(m_config, args[0])),
        m_logging(HeaderTech::Logging::MakeLogging(m_config, m_fileSystem)),
        m_log(m_logging->CreateLogger<Application>()),
        m_isRunning(false)
{
    m_log->info("Launching {} {}", name.data(), version.data());
}

Application::~Application() noexcept
{
    m_log->info("The application has been shutdown");
}

int Application::Launch() noexcept
{
    m_isRunning = true;
    while (m_isRunning) {
        ProcessTick();
    }
    return 0;
}

void Application::Terminate() noexcept
{
    m_isRunning = false;
}
