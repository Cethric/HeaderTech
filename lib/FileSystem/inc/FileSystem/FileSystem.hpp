//
// Created by Blake Rogan on 20/04/2021.
//

#ifndef HEADERTECH_FILESYSTEM_HPP
#define HEADERTECH_FILESYSTEM_HPP

#include <FileSystem/Exports.h>

#include <Config/Config.hpp>

namespace HeaderTech::FileSystem {
    class FileSystem {
    public:
        HeaderTech_FileSystem_Export explicit FileSystem(const HeaderTech::Config::Config &config, const char *argv0) noexcept;

        HeaderTech_FileSystem_Export ~FileSystem() noexcept;
    };
}


#endif //HEADERTECH_FILESYSTEM_HPP
