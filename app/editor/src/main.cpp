//
// Created by Blake Rogan on 20/04/2021.
//

#include <Editor/Version.hpp>
#include <FileSystem/Version.hpp>
#include <FileSystem/FileSystem.hpp>
#include <Config/Version.hpp>
#include <Config/Config.hpp>
#include <Logging/Version.hpp>
#include <Logging/Logging.hpp>
#include <cassert>

class Application {
public:
    Application(
            HeaderTech::Config::Config &config,
            HeaderTech::FileSystem::FileSystem &fileSystem,
            HeaderTech::Logging::Logging &logging
    ) noexcept: m_log(logging.CreateLogger<Application>())
    { m_log->info("Launching Application"); }

private:
    HeaderTech::Logging::Logger m_log;
};

int main(int argc, const char **argv)
{
    assert(HeaderTech::Editor::ValidateVersion(HeaderTech::Editor::HeaderVersion));
    assert(HeaderTech::Config::ValidateVersion(HeaderTech::Config::HeaderVersion));
    assert(HeaderTech::FileSystem::ValidateVersion(HeaderTech::FileSystem::HeaderVersion));
    assert(HeaderTech::Logging::ValidateVersion(HeaderTech::Logging::HeaderVersion));

    HeaderTech::Config::Config         config("Editor", HeaderTech::Editor::VersionString, argc, argv);
    HeaderTech::FileSystem::FileSystem fileSystem(config, *argv);
    HeaderTech::Logging::Logging       logging(config, fileSystem);

    logging.GetOrCreateLogger("console")->info("Hello, World!");
    logging.GetOrCreateLogger("console")->info("Versions:");
    logging.GetOrCreateLogger("console")->info("\tEditor {}", HeaderTech::Editor::VersionString);
    logging.GetOrCreateLogger("console")->info("\tConfig {}", HeaderTech::Config::VersionString);
    logging.GetOrCreateLogger("console")->info("\tFileSystem {}", HeaderTech::FileSystem::VersionString);
    logging.GetOrCreateLogger("console")->info("\tLogging {}", HeaderTech::Logging::VersionString);

    Application application(config, fileSystem, logging);

    return 0;
}