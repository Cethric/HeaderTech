cmake_minimum_required(VERSION 3.17)
project(HeaderTech_Scene)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_Scene_SRC
        src/SceneGraph.cpp
)

set(
        HeaderTech_Scene_INC
        inc/Scene.h
        inc/SceneGraph.h
        inc/SceneGraph.inl
        inc/SceneManager.h
        inc/SceneManager.inl
        inc/SceneGraphManagement.inl
)

add_library(HeaderTech_Scene STATIC ${HeaderTech_Scene_SRC} ${HeaderTech_Scene_INC})
target_include_directories(HeaderTech_Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Scene PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Scene PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Scene PUBLIC hashmap::hashmap imgui::imgui)
target_link_libraries(HeaderTech_Scene PUBLIC HeaderTech_Core HeaderTech_Logging HeaderTech_Profiler HeaderTech_Render HeaderTech_EntityComponentSystem HeaderTech_UserInterface)
