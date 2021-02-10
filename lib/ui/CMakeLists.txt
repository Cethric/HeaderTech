cmake_minimum_required(VERSION 3.17)
project(HeaderTech_UserInterface)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_UserInterface_SRC
        src/UIIncludes.cpp
)

set(
        HeaderTech_UserInterface_INC
        inc/UIIncludes.h

        inc/ImGuiSurface.h)

add_library(HeaderTech_UserInterface STATIC ${HeaderTech_UserInterface_SRC} ${HeaderTech_UserInterface_INC})
target_include_directories(HeaderTech_UserInterface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_UserInterface PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_UserInterface PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_UserInterface PUBLIC HeaderTech_Logging HeaderTech_Profiler HeaderTech_Events HeaderTech_Config HeaderTech_FileSystem HeaderTech_Window)
target_link_libraries(HeaderTech_UserInterface PUBLIC imgui::imgui)
