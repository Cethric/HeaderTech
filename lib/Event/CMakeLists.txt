cmake_minimum_required(VERSION 3.19)
project(Event VERSION 0.0.1.0 DESCRIPTION "HeaderTech Event library" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        Event_SRC
        src/Event.cpp
        src/EventHandler.cpp
        src/EventProcessor.cpp
)

set(
        Event_INC
        inc/Event/Event.hpp
        inc/Event/EventHandler.hpp
        inc/Event/EventProcessor.hpp
        inc/Event/EventPriorityQueue.hpp
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
target_link_libraries(Event PUBLIC ctti::ctti hashmap::hashmap)

target_precompile_headers(Event PUBLIC <Event/Version.hpp> <Event/Exports.h>)

ConfigureLibrary(Event 0 0 1 "+dev")
