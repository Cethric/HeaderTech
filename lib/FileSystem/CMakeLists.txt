cmake_minimum_required(VERSION 3.19)
project(FileSystem VERSION 0.0.1.0 DESCRIPTION "HeaderTech FileSystem library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        FileSystem_SRC
        src/FileSystem.cpp
)

set(
        FileSystem_INC
        inc/FileSystem/FileSystem.hpp
)

add_library(FileSystem SHARED ${FileSystem_SRC} ${FileSystem_INC})
target_include_directories(
        FileSystem
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
            $<INSTALL_INTERFACE:include/>
)
target_link_libraries(FileSystem PRIVATE Common Config)
target_link_libraries(FileSystem PRIVATE physfs::physfs)

ConfigureLibrary(FileSystem 0 0 1 "+dev")