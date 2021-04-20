if (EMSCRIPTEN)
    add_library(glfw INTERFACE)
    target_include_directories(glfw INTERFACE ${EMSCRIPTEN_ROOT_PATH}/system/include)
    target_link_libraries(glfw INTERFACE glfw.js)
#    em_setting_target(glfw INTERFACE USE_GLFW 3 COMPILE_AND_LINK)
#    em_setting_target(glfw INTERFACE USE_WEBGL2 1 LINK)
#    em_setting_target(glfw INTERFACE USE_WEBGPU 0 LINK)
#    em_setting_target(glfw INTERFACE MIN_WEBGL_VERSION 2 LINK)
#    em_setting_target(glfw INTERFACE MAX_WEBGL_VERSION 2 LINK)
#    em_setting_target(glfw INTERFACE FULL_ES3 1 LINK)
#    em_setting_target(glfw INTERFACE GL_ASSERTIONS 1 LINK)
#    em_setting_target(glfw INTERFACE TRACE_WEBGL_CALLS 0 LINK)
#    em_setting_target(glfw INTERFACE WEBGL2_BACKWARDS_COMPATIBILITY_EMULATION 0 LINK)
#    em_setting_target(glfw INTERFACE EMULATE_FUNCTION_POINTER_CASTS 0 LINK)
    #    target_link_options(glfw INTERFACE "--pre-js ${EMSCRIPTEN_ROOT_PATH}/src/")
else (EMSCRIPTEN)
    set(BUILD_SHARED_LIBS ON CACHE INTERNAL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "" FORCE)
    set(GLFW_INSTALL OFF CACHE INTERNAL "" FORCE)
    set(GLFW_VULKAN_STATIC OFF CACHE INTERNAL "" FORCE)

    add_subdirectory(glfw/)

    RegisterLibrary(glfw PRIVATE)

endif (EMSCRIPTEN)


add_library(glfw::glfw3 ALIAS glfw)

# lib glfw
