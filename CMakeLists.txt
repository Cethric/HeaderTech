cmake_minimum_required(VERSION 3.17)
project(HeaderTech)



set(CMAKE_UNITY_BUILD ON)
if (MSVC)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

        set(CMAKE_UNITY_BUILD OFF)
    endif ()
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)
if (MSVC)
    add_compile_options(/GR-)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
endif ()

add_subdirectory(ext/)
add_subdirectory(lib/)
add_subdirectory(app/)


include(GNUInstallDirs)

message(STATUS "FLAGS ${CMAKE_C_FLAGS}")
message(STATUS "FLAGS ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message(STATUS "FLAGS ${CMAKE_CXX_FLAGS}")
message(STATUS "FLAGS ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
