//
// Created by Blake Rogan on 20/04/2021.
//

#include <Sample/Version.hpp>
#include <Editor/Version.hpp>
#include <FileSystem/Version.hpp>
#include <FileSystem/FileSystem.hpp>
#include <cassert>

int main(int argc, const char **argv)
{
    assert(HeaderTech::SampleVersion::ValidateVersion(HeaderTech::SampleVersion::HeaderVersion));
    assert(HeaderTech::EditorVersion::ValidateVersion(HeaderTech::EditorVersion::HeaderVersion));
    assert(HeaderTech::FileSystemVersion::ValidateVersion(HeaderTech::FileSystemVersion::HeaderVersion));

    HeaderTech::FileSystem::FileSystem fileSystem(*argv);
    
    return 0;
}