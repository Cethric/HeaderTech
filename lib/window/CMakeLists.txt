cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Window)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Window_SRC
        src/Window.cpp
)

set(
        HeaderTech_Window_INC
        # Window Events
        inc/events/WindowPositionEvent.h
        inc/events/WindowSizeEvent.h
        inc/events/WindowCloseEvent.h
        inc/events/WindowRefreshEvent.h
        inc/events/WindowFocusEvent.h
        inc/events/WindowIconifyEvent.h
        inc/events/WindowMaximizeEvent.h
        inc/events/FramebufferSizeEvent.h
        inc/events/WindowContentScaleEvent.h
        inc/events/MouseButtonEvent.h
        inc/events/CursorPositionEvent.h
        inc/events/CursorEnterEvent.h
        inc/events/ScrollEvent.h
        inc/events/KeyEvent.h
        inc/events/CharEvent.h
        inc/events/CharModsEvent.h
        inc/events/FileDropEvent.h
        # Windowing
        inc/Window.h
        inc/WindowTypes.h
        inc/WindowBase.h
        inc/WindowBase.inl
        # Window APIs
        inc/api/WindowApi.h
        inc/api/WindowApi.inl
        inc/api/BaseWindowApi.h
        inc/api/opengl/OpenGLWindowApi.h
        inc/api/opengl/OpenGLWindowApi.inl
        inc/api/opengl/OpenGLWindowApiEvents.inl
        inc/api/GLFWKeyMapping.h)

add_library(HeaderTech_Window STATIC ${HeaderTech_Window_SRC} ${HeaderTech_Window_INC})
target_include_directories(HeaderTech_Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Window PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Window PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Window PUBLIC HeaderTech_Logging HeaderTech_Profiler HeaderTech_Events HeaderTech_Config HeaderTech_Render)
target_link_libraries(HeaderTech_Window PUBLIC glfw::glfw3)
