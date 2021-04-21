//
// Created by Blake Rogan on 20/04/2021.
//

#include <Editor/Version.hpp>
#include <FileSystem/Version.hpp>
#include <FileSystem/FileSystem.hpp>
#include <Config/Version.hpp>
#include <Config/Config.hpp>
#include <cassert>

int main(int argc, const char **argv)
{
    assert(HeaderTech::Editor::ValidateVersion(HeaderTech::Editor::HeaderVersion));
    assert(HeaderTech::Config::ValidateVersion(HeaderTech::Config::HeaderVersion));
    assert(HeaderTech::FileSystem::ValidateVersion(HeaderTech::FileSystem::HeaderVersion));

    HeaderTech::Config::Config         config("Editor", HeaderTech::Editor::VersionString, argc, argv);
    HeaderTech::FileSystem::FileSystem fileSystem(config, *argv);

    return 0;
}