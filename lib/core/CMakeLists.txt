cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Core)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Core_SRC
        src/CoreIncludes.cpp
)

set(
        HeaderTech_Core_INC
        inc/CoreIncludes.h
        inc/WindowTypes.h

        inc/scoped/ScopedGLFW.h

        inc/api/render/RenderContextApi.h
        inc/api/render/RenderFramebuffer.h
        inc/api/render/RenderFramebuffer.inl

        inc/api/window/WindowApi.h
        inc/api/render/RenderApiIncludes.h inc/api/window/WindowApiIncludes.h)

add_library(HeaderTech_Core STATIC ${HeaderTech_Core_SRC} ${HeaderTech_Core_INC})
target_include_directories(HeaderTech_Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Core PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Core PUBLIC glfw::glfw3)
target_link_libraries(HeaderTech_Core PUBLIC HeaderTech_Logging HeaderTech_Config HeaderTech_Events)
