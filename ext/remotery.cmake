cmake_minimum_required(VERSION 3.17)
project(remotery CXX)

set(CMAKE_CXX_STANDARD 20)

set(
        Remotery_SRC
        remotery/lib/Remotery.c
)

if (APPLE)
    set(
            Remotery_SRC
            ${Remotery_SRC}
            remotery/lib/RemoteryMetal.mm
    )
endif (APPLE)

set(
        Remotery_Inc
        remotery/lib/Remotery.h
)

add_library(Remotery STATIC ${Remotery_SRC} ${Remotery_Inc})
target_include_directories(Remotery PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/remotery/lib/)
target_include_directories(Remotery PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/remotery/lib/)
target_compile_definitions(Remotery PUBLIC -DRMT_ENABLED=1)
if (MSVC)
    target_compile_definitions(Remotery PUBLIC -DRMT_USE_OPENGL=1)
    target_compile_definitions(Remotery PUBLIC -DRMT_USE_D3D11=1)
endif (MSVC)
if (APPLE)
    target_compile_definitions(Remotery PUBLIC -DRMT_USE_METAL=1)
endif (APPLE)
if (UNIX)
    target_include_directories(Remotery PUBLIC libGL)
endif (UNIX)

add_library(remotery::remotery ALIAS Remotery)

# lib remotery::remotery
