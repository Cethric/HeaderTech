//
// Created by rogan2 on 4/05/2021.
//

#ifndef HEADERTECH_RUNTIME_HPP
#define HEADERTECH_RUNTIME_HPP

#include <Runtime/Exports.h>

#include <Config/Config.hpp>
#include <Logging/Logging.hpp>
#include <FileSystem/FileSystem.hpp>

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
}


#endif //HEADERTECH_RUNTIME_HPP
