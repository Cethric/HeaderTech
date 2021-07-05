cmake_minimum_required(VERSION 3.19)
project(TEMPLATE VERSION 0.0.1.0 DESCRIPTION "HeaderTech Template library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        TEMPLATE_SRC
)

set(
        TEMPLATE_INC
)

add_library(TEMPLATE SHARED ${TEMPLATE_SRC} ${TEMPLATE_INC})
target_include_directories(
        TEMPLATE
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
        $<INSTALL_INTERFACE:include/>
)

target_link_libraries(TEMPLATE PRIVATE Common)

ConfigureLibrary(TEMPLATE 0 0 1 "+dev")

target_precompile_headers(TEMPLATE REUSE_FROM Common)
target_precompile_headers(TEMPLATE PUBLIC <TEMPLATE/Version.hpp> <TEMPLATE/Exports.h>)

if (BUILD_TESTING)
    add_subdirectory(test)
endif (BUILD_TESTING)
