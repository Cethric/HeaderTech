cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Sandbox)


set(CMAKE_CXX_STANDARD 20)

add_executable(HeaderTech_Sandbox src/main.cpp inc/Sandbox.h)
target_link_libraries(HeaderTech_Sandbox PUBLIC HeaderTech_Core HeaderTech_FileSystem HeaderTech_Scene)
target_compile_definitions(HeaderTech_Sandbox PUBLIC -DHEADERTECH_CONFIG_IMPL=1)
target_compile_definitions(HeaderTech_Sandbox PUBLIC -DHEADERTECH_CORE_IMPL=1)
target_compile_definitions(HeaderTech_Sandbox PUBLIC -DHEADERTECH_EVENTS_IMPL=1)
target_compile_definitions(HeaderTech_Sandbox PUBLIC -DHEADERTECH_LOGGING_IMPL=1)
target_compile_definitions(HeaderTech_Sandbox PUBLIC -DHEADERTECH_PROFILER_IMPL=1)
target_compile_definitions(HeaderTech_Sandbox PUBLIC -DHEADERTECH_FILESYSTEM_IMPL=1)
target_compile_definitions(HeaderTech_Sandbox PUBLIC -DHEADERTECH_SCENE_IMPL=1)
target_include_directories(HeaderTech_Sandbox PUBLIC inc)
target_include_directories(HeaderTech_Sandbox PRIVATE src)


set_property(
        TARGET HeaderTech_Sandbox
        PROPERTY UNITY_BUILD OFF
)
