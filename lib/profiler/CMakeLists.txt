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
        inc/scoped/ScopedProfilerIncludes.h
        # Scoped
        inc/scoped/ScopedProfiler.h
        inc/scoped/ScopedProfiler.inl
)

add_library(HeaderTech_Profiler STATIC ${HeaderTech_Profiler_SRC} ${HeaderTech_Profiler_INC})
target_include_directories(HeaderTech_Profiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Profiler PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Profiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Profiler PUBLIC remotery::remotery)
target_link_libraries(HeaderTech_Profiler PUBLIC HeaderTech_Logging)


generate_export_header(
        HeaderTech_Profiler
        EXPORT_FILE_NAME inc/HeaderTech_Profiler_Export.h
)
