cmake_minimum_required(VERSION 3.19)
project(Config VERSION 0.0.1.0 DESCRIPTION "HeaderTech Config library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        Config_SRC
        src/Config.cpp
)

set(
        Config_INC
        inc/Config/Config.hpp
)

add_library(Config SHARED ${Config_SRC} ${Config_INC})
target_include_directories(
        Config
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
        $<INSTALL_INTERFACE:include/>
)

target_link_libraries(Config PRIVATE Common)
target_link_libraries(Config PRIVATE argparse::argparse json::json)

target_precompile_headers(Config PUBLIC <Config/Version.hpp> <Config/Exports.h>)

ConfigureLibrary(Config 0 0 1 "+dev")
