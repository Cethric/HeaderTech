include_guard(GLOBAL)

include(Version)

include(emscripten/Functions)

function(RegisterExecutable Target Visibility)
    if (EMSCRIPTEN)
        em_setting_target(${Target} ${Visibility} RELOCATABLE 1 COMPILE_AND_LINK)
        em_setting_target(${Target} ${Visibility} MAIN_MODULE 1 COMPILE_AND_LINK)
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


    set(RC_INPUT_FILE ${TEMPLATE_DIR}/ApplicationCMake.rc.in)
    set(RC_OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/include/${Target}/Executable.rc)

    configure_file(${RC_INPUT_FILE} ${RC_OUTPUT_FILE} @ONLY NEWLINE_STYLE UNIX)

    target_sources(
            ${Target}
            PRIVATE
            $<BUILD_INTERFACE:${RC_OUTPUT_FILE}>
            $<INSTALL_INTERFACE:include/${Target}/Executable.rc>
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

    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set_property(
                TARGET ${Target}
                PROPERTY UNITY_BUILD OFF
        )
    endif ()

    #    catch_discover_tests(${Target})

    RegisterExecutable(${Target} PRIVATE)
endfunction(ConfigureExecutable)
