set(PHMAP_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(PHMAP_BUILD_EXAMPLES OFF CACHE INTERNAL "" FORCE)
#add_subdirectory(hashmap/ EXCLUDE_FROM_ALL)

add_library(parallel_hashmap INTERFACE)
target_include_directories(
        parallel_hashmap
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hashmap/parallel_hashmap/>
        $<INSTALL_INTERFACE:include/hashmap/parallel_hashmap/>
)

add_library(hashmap::hashmap ALIAS parallel_hashmap)

RegisterLibrary(parallel_hashmap INTERFACE)
# lib hashmap::hashmap
