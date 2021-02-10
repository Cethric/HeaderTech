cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Logging)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Logging_SRC
        src/LoggingIncludes.cpp
)

set(
        HeaderTech_Logging_INC
        inc/LoggingIncludes.h
        inc/Logger.h
        inc/Logger.inl
        inc/ProfilerSink.h
        inc/ProfilerSink.inl
        inc/scoped/ScopedLogging.h
        inc/FileSink.h
        inc/FileSink.inl
        inc/scoped/ScopedLogging.inl)

add_library(HeaderTech_Logging STATIC ${HeaderTech_Logging_SRC} ${HeaderTech_Logging_INC})
target_include_directories(HeaderTech_Logging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Logging PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Logging PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Logging PUBLIC spdlog::spdlog ctti::ctti)
target_link_libraries(HeaderTech_Logging PUBLIC HeaderTech_Profiler HeaderTech_FileSystem)
