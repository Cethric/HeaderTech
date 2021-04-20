cmake_minimum_required(VERSION 3.17)
project(imgui)

set(CMAKE_CXX_STANDARD 20)

set(
        ImGui_SRC
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
)

set(
        ImGui_Inc
        imgui/imconfig.h
        imgui/imgui.h
        imgui/imgui_internal.h
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
)

set(
        ImGui_Misc_Code
        imgui/misc/cpp/imgui_stdlib.cpp
        imgui/misc/cpp/imgui_stdlib.h
        imgui/misc/debuggers/imgui.gdb
        imgui/misc/debuggers/imgui.natstepfilter
        imgui/misc/debuggers/imgui.natvis
)


set(
        ImGuiBackend_SRC
        imgui/backends/imgui_impl_glfw.cpp
        imgui_backends/ImGui_OpenGL3.cpp
)

set(
        ImGuiBackend_Inc
        imgui/backends/imgui_impl_glfw.h
        imgui_backends/ImGui_OpenGL3.h
)

add_library(ImGui SHARED ${ImGui_SRC} ${ImGui_Inc} ${ImGui_Misc_Code} ${ImGuiBackend_SRC} ${ImGuiBackend_Inc})
target_include_directories(
        ImGui
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/>
            $<INSTALL_INTERFACE:include/imgui/>
            $<INSTALL_INTERFACE:include/imgui/misc/cpp/>
        PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/>
            $<INSTALL_INTERFACE:include/imgui/>
            $<INSTALL_INTERFACE:include/imgui/misc/cpp/>
)

# ImGui Backends

target_include_directories(
        ImGui
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui_backends/>
            $<INSTALL_INTERFACE:include/imgui/backends/>
            $<INSTALL_INTERFACE:include/imgui_backends/>
        PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui_backends/>
            $<INSTALL_INTERFACE:include/imgui/backends/>
            $<INSTALL_INTERFACE:include/imgui_backends/>
)

target_link_libraries(ImGui PRIVATE glad::glad)
target_link_libraries(ImGui PRIVATE glfw::glfw3)
target_compile_definitions(ImGui PRIVATE -DGLFW_INCLUDE_NONE=1)


add_executable(ImGuiFontCompressor imgui/misc/fonts/binary_to_compressed_c.cpp)


add_library(imgui::imgui ALIAS ImGui)

RegisterLibrary(ImGui PRIVATE)

# lib imgui::imgui
