cmake_minimum_required(VERSION 3.17)
project(HeaderTech)


set(CMAKE_UNITY_BUILD ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)

add_subdirectory(ext/)
add_subdirectory(lib/)
add_subdirectory(app/)


include(GNUInstallDirs)
