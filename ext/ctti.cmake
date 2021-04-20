set(CTTI_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(CTTI_BUILD_EXAMPLES OFF CACHE INTERNAL "" FORCE)
add_subdirectory(ctti/ EXCLUDE_FROM_ALL)

add_library(ctti::ctti ALIAS ctti)

#RegisterLibrary(ctti INTERFACE)

# lib ctti::ctti
