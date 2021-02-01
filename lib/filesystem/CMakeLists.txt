cmake_minimum_required(VERSION 3.17)
project(HeaderTech_FileSystem)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_FileSystem_SRC
        src/FileSystem.cpp
)

set(
        HeaderTech_FileSystem_INC
        inc/FileSystem.h
        inc/scoped/ScopedFileSystem.h
)

add_library(HeaderTech_FileSystem STATIC ${HeaderTech_FileSystem_SRC} ${HeaderTech_FileSystem_INC})
target_include_directories(HeaderTech_FileSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_FileSystem PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_FileSystem PUBLIC ${CMAKE_SOURCE_DIR}/ext/physfs/src)
target_include_directories(HeaderTech_FileSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_FileSystem PUBLIC physfs::physfs)
