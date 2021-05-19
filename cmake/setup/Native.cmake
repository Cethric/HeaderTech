include_guard(GLOBAL)

set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)

set(CMAKE_UNITY_BUILD ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS 11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS 20)

set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_RC_CREATE_SHARED_LIBRARY ON)