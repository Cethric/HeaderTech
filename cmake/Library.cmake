include_guard(GLOBAL)

include(Version)

include(emscripten/Functions)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
set(TEMPLATE_DIR ${SOURCE_DIR}/templates/)

function(RegisterLibrary Target Visibility)
    if (EMSCRIPTEN)
        em_setting_target(${Target} ${Visibility} RELOCATABLE 1 COMPILE_AND_LINK)
        em_setting_target(${Target} ${Visibility} SIDE_MODULE 1 COMPILE_AND_LINK)
        em_setting_target(${Target} ${Visibility} LINKABLE 1 COMPILE_AND_LINK)
    endif (EMSCRIPTEN)

    install(
            TARGETS ${Target}
            CONFIGURATIONS Debug
            EXPORT HeaderTechLibsDebug
            ARCHIVE
                DESTINATION Debug/lib
                COMPONENT Libraries
            LIBRARY
                DESTINATION Debug/lib
                COMPONENT Libraries
                NAMELINK_COMPONENT Development
            RUNTIME
                DESTINATION Debug/bin
                COMPONENT Runtime
            FRAMEWORK
                DESTINATION Debug/bin
                COMPONENT Runtime
            BUNDLE
                DESTINATION Debug/bin
                COMPONENT Runtime
            RESOURCE
                DESTINATION Debug/bin
                COMPONENT Runtime
            PUBLIC_HEADER
                DESTINATION Debug/include
                COMPONENT Development
            PRIVATE_HEADER
                DESTINATION Debug/include
                COMPONENT Development
    )

    install(
            TARGETS ${Target}
            CONFIGURATIONS Release
            EXPORT HeaderTechLibsRelease
            ARCHIVE
                DESTINATION Release/lib
                COMPONENT Libraries
            LIBRARY
                DESTINATION Release/lib
                COMPONENT Libraries
                NAMELINK_COMPONENT Development
            RUNTIME
                DESTINATION Release/bin
                COMPONENT Runtime
            FRAMEWORK
                DESTINATION Release/bin
                COMPONENT Runtime
            BUNDLE
                DESTINATION Release/bin
                COMPONENT Runtime
            RESOURCE
                DESTINATION Release/bin
                COMPONENT Runtime
            PUBLIC_HEADER
                DESTINATION Release/include
                COMPONENT Development
            PRIVATE_HEADER
                DESTINATION Release/include
                COMPONENT Development
    )
endfunction(RegisterLibrary)

function(ConfigureLibrary Target Major Minor Patch Tweak)
    ConfigureVersion(${Target} ${Major} ${Minor} ${Patch} ${Tweak})


    set(RC_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Library.rc)
    set(EXPORTS_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Exports.h)
    set(CONFIG_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Config.hpp)

    configure_file(${TEMPLATE_DIR}/LibraryCMake.rc ${RC_OUTPUT_FILE} @ONLY NEWLINE_STYLE WIN32)
    configure_file(${TEMPLATE_DIR}/LibraryConfigCMake.hpp ${CONFIG_OUTPUT_FILE} @ONLY NEWLINE_STYLE WIN32)

    target_sources(
            ${Target}
            PRIVATE
                $<BUILD_INTERFACE:${RC_OUTPUT_FILE}>
                $<BUILD_INTERFACE:${EXPORTS_OUTPUT_FILE}>
                $<INSTALL_INTERFACE:include/${Target}/Library.rc>
                $<INSTALL_INTERFACE:include/${Target}/Exports.h>
            PUBLIC
                $<BUILD_INTERFACE:${CONFIG_OUTPUT_FILE}>
                $<INSTALL_INTERFACE:include/${Target}/Config.hpp>
    )

    target_include_directories(
            ${Target}
            PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
                $<INSTALL_INTERFACE:include/>
            PRIVATE
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
                $<INSTALL_INTERFACE:include/>
    )

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

    set_target_properties(${Target} PROPERTIES PREFIX "HeaderTech_")

    RegisterLibrary(${Target} PRIVATE)
endfunction(ConfigureLibrary)