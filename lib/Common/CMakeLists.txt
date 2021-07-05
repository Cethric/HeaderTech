cmake_minimum_required(VERSION 3.19)
project(Common VERSION 0.0.1.0 DESCRIPTION "HeaderTech Common library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        Common_SRC
        src/Clock.cpp
)

set(
        Common_INC
        inc/Common/Clock.hpp
)

add_library(Common SHARED ${Common_SRC} ${Common_INC})
target_include_directories(
        Common
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
        $<INSTALL_INTERFACE:include/>
)

ConfigureLibrary(Common 0 0 1 "+dev")

target_precompile_headers(Common PUBLIC <Common/Version.hpp> <Common/Exports.h>)

if (BUILD_TESTING)
    add_subdirectory(test)
endif (BUILD_TESTING)
