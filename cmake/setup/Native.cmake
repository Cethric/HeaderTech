include_guard(GLOBAL)

set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)

set(CMAKE_UNITY_BUILD ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_RC_CREATE_SHARED_LIBRARY ON)

set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_C_VISIBILITY_PRESET default)
set(CMAKE_VISIBILITY_INLINES_HIDDEN OFF)


check_cxx_compiler_flag(-std=c++20 has_std_20_flag)
check_cxx_compiler_flag(-std=c++2a has_std_2a_flag)
check_cxx_compiler_flag(/std:c++20 has_msvc_20_flag)
check_cxx_compiler_flag(/std:c++latest has_msvc_latest_flag)

if (has_std_20_flag)
    set(CXX_STANDARD_FLAG -std=c++20)
elseif (has_std_2a_flag)
    set(CXX_STANDARD_FLAG -std=c++2a)
elseif (has_msvc_20_flag)
    set(CXX_STANDARD_FLAG /std:c++20)
elseif (has_msvc_latest_flag)
    set(CXX_STANDARD_FLAG /std:c++latest)
endif ()

