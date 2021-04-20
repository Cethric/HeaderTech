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
        std::exit(-1);
    }
}

inline static void SearchPathCallback(void *, const char *path)
{
    std::cout << "Search Path: " << path << std::endl;
}

HeaderTech_FileSystem_Export HeaderTech::FileSystem::FileSystem::FileSystem(const char *argv0) noexcept
{
    CheckPhyFSCall(PHYSFS_init(argv0));
    CheckPhyFSCall(PHYSFS_setSaneConfig("HeaderTech", "Editor", "zip", 0, 1));

    PHYSFS_getSearchPathCallback(SearchPathCallback, nullptr);
}

HeaderTech::FileSystem::FileSystem::~FileSystem() noexcept
{
    CheckPhyFSCall(PHYSFS_deinit());
}
