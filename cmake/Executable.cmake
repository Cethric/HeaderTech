include_guard(GLOBAL)

include(Version)

function(RegisterExecutable Target Visibility)
    if (EMSCRIPTEN)
        em_setting_target(${Target} ${Visibility} RELOCATABLE 1 COMPILE_AND_LINK)
        em_setting_target(${Target} ${Visibility} MAIN_MODULE 0 COMPILE_AND_LINK)
        em_setting_target(${Target} ${Visibility} LINKABLE 1 COMPILE_AND_LINK)
        em_setting_target(${Target} ${Visibility} MODULARIZE 1 COMPILE_AND_LINK)
        em_setting_target(${Target} ${Visibility} EXPORTED_FUNCTIONS "['_main']" COMPILE_AND_LINK)
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
endfunction(RegisterExecutable)

function(ConfigureExecutable Target Major Minor Patch Tweak)
    ConfigureVersion(${Target} ${Major} ${Minor} ${Patch} ${Tweak})


    set(RC_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Executable.rc)
    set(CONFIG_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Config.hpp)

    configure_file(${TEMPLATE_DIR}/ApplicationCMake.rc ${RC_OUTPUT_FILE} @ONLY NEWLINE_STYLE WIN32)
    configure_file(${TEMPLATE_DIR}/LibraryConfigCMake.hpp ${CONFIG_OUTPUT_FILE} @ONLY NEWLINE_STYLE WIN32)

    target_sources(
            ${Target}
            PRIVATE
            $<BUILD_INTERFACE:${RC_OUTPUT_FILE}>
            $<INSTALL_INTERFACE:include/${Target}/Executable.rc>
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

    set_target_properties(${Target} PROPERTIES PREFIX "HeaderTech_")

    RegisterExecutable(${Target} PRIVATE)
endfunction(ConfigureExecutable)