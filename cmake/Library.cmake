include_guard(GLOBAL)

include(Version)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
set(TEMPLATE_DIR ${SOURCE_DIR}/templates/)

function(ConfigureLibrary Target Major Minor Patch Tweak)
    ConfigureVersion(${Target} ${Major} ${Minor} ${Patch} ${Tweak})


    set(RC_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Library.rc)
    set(EXPORTS_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Exports.h)
    set(CONFIG_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Config.hpp)

    configure_file(${TEMPLATE_DIR}/LibraryCMake.rc ${RC_OUTPUT_FILE} @ONLY NEWLINE_STYLE WIN32)
    configure_file(${TEMPLATE_DIR}/LibraryConfigCMake.hpp ${CONFIG_OUTPUT_FILE} @ONLY NEWLINE_STYLE WIN32)

    target_sources(${Target} PRIVATE ${RC_OUTPUT_FILE} ${EXPORTS_OUTPUT_FILE})
    target_sources(${Target} PUBLIC ${CONFIG_OUTPUT_FILE})
    target_include_directories(${Target} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)

    generate_export_header(
            ${Target}
            EXPORT_MACRO_NAME ${Target}_Export
            DEPRECATED_MACRO_NAME ${Target}_Deprecated
            NO_EXPORT_MACRO_NAME ${Target}_No_Export
            INCLUDE_GUARD_NAME ${Target}_EXPORT_H
            STATIC_DEFINE ${Target}_Static_Define
            NO_DEPRECATED_MACRO_NAME ${Target}_No_Deprecated
            PREFIX_NAME HeaderTech_
            EXPORT_FILE_NAME ${EXPORTS_OUTPUT_FILE}
    )
endfunction(ConfigureLibrary)