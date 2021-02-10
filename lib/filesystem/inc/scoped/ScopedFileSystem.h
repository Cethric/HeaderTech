//
// Created by rogan2 on 16/11/2020.
//

#ifndef HEADERTECH_SCOPEDFILESYSTEM_H
#define HEADERTECH_SCOPEDFILESYSTEM_H

#include <physfs.h>
#include <exception>

namespace HeaderTech::FileSystem::Scoped {
    class ScopedFileSystem {
    public:
        explicit inline ScopedFileSystem(const char *argv0, const char* name)
        {
            if (PHYSFS_init(argv0) == 0) {
                throw std::exception("Failed to initialise PhysFS");
            };
            if (PHYSFS_setSaneConfig("HeaderTech", name, "zip", 0, 1) == 0) {
                throw std::exception("Failed to set sane fs config");
            }
        }

        inline ~ScopedFileSystem() {
            PHYSFS_deinit();
        }
    };
}

#endif //HEADERTECH_SCOPEDFILESYSTEM_H
