include_guard(GLOBAL)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
set(TEMPLATE_DIR ${SOURCE_DIR}/templates/)

function(ConfigureVersion Target Major Minor Patch Tweak)
    if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/build.txt)
        file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/build.txt 0)
    endif (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/build.txt)


    set(HEADER_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Version.hpp)
    set(SOURCE_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/src/Version.cpp)
    set(RC_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Version.rc)
    set(BUILD_NUMBER_FILE ${CMAKE_CURRENT_BINARY_DIR}/build.txt)

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
            COMMAND ${CMAKE_COMMAND} -D CONFIG=${CMAKE_BUILD_TYPE} -D NAME=${Target} -D BUILD_FILE=${BUILD_NUMBER_FILE} -D MAJOR=${Major} -D MINOR=${Minor} -D PATCH=${Patch} -D TWEAK=${Tweak} -D HEADER_OUTPUT=${HEADER_OUTPUT_FILE} -D SOURCE_OUTPUT=${SOURCE_OUTPUT_FILE} -D RC_OUTPUT=${RC_OUTPUT_FILE} -D HEADER_INPUT=${TEMPLATE_DIR}/VersionCMake.hpp -D SOURCE_INPUT=${TEMPLATE_DIR}/VersionCMake.cpp -D RC_INPUT=${TEMPLATE_DIR}/VersionCMake.rc -P ${SOURCE_DIR}/ConfigureVersion.cmake
            VERBATIM
    )

    target_sources(${Target} PUBLIC ${HEADER_OUTPUT_FILE})
    target_sources(${Target} PRIVATE ${BUILD_NUMBER_FILE} ${SOURCE_OUTPUT_FILE} ${RC_OUTPUT_FILE})
    target_include_directories(${Target} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)
endfunction()