cmake_minimum_required(VERSION 3.19)
project(Editor VERSION 0.0.1.0 DESCRIPTION "HeaderTech Editor Application" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        Editor_SRC
        src/main.cpp
)

set(
        Editor_INC
)

add_executable(Editor ${Editor_SRC} ${Editor_INC})
target_include_directories(
        Editor
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
        $<INSTALL_INTERFACE:include/>
)
#target_link_libraries(Editor PRIVATE ctti::ctti)
target_link_libraries(Editor PRIVATE Core)
#target_link_libraries(Editor PRIVATE Config FileSystem Logging Common Event Runtime)

target_precompile_headers(Editor PRIVATE <Editor/Version.hpp>)

ConfigureExecutable(Editor 0 0 1 "+dev")
