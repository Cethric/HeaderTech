cmake_minimum_required(VERSION 3.19)
project(HeaderTech VERSION 0.0.1.0 DESCRIPTION "HeaderTech Project" HOMEPAGE_URL "https://cehtric.github.io" LANGUAGES CXX C)

enable_testing()

set(
        CMAKE_PREFIX_PATH
        ${CMAKE_PREFIX_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)
set(
        CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

include(Setup)
include(Version)
include(Library)
include(Executable)
include(Test)
include(Install)

add_subdirectory(ext/)
add_subdirectory(lib/)
add_subdirectory(app/)

feature_summary(INCLUDE_QUIET_PACKAGES QUIET_ON_EMPTY WHAT ALL)

FinaliseInstall()
