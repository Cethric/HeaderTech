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
        inc/ecs/ECS.h
        inc/ecs/EntityBuilder.h
        inc/ecs/System.h
        inc/ecs/Component.h
        inc/ecs/EntityCollection.h
        inc/ecs/EntityCollection.inl
        inc/ecs/Entity.h
        inc/ecs/EntityBuilder.inl
        inc/ecs/EntitySet.h
        inc/ecs/Entity.inl
        inc/ecs/EntityComponentView.h
        inc/ecs/EntityComponentView.inl
        inc/ecs/EntitySet.inl
)

add_library(HeaderTech_Scene STATIC ${HeaderTech_Scene_SRC} ${HeaderTech_Scene_INC})
target_include_directories(HeaderTech_Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_Scene PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_Scene PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_Scene PUBLIC hashmap::hashmap)
target_link_libraries(HeaderTech_Scene PUBLIC HeaderTech_Core HeaderTech_Logging HeaderTech_Profiler HeaderTech_Render)
