cmake_minimum_required(VERSION 3.17)
project(HeaderTech_EntityComponentSystem)


set(CMAKE_CXX_STANDARD 20)

set(
        HeaderTech_EntityComponentSystem_SRC
        src/EntityComponentSystem.cpp
)

set(
        HeaderTech_EntityComponentSystem_INC
        inc/EntityComponentSystem.h
        inc/EntityBuilder.h
        inc/Component.h
        inc/EntityCollection.h
        inc/EntityCollection.inl
        inc/Entity.h
        inc/EntityBuilder.inl
        inc/EntitySet.h
        inc/Entity.inl
        inc/EntityComponentView.h
        inc/EntityComponentView.inl
        inc/EntitySet.inl
)

add_library(HeaderTech_EntityComponentSystem STATIC ${HeaderTech_EntityComponentSystem_SRC} ${HeaderTech_EntityComponentSystem_INC})
target_include_directories(HeaderTech_EntityComponentSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
target_include_directories(HeaderTech_EntityComponentSystem PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc/)
target_include_directories(HeaderTech_EntityComponentSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}src/)
target_link_libraries(HeaderTech_EntityComponentSystem PUBLIC hashmap::hashmap ctti::ctti)
target_link_libraries(HeaderTech_EntityComponentSystem PUBLIC HeaderTech_Core HeaderTech_Logging HeaderTech_Profiler)
