cmake_minimum_required(VERSION 3.19)
project(TEMPLATE VERSION 0.0.1.0 DESCRIPTION "HeaderTech Template Application" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

set(
        TEMPLATE_SRC
        src/main.cpp
)

set(
        TEMPLATE_INC
)

add_executable(TEMPLATE ${TEMPLATE_SRC} ${TEMPLATE_INC})
target_include_directories(
        TEMPLATE
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
        $<INSTALL_INTERFACE:include/>
)

ConfigureExecutable(TEMPLATE 0 0 1 "+dev")