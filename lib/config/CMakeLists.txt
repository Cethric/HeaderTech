cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Config)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Config_SRC
        src/Config.cpp
)

set(
        HeaderTech_Config_INC
        inc/Config.h
        inc/RuntimeConfig.h
)

add_library(HeaderTech_Config STATIC ${HeaderTech_Config_SRC} ${HeaderTech_Config_INC})
target_include_directories(HeaderTech_Config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Config PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Config PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
