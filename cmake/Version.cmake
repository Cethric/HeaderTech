include_guard(GLOBAL)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
set(TEMPLATE_DIR ${SOURCE_DIR}/templates/)

function(ConfigureVersion Target Major Minor Patch Tweak)
    set(HEADER_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Version.hpp)
    set(SOURCE_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/src/Version.cpp)
    set(RC_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Version.rc)
    set(BUILD_NUMBER_FILE ${CMAKE_CURRENT_BINARY_DIR}/build.txt)


    if (NOT EXISTS ${BUILD_NUMBER_FILE})
        file(WRITE ${BUILD_NUMBER_FILE} 0)
    endif (NOT EXISTS ${BUILD_NUMBER_FILE})

    set(HEADER_INPUT_FILE ${TEMPLATE_DIR}/VersionCMake.hpp)
    set(SOURCE_INPUT_FILE ${TEMPLATE_DIR}/VersionCMake.cpp)
    get_target_property(TARGET_TYPE ${Target} TYPE)
    if (TARGET_TYPE STREQUAL "EXECUTABLE")
        set(HEADER_INPUT_FILE ${TEMPLATE_DIR}/VersionExecutableCMake.hpp)
        set(SOURCE_INPUT_FILE ${TEMPLATE_DIR}/VersionExecutableCMake.cpp)
    endif ()

    add_custom_command(
            TARGET ${Target}
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -D BUILD_FILE=${BUILD_NUMBER_FILE} -P ${SOURCE_DIR}/UpdateBuild.cmake
            BYPRODUCTS ${BUILD_NUMBER_FILE}
            VERBATIM
    )

    add_custom_command(
            OUTPUT ${HEADER_OUTPUT_FILE} ${SOURCE_OUTPUT_FILE}
            MAIN_DEPENDENCY ${BUILD_NUMBER_FILE}
            BYPRODUCTS ${BUILD_NUMBER_FILE} ${HEADER_OUTPUT_FILE} ${SOURCE_OUTPUT_FILE} ${RC_OUTPUT_FILE}
            COMMAND ${CMAKE_COMMAND} -D CONFIG=${CMAKE_BUILD_TYPE} -D NAME=${Target} -D BUILD_FILE=${BUILD_NUMBER_FILE} -D MAJOR=${Major} -D MINOR=${Minor} -D PATCH=${Patch} -D TWEAK=${Tweak} -D HEADER_OUTPUT=${HEADER_OUTPUT_FILE} -D SOURCE_OUTPUT=${SOURCE_OUTPUT_FILE} -D RC_OUTPUT=${RC_OUTPUT_FILE} -D HEADER_INPUT=${HEADER_INPUT_FILE} -D SOURCE_INPUT=${SOURCE_INPUT_FILE} -D RC_INPUT=${TEMPLATE_DIR}/VersionCMake.rc -P ${SOURCE_DIR}/ConfigureVersion.cmake
            VERBATIM
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

    #    set_source_file_properties(${BUILD_NUMBER_FILE} PROPERTIES GENERATED 1)
    #    set_source_file_properties(${SOURCE_OUTPUT_FILE} PROPERTIES GENERATED 1)
    #    set_source_file_properties(${RC_OUTPUT_FILE} PROPERTIES GENERATED 1)
    #    set_source_file_properties(${HEADER_OUTPUT_FILE} PROPERTIES GENERATED 1)


    target_include_directories(
            ${Target}
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include/>
    )
endfunction()