cmake_minimum_required(VERSION 3.19)
project(Sample VERSION 0.0.1.0 DESCRIPTION "HeaderTech Sample library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        Sample_SRC
        src/Sample.cpp
)

set(
        Sample_INC
        inc/Sample/Sample.hpp
)

add_library(Sample SHARED ${Sample_SRC} ${Sample_INC})
target_include_directories(
        Sample
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
            $<INSTALL_INTERFACE:include/>
)
target_link_libraries(Sample PUBLIC Common FileSystem Logging)

ConfigureLibrary(Sample 0 0 1 "+dev")