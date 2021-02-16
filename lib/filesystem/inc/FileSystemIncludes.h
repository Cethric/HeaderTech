//
// Created by rogan2 on 16/11/2020.
//

#ifndef HEADERTECH_FILESYSTEMINCLUDES_H
#define HEADERTECH_FILESYSTEMINCLUDES_H

#include <scoped/ScopedFileSystem.h>

#if defined(HEADERTECH_FILESYSTEM_IMPL) && DEFINE_IMPLEMENTATION == 1

#endif

namespace HeaderTech::FileSystem {
    int FileSystemVersion();
}

#endif //HEADERTECH_FILESYSTEMINCLUDES_H
