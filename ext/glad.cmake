set(BUILD_SHARED_LIBS ON CACHE INTERNAL "" FORCE)
add_subdirectory(glad/cmake EXCLUDE_FROM_ALL)

glad_add_library(
        glad
        STATIC
        EXCLUDE_FROM_ALL
        MERGE
        MX
        ALIAS
        QUIET
        KEEP_SOURCES
        LOCATION "${CMAKE_CURRENT_BINARY_DIR}/glad"
        LANGUAGE C
        API gl:core=4.6
)

# lib glad
