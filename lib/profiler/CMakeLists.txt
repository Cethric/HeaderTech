cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Profiler)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Profiler_SRC
        src/ProfilerIncludes.cpp
)

set(
        HeaderTech_Profiler_INC
        inc/ProfilerIncludes.h
        inc/ProfilerManager.h
        inc/ProfilerManager.inl
        inc/LogDispatcher.h
        inc/LogDispatcher.inl
        inc/Types.h
        inc/ProfileDispatcher.h
        inc/ProfileDispatcher.inl
        inc/ProfilerTypes.h
        inc/scoped/ScopedProfiler.h
        inc/scoped/ScopedProfileMark.h
        inc/scoped/ScopedProfileMark.inl
        inc/scoped/ScopedProfiler.inl
        inc/scoped/ScopedProfilerIncludes.h
)

add_library(HeaderTech_Profiler STATIC ${HeaderTech_Profiler_SRC} ${HeaderTech_Profiler_INC})
target_include_directories(HeaderTech_Profiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Profiler PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Profiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Profiler PUBLIC httplib::httplib glfw::glfw3 json::json)
target_link_libraries(HeaderTech_Profiler PUBLIC HeaderTech_Logging)
target_include_directories(HeaderTech_Profiler PUBLIC ${CMAKE_SOURCE_DIR}/ext/hashmap/parallel_hashmap)


add_custom_target(
        HeaderTech_Profiler_UI
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui
        COMMAND npm run build
        BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist/index.html
)

add_custom_command(
        TARGET HeaderTech_Profiler_UI
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/profiler/ui
        BYPRODUCTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/profiler/ui/index.html
)

#add_dependencies(HeaderTech_Profiler HeaderTech_Profiler_UI)
