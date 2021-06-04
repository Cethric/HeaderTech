include_guard(GLOBAL)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG devel
        GIT_SHALLOW 1
        GIT_PROGRESS 1
)

FetchContent_MakeAvailable(Catch2)

set_property(
        TARGET Catch2
        PROPERTY UNITY_BUILD OFF
)

set(
        CMAKE_PREFIX_PATH
        ${CMAKE_PREFIX_PATH}
        "${catch2_SOURCE_DIR}/extras/"
)
set(
        CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${catch2_SOURCE_DIR}/extras/"
)

include(CTest)
include(Catch)

function(RegisterTests Target)
    target_link_libraries(${Target} PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
    catch_discover_tests(${Target})
endfunction(RegisterTests)
