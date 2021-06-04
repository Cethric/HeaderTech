include_guard(GLOBAL)

set(VERSION_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version/)
set(VERSION_TEMPLATE_DIR ${VERSION_SOURCE_DIR}/templates/)

macro(GetBuildNumberFile File)
    set(OUTPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/build/build.txt)

    if (NOT EXISTS ${OUTPUT_FILE})
        file(WRITE ${OUTPUT_FILE} 0)
    endif (NOT EXISTS ${OUTPUT_FILE})

    set(${File} ${OUTPUT_FILE})
endmacro()

macro(GetInputs Header Source RC)
    set(${Header} ${VERSION_TEMPLATE_DIR}/VersionLibraryCMake.hpp.in)
    set(${Source} ${VERSION_TEMPLATE_DIR}/VersionLibraryCMake.cpp.in)
    get_target_property(TARGET_TYPE ${Target} TYPE)
    if (TARGET_TYPE STREQUAL "EXECUTABLE")
        set(${Header} ${VERSION_TEMPLATE_DIR}/VersionExecutableCMake.hpp.in)
        set(${Source} ${VERSION_TEMPLATE_DIR}/VersionExecutableCMake.cpp.in)
    endif ()
    set(${RC} ${VERSION_TEMPLATE_DIR}/VersionCMake.rc.in)
endmacro()

macro(GetOutputs Header Source RC)
    set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(${Header} ${OUTPUT_DIR}/include/${Target}/Version.hpp)
    set(${Source} ${OUTPUT_DIR}/src/Version.cpp)
    set(${RC} ${OUTPUT_DIR}/include/${Target}/Version.rc)
endmacro()

function(ConfigureVersion Target Major Minor Patch Tweak)
    GetBuildNumberFile(BUILD_NUMBER_FILE)
    GetInputs(HEADER_INPUT_FILE SOURCE_INPUT_FILE RC_INPUT_FILE)
    GetOutputs(HEADER_OUTPUT_FILE SOURCE_OUTPUT_FILE RC_OUTPUT_FILE)

    set(
            UPDATE_BUILD_COMMAND
            ${CMAKE_COMMAND}
            -D BUILD_FILE=${BUILD_NUMBER_FILE}
            -P ${VERSION_SOURCE_DIR}/UpdateBuild.cmake
    )

    set(
            CONFIGURE_VERSION_COMMAND
            ${CMAKE_COMMAND}
            -D CONFIG=${CMAKE_BUILD_TYPE}
            -D NAME=${Target}
            -D BUILD_FILE=${BUILD_NUMBER_FILE}
            -D MAJOR=${Major}
            -D MINOR=${Minor}
            -D PATCH=${Patch}
            -D TWEAK=${Tweak}
            -D HEADER_OUTPUT=${HEADER_OUTPUT_FILE}
            -D SOURCE_OUTPUT=${SOURCE_OUTPUT_FILE}
            -D RC_OUTPUT=${RC_OUTPUT_FILE}
            -D HEADER_INPUT=${HEADER_INPUT_FILE}
            -D SOURCE_INPUT=${SOURCE_INPUT_FILE}
            -D RC_INPUT=${RC_INPUT_FILE}
            -P ${VERSION_SOURCE_DIR}/ConfigureVersion.cmake
    )

    add_custom_command(
            TARGET ${Target}
            PRE_BUILD
            COMMAND ${UPDATE_BUILD_COMMAND}
            BYPRODUCTS ${BUILD_NUMBER_FILE}
    )

    add_custom_command(
            OUTPUT ${HEADER_OUTPUT_FILE} ${SOURCE_OUTPUT_FILE} ${RC_OUTPUT_FILE}
            MAIN_DEPENDENCY ${BUILD_NUMBER_FILE}
            BYPRODUCTS ${BUILD_NUMBER_FILE} ${HEADER_OUTPUT_FILE} ${SOURCE_OUTPUT_FILE} ${RC_OUTPUT_FILE}
            COMMAND ${CONFIGURE_VERSION_COMMAND}
    )

    target_sources(
            ${Target}
            PRIVATE
            $<BUILD_INTERFACE:${BUILD_NUMBER_FILE}>
            $<BUILD_INTERFACE:${SOURCE_OUTPUT_FILE}>
            $<BUILD_INTERFACE:${RC_OUTPUT_FILE}>
            $<INSTALL_INTERFACE:include/${Target}/build.txt>
            $<INSTALL_INTERFACE:include/${Target}/Version.cpp>
            $<INSTALL_INTERFACE:include/${Target}/Version.rc>
            $<BUILD_INTERFACE:${HEADER_OUTPUT_FILE}>
            PUBLIC
            $<INSTALL_INTERFACE:include/${Target}/Version.hpp>
    )

    target_include_directories(
            ${Target}
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include/>
    )
endfunction()
