//
// Created by Blake Rogan on 20/04/2021.
//

#ifndef HEADERTECH_FILESYSTEM_HPP
#define HEADERTECH_FILESYSTEM_HPP

#include <FileSystem/Exports.h>

#include <Config/Config.hpp>

#include <memory>

namespace HeaderTech::FileSystem {
    class FileSystem : public std::enable_shared_from_this<FileSystem> {
    public:
        HeaderTech_FileSystem_Export explicit FileSystem(
                const HeaderTech::Config::ConfigPtr &config,
                const char *argv0
        ) noexcept;

        HeaderTech_FileSystem_Export ~FileSystem() noexcept;
    };

    using FileSystemPtr = std::shared_ptr<FileSystem>;
    using FileSystemWeakPtr = std::weak_ptr<FileSystem>;
}


#endif //HEADERTECH_FILESYSTEM_HPP
