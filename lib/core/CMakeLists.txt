cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Core)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Core_SRC
        src/Engine.cpp
)

set(
        HeaderTech_Core_INC
        inc/Core.h
        inc/Runtime.h
        inc/Runtime.inl
        inc/events/LaunchEvent.h
        inc/scoped/ScopedGLFW.h
)

add_library(HeaderTech_Core STATIC ${HeaderTech_Core_SRC} ${HeaderTech_Core_INC})
target_include_directories(HeaderTech_Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Core PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Core PUBLIC glfw)
target_link_libraries(HeaderTech_Core PUBLIC HeaderTech_Logging HeaderTech_Events HeaderTech_Profiler HeaderTech_Config HeaderTech_Scene HeaderTech_Window HeaderTech_Render)
