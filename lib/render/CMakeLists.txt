cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Render)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Render_SRC
        src/RenderIncludes.cpp
)

set(
        HeaderTech_Render_INC
        # Rendering
        inc/RenderIncludes.h
        inc/RenderContext.inl
        inc/RenderObject.h
        inc/RenderSurface.h

        # Rendering APIs
        inc/api/RenderContextApiIncludes.h

        # Scene
        inc/scene/SceneGraphRenderManagement.inl
        inc/scene/SceneGraphRenderManagement.h

        # OpenGL
        inc/api/opengl/OpenGLRenderContextApi.h
        inc/api/opengl/OpenGLRenderContextApi.inl
        inc/api/opengl/OpenGLRenderFramebuffer.h
        inc/api/opengl/OpenGLRenderFramebuffer.inl
        inc/api/opengl/OpenGLDebugGui.inl
)

add_library(HeaderTech_Render STATIC ${HeaderTech_Render_SRC} ${HeaderTech_Render_INC})
target_include_directories(HeaderTech_Render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Render PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Render PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Render PUBLIC HeaderTech_Logging HeaderTech_Profiler HeaderTech_Events HeaderTech_Config HeaderTech_Window HeaderTech_FileSystem HeaderTech_Runtime HeaderTech_Core)
target_link_libraries(HeaderTech_Render PUBLIC glfw::glfw3 glad::glad imgui::imgui)


generate_export_header(
        HeaderTech_Render
        EXPORT_FILE_NAME inc/HeaderTech_Render_Export.h
)
