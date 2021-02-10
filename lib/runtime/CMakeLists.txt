cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Runtime)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Runtime_SRC
        src/RuntimeIncludes.cpp
)

set(
        HeaderTech_Runtime_INC
        inc/RuntimeIncludes.h

        inc/Runtime.h
        inc/Runtime.inl

        # Events
        inc/events/LaunchEvent.h
)

add_library(HeaderTech_Runtime STATIC ${HeaderTech_Runtime_SRC} ${HeaderTech_Runtime_INC})
target_include_directories(HeaderTech_Runtime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Runtime PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Runtime PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Runtime PUBLIC HeaderTech_Logging HeaderTech_Profiler HeaderTech_Events HeaderTech_Config HeaderTech_Window HeaderTech_Scene)
