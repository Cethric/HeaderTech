cmake_minimum_required(VERSION 3.19)
project(Runtime VERSION 0.0.1.0 DESCRIPTION "HeaderTech Runtime library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        Runtime_SRC
        src/Runtime.cpp
        src/Application.cpp
)

set(
        Runtime_INC
        inc/Runtime/Runtime.hpp
        inc/Runtime/Application.hpp
)

add_library(Runtime SHARED ${Runtime_SRC} ${Runtime_INC})
target_include_directories(
        Runtime
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
        $<INSTALL_INTERFACE:include/>
)

target_link_libraries(Runtime PRIVATE Common Config FileSystem Logging Event)

target_precompile_headers(Runtime PUBLIC <Runtime/Version.hpp> <Runtime/Exports.h>)

ConfigureLibrary(Runtime 0 0 1 "+dev")
