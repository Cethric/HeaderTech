cmake_minimum_required(VERSION 3.19)
project(Event VERSION 0.0.1.0 DESCRIPTION "HeaderTech Event library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        Event_SRC
)

set(
        Event_INC
        inc/Event/Reactive/Reactive.hpp
)

add_library(Event SHARED ${Event_SRC} ${Event_INC})
target_include_directories(
        Event
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
            $<INSTALL_INTERFACE:include/>
)

target_link_libraries(Event PRIVATE Common)

ConfigureLibrary(Event 0 0 1 "+dev")