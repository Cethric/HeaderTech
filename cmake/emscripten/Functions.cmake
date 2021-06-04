include_guard(GLOBAL)

function(em_setting Name Value Section)
    if (${Section} MATCHES "COMPILE_AND_LINK" OR ${Section} MATCHES "COMPILE")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s ${Name}=${Value}" PARENT_SCOPE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ${Name}=${Value}" PARENT_SCOPE)
    endif ()
    if (${Section} MATCHES "COMPILE_AND_LINK" OR ${Section} MATCHES "LINK")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ${Name}=${Value}" PARENT_SCOPE)
    endif ()
endfunction(em_setting)

function(em_setting_target Target Visibility Name Value Section)
    if (${Section} MATCHES "COMPILE_AND_LINK" OR ${Section} MATCHES "COMPILE")
        target_compile_options(${Target} ${Visibility} "SHELL:-s ${Name}=${Value}")
    endif ()
    if (${Section} MATCHES "COMPILE_AND_LINK" OR ${Section} MATCHES "LINK")
        target_link_options(${Target} ${Visibility} "SHELL:-s ${Name}=${Value}")
    endif ()
endfunction(em_setting_target)

#function(em_make_shared Target)
#    em_setting_target(${Target} PRIVATE SIDE_MODULE 1 COMPILE_AND_LINK)
#    set_target_properties(
#            ${Target} PROPERTIES
#            SUFFIX ".wasm"
#    )
#endfunction(em_make_shared)

#function(em_make_executable Target)
#    target_link_options(${Target} PUBLIC "--bind")
#    target_compile_options(${Target} PUBLIC "--bind")
#    set_target_properties(${Target} PROPERTIES SUFFIX ".mjs")
#    em_setting_target(${Target} PUBLIC MAIN_MODULE 1 COMPILE_AND_LINK)
#    em_setting_target(${Target} PUBLIC SINGLE_FILE 0 COMPILE_AND_LINK)
#    em_setting_target(${Target} PUBLIC EXIT_RUNTIME 1 COMPILE_AND_LINK)
#    em_setting_target(${Target} PUBLIC LINKABLE 0 LINK)
#    em_setting_target(${Target} PUBLIC EXPORTED_FUNCTIONS ['_main'] LINK)
#    em_setting_target(${Target} PUBLIC EXTRA_EXPORTED_RUNTIME_METHODS ['callMain'] LINK)
#    target_link_options(${Target} PUBLIC "SHELL:--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/data@/data")
#    #    target_link_options(${Target} PUBLIC "SHELL:--shell-file ${CMAKE_SOURCE_DIR}/shell/runtime/shell.html")
#    set(TargetBuild "${Target}_Shell_Build")
#    set(TargetCopy "${Target}_Shell_Copy")
#    add_custom_target(
#            ${TargetBuild}
#            node ./.yarn/releases/yarn-berry.cjs build
#            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/shell
#            BYPRODUCTS runtime/index.js runtime/index.js.map
#    )
#    add_custom_target(
#            ${TargetCopy}
#            ${CMAKE_COMMAND} -E copy runtime/index.js ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/index.js
#            COMMAND ${CMAKE_COMMAND} -E copy runtime/index.js.map ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/index.js.map
#            COMMAND ${CMAKE_COMMAND} -E copy shell.html ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${Target}.html
#            DEPENDS ${TargetBuild}
#            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/shell
#    )
#    add_dependencies(${Target} ${TargetCopy} ${TargetBuild})
#endfunction(em_make_executable)
