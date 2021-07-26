cmake_minimum_required(VERSION 3.17)
project(remotery CXX)

if (EMSCRIPTEN)
    add_library(Remotery INTERFACE)
    target_link_options(Remotery INTERFACE "SHELL:--profiling")
    target_link_options(Remotery INTERFACE "SHELL:--cpuprofiler")
    target_link_options(Remotery INTERFACE "SHELL:--memoryprofiler")
    target_compile_options(Remotery INTERFACE "SHELL:--profiling")
    em_setting_target(Remotery INTERFACE GL_TRACK_ERRORS 1 LINK)
    em_setting_target(Remotery INTERFACE GL_DEBUG 1 LINK)
    em_setting_target(Remotery INTERFACE GL_ASSERTIONS 1 LINK)

    RegisterLibrary(Remotery INTERFACE)

else (EMSCRIPTEN)

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

    add_library(Remotery SHARED ${Remotery_SRC} ${Remotery_Inc})
    target_include_directories(
            Remotery
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/remotery/lib/>
            $<INSTALL_INTERFACE:include/remotery/lib/>
            PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/remotery/lib/>
            $<INSTALL_INTERFACE:include/remotery/lib/>
    )

    target_compile_definitions(Remotery PUBLIC -DRMT_ENABLED=0)
    if (MSVC)
        target_compile_definitions(Remotery PUBLIC -DRMT_USE_OPENGL=1)
        target_compile_definitions(Remotery PUBLIC -DRMT_USE_D3D11=1)
        target_link_libraries(Remotery PRIVATE Winmm)
    endif (MSVC)
    if (APPLE)
        target_compile_definitions(Remotery PUBLIC -DRMT_USE_METAL=1)
    endif (APPLE)
    #if (UNIX)
    #    target_include_directories(Remotery PUBLIC libGL)
    #endif (UNIX)

    RegisterLibrary(Remotery PRIVATE OFF)

endif (EMSCRIPTEN)

add_library(remotery::remotery ALIAS Remotery)

# lib remotery::remotery
