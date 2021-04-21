//
// Created by Blake Rogan on 20/04/2021.
//

#include "FileSystem/FileSystem.hpp"

#include <physfs.h>

#include <iostream>

struct ArchiveData {
    PHYSFS_Io *io;
};

static inline void *openArchive(PHYSFS_Io *io, const char *name, int forWrite, int *claimed)
{
    std::cout << "Open Archive" << name << " - " << forWrite << std::endl;
    return new ArchiveData{
            .io = io,
    };
}

static inline PHYSFS_EnumerateCallbackResult enumerate(
        void *opaque,
        const char *dirname,
        PHYSFS_EnumerateCallback cb,
        const char *origdir,
        void *callbackdata
)
{
    auto data = static_cast<ArchiveData *>(opaque);
    return PHYSFS_ENUM_STOP;
}

static inline PHYSFS_Io *openRead(void *opaque, const char *fnm)
{
    auto data = static_cast<ArchiveData *>(opaque);
    return nullptr;
}

static inline PHYSFS_Io *openWrite(void *opaque, const char *fnm)
{
    auto data = static_cast<ArchiveData *>(opaque);
    return nullptr;
}

static inline PHYSFS_Io *openAppend(void *opaque, const char *fnm)
{
    auto data = static_cast<ArchiveData *>(opaque);
    return nullptr;
}

static inline int remove(void *opaque, const char *fnm)
{
    auto data = static_cast<ArchiveData *>(opaque);
    return 1;
}

static inline int mkdir(void *opaque, const char *fnm)
{
    auto data = static_cast<ArchiveData *>(opaque);
    return 1;
}

static inline int stat(void *opaque, const char *fn, PHYSFS_Stat *stat)
{
    auto data = static_cast<ArchiveData *>(opaque);
    return 1;
}

static inline void closeArchive(void *opaque)
{
    auto data = static_cast<ArchiveData *>(opaque);
    delete data;
}

static const PHYSFS_Archiver MyArchiver{
        .version = 0,
        .info = {
                .extension = ".hpro",
                .description = "HeaderTech Project Container",
                .author = "Blake Rogan",
                .url = "https://cethric.github.io",
                .supportsSymlinks = 0,
        },
        .openArchive = openArchive,
        .enumerate = enumerate,
        .openRead = openRead,
        .openWrite = openWrite,
        .openAppend = openAppend,
        .remove = remove,
        .mkdir = mkdir,
        .stat = stat,
        .closeArchive = closeArchive,
};

inline static void CheckPhyFSCall(int result)
{
    if (result == 0) {
        std::cerr << "Failed to execute PhysFS Command" << std::endl;
        std::cerr << PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()) << std::endl;
        std::exit(-1);
    }
}

inline static void SearchPathCallback(void *, const char *path)
{
    std::cout << "Search Path: " << path << std::endl;
}

HeaderTech_FileSystem_Export HeaderTech::FileSystem::FileSystem::FileSystem(
        const HeaderTech::Config::Config &config,
        const char *argv0
) noexcept
{
    CheckPhyFSCall(PHYSFS_init(argv0));
    CheckPhyFSCall(PHYSFS_setSaneConfig("HeaderTech", "Editor", "zip", 0, 1));
    for (const auto &path : config.SearchPaths()) {
        CheckPhyFSCall(PHYSFS_addToSearchPath(path.data(), 1));
    }

    PHYSFS_getSearchPathCallback(SearchPathCallback, nullptr);

    CheckPhyFSCall(PHYSFS_registerArchiver(&MyArchiver));

    for (auto i = PHYSFS_supportedArchiveTypes(); *i != nullptr; i++) {
        std::cout << "Archiver: " << (*i)->description << " - " << (*i)->extension << std::endl;
    }

    char buffer[1024];

    CheckPhyFSCall(PHYSFS_mountMemory(buffer, 1024, [](void *data) {}, "Project.hpro", "/project", 1));

    auto file = PHYSFS_openWrite("/project/Example.txt");
    PHYSFS_write(file, "Hello, World!", 1, 14);
    PHYSFS_close(file);
}

HeaderTech::FileSystem::FileSystem::~FileSystem() noexcept
{
    CheckPhyFSCall(PHYSFS_deinit());
}
