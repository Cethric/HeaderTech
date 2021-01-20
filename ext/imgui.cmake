cmake_minimum_required(VERSION 3.17)
project(imgui)

set(CMAKE_CXX_STANDARD 20)

set(
        ImGui_SRC
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_tables.cpp
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
        imgui/misc/natvis/imgui.natvis
)

add_library(ImGui STATIC ${ImGui_SRC} ${ImGui_Inc} ${ImGui_Misc_Code})
target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/)
target_include_directories(ImGui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui/)
target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/)
target_include_directories(ImGui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/)
target_link_libraries(ImGui PUBLIC glad)

add_executable(ImGuiFontCompressor WIN32 imgui/misc/fonts/binary_to_compressed_c.cpp)


add_library(imgui::imgui ALIAS ImGui)

# lib imgui::imgui
