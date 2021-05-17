//
// Created by Blake Rogan on 20/04/2021.
//

#include "FileSystem/FileSystem.hpp"

#include <physfs.h>

#include <iostream>

inline static void CheckPhyFSCall(int result)
{
    if (result == 0) {
        std::cerr << "Failed to execute PhysFS Command" << std::endl;
        std::cerr << PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()) << std::endl;
        std::exit(-1);
    }
}

HeaderTech_FileSystem_Export HeaderTech::FileSystem::FileSystem::FileSystem(
        const HeaderTech::Config::ConfigPtr &config,
        const char *argv0
) noexcept: std::enable_shared_from_this<FileSystem>()
{
    CheckPhyFSCall(PHYSFS_init(argv0));
    CheckPhyFSCall(PHYSFS_setSaneConfig("HeaderTech", "Editor", "zip", 0, 1));
    for (const auto &path : config->SearchPaths()) {
        CheckPhyFSCall(PHYSFS_mount(path.data(), nullptr, 1));
    }
}

HeaderTech::FileSystem::FileSystem::~FileSystem() noexcept
{
    CheckPhyFSCall(PHYSFS_deinit());
}
