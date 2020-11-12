cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Events)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Events_SRC
        src/Event.cpp
)

set(
        HeaderTech_Events_INC
        inc/Event.h
        inc/EventDispatcher.h
        inc/EventDispatcher.inl
        inc/Event.inl inc/EventSubscription.h inc/EventSubscription.inl inc/Events.h)

add_library(HeaderTech_Events STATIC ${HeaderTech_Events_SRC} ${HeaderTech_Events_INC})
target_include_directories(HeaderTech_Events PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Events PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Events PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Events PUBLIC ctti)
target_link_libraries(HeaderTech_Events PUBLIC HeaderTech_Logging)