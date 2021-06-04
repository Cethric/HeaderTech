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
    const char *argv0) noexcept : std::enable_shared_from_this<FileSystem>()
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
