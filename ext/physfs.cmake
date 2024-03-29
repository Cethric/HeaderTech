set(PHYSFS_ARCHIVE_ZIP ON CACHE INTERNAL "" FORCE)
set(PHYSFS_ARCHIVE_7Z ON CACHE INTERNAL "" FORCE)
set(PHYSFS_ARCHIVE_GRP OFF CACHE INTERNAL "" FORCE)
set(PHYSFS_ARCHIVE_WAD OFF CACHE INTERNAL "" FORCE)
set(PHYSFS_ARCHIVE_HOG OFF CACHE INTERNAL "" FORCE)
set(PHYSFS_ARCHIVE_MVL OFF CACHE INTERNAL "" FORCE)
set(PHYSFS_ARCHIVE_QPAK OFF CACHE INTERNAL "" FORCE)
set(PHYSFS_ARCHIVE_SLB OFF CACHE INTERNAL "" FORCE)
set(PHYSFS_ARCHIVE_ISO9660 OFF CACHE INTERNAL "" FORCE)
set(PHYSFS_ARCHIVE_VDF OFF CACHE INTERNAL "" FORCE)
set(PHYSFS_BUILD_STATIC OFF CACHE INTERNAL "" FORCE)
set(PHYSFS_BUILD_SHARED ON CACHE INTERNAL "" FORCE)
set(PHYSFS_BUILD_TEST OFF CACHE INTERNAL "" FORCE)

add_subdirectory(physfs/ EXCLUDE_FROM_ALL)

set_property(
        TARGET physfs
        PROPERTY UNITY_BUILD OFF
)

if (MSVC)
    set_property(
            TARGET physfs
            PROPERTY C_FLAGS /wd5105
    )
endif (MSVC)

target_include_directories(
        physfs
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/physfs/src>
        $<INSTALL_INTERFACE:include/>
)

add_library(physfs::physfs ALIAS physfs)

RegisterLibrary(physfs PRIVATE OFF)

# lib physfs::physfs
