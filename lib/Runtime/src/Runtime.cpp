//
// Created by rogan2 on 4/05/2021.
//
#include "Runtime/Runtime.hpp"

#include <Config/Version.hpp>
#include <FileSystem/Version.hpp>
#include <Logging/Version.hpp>
#include <Runtime/Version.hpp>

HeaderTech_Runtime_Export HeaderTech::Runtime::Runtime::Runtime(
        const std::string_view &name,
        const std::string_view &version,
        int argc,
        const char **argv
) noexcept
        : std::enable_shared_from_this<Runtime>(),
          m_config(nullptr),
          m_fileSystem(nullptr),
          m_logging(nullptr),
          m_log(nullptr),
          m_running(false)
{
    m_config     = std::make_shared<HeaderTech::Config::Config>(name, version, argc, argv);
    m_fileSystem = std::make_shared<HeaderTech::FileSystem::FileSystem>(m_config, argv[0]);
    m_logging    = std::make_shared<HeaderTech::Logging::Logging>(m_config, m_fileSystem);
    m_log        = m_logging->CreateLogger<HeaderTech::Runtime::Runtime>();
}

HeaderTech_Runtime_Export HeaderTech::Runtime::Runtime::~Runtime() noexcept
{
    m_log->info("Runtime has been destroyed");
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
    m_log->info("Entering main loop");
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
    m_log->info("Versions:");
    m_log->info("\tConfig {}", HeaderTech::Config::VersionString);
    m_log->info("\tFileSystem {}", HeaderTech::FileSystem::VersionString);
    m_log->info("\tLogging {}", HeaderTech::Logging::VersionString);
    m_log->info("\tRuntime {}", HeaderTech::Runtime::VersionString);
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
