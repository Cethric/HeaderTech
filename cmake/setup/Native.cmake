include_guard(GLOBAL)

set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)

if (MSVC)
    set(CMAKE_SYSTEM_VERSION 10.0)
endif (MSVC)

set(CMAKE_UNITY_BUILD ON)
set(BUILD_SHARED_LIBS ON)
