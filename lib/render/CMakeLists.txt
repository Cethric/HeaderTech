cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Render)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Render_SRC
        src/Render.cpp
)

set(
        HeaderTech_Render_INC
        # Rendering
        inc/Render.h
        inc/RenderContext.inl
        inc/RenderObject.h
        inc/RenderSurface.h
        inc/scene/SceneGraphRenderManagement.h

        # Rendering APIs
        inc/api/RenderContextApi.h
        inc/api/RenderContextApi.inl
        inc/api/BaseRenderContextApi.h

        inc/api/opengl/OpenGLRenderContextApi.h
        inc/api/opengl/OpenGLRenderContextApi.inl
        inc/scene/SceneGraphRenderManagement.inl
        inc/api/RenderFramebuffer.h
        inc/api/RenderFramebuffer.inl
        inc/api/opengl/OpenGLRenderFramebuffer.h
        inc/api/opengl/OpenGLRenderFramebuffer.inl
        inc/api/opengl/OpenGLDebugGui.inl
)

add_library(HeaderTech_Render STATIC ${HeaderTech_Render_SRC} ${HeaderTech_Render_INC})
target_include_directories(HeaderTech_Render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Render PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Render PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Render PUBLIC HeaderTech_Logging HeaderTech_Profiler HeaderTech_Events HeaderTech_Config HeaderTech_Window HeaderTech_FileSystem)
target_link_libraries(HeaderTech_Render PUBLIC glfw glad)
