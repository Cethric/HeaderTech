set(FMT_PEDANTIC OFF CACHE INTERNAL "" FORCE)
set(FMT_WERROR ON CACHE INTERNAL "" FORCE)
set(FMT_DOC OFF CACHE INTERNAL "" FORCE)
set(FMT_INSTALL OFF CACHE INTERNAL "" FORCE)
set(FMT_TEST OFF CACHE INTERNAL "" FORCE)
set(FMT_FUZZ OFF CACHE INTERNAL "" FORCE)
set(FMT_CUDA_TEST OFF CACHE INTERNAL "" FORCE)
set(FMT_OS ON CACHE INTERNAL "" FORCE)

if (MSVC)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_definitions(-DFMT_EXCEPTIONS=0)
        set(FMT_OS OFF CACHE INTERNAL "" FORCE)
        set(FMT_PEDANTIC ON CACHE INTERNAL "" FORCE)
        set(FMT_WERROR OFF CACHE INTERNAL "" FORCE)
    endif ()
endif ()

add_subdirectory(fmt/ EXCLUDE_FROM_ALL)

# lib fmt::fmt
