cmake_minimum_required(VERSION 3.19)
project(Logging VERSION 0.0.1.0 DESCRIPTION "HeaderTech Logging library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        Logging_SRC
)

set(
        Logging_INC
)

add_library(Logging SHARED ${Logging_SRC} ${Logging_INC})
target_include_directories(
        Logging
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
            $<INSTALL_INTERFACE:include/>
)
target_link_libraries(Logging PRIVATE Common FileSystem)
target_link_libraries(Logging PUBLIC fmt::fmt spdlog::spdlog)

ConfigureLibrary(Logging 0 0 1 "+dev")