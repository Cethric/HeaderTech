cmake_minimum_required(VERSION 3.19)
project(Logging VERSION 0.0.1.0 DESCRIPTION "HeaderTech Logging library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        Logging_SRC
        src/Logging.cpp
        src/LogFileHelper.cpp
)

set(
        Logging_INC
        inc/Logging/Logging.hpp
        inc/Logging/RotatingSink.hpp
        inc/Logging/RotatingSink.inl
        inc/Logging/LogFileHelper.hpp
)

add_library(Logging SHARED ${Logging_SRC} ${Logging_INC})
target_include_directories(
        Logging
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
            $<INSTALL_INTERFACE:include/>
)
target_link_libraries(Logging PRIVATE Common FileSystem Config)
target_link_libraries(Logging PUBLIC fmt::fmt spdlog::spdlog ctti::ctti physfs::physfs)

ConfigureLibrary(Logging 0 0 1 "+dev")