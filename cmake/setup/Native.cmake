include_guard(GLOBAL)

set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)

if (MSVC)
    set(CMAKE_SYSTEM_VERSION 10.0)
endif (MSVC)

set(CMAKE_UNITY_BUILD ON)
set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_RC_CREATE_SHARED_LIBRARY ON)

set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_C_VISIBILITY_PRESET default)
set(CMAKE_VISIBILITY_INLINES_HIDDEN OFF)


check_cxx_compiler_flag(-std=c++20 has_std_cxx_20_flag)
check_cxx_compiler_flag(-std=c++2a has_std_cxx_2a_flag)
check_cxx_compiler_flag(/std:c++20 has_msvc_cxx_20_flag)
check_cxx_compiler_flag(/std:c++latest has_msvc_cxx_latest_flag)

if (has_std_cxx_20_flag)
    set(CMAKE_CXX_STANDARD 20)
    set(CXX_STANDARD_FLAG -std=c++20)
elseif (has_std_cxx_2a_flag)
    set(CMAKE_CXX_STANDARD 20)
    set(CXX_STANDARD_FLAG -std=c++2a)
elseif (has_msvc_cxx_20_flag)
    set(CMAKE_CXX_STANDARD 20)
    set(CXX_STANDARD_FLAG /std:c++20 /Zc:__cplusplus /cgthreads8)
elseif (has_msvc_cxx_latest_flag)
    set(CMAKE_CXX_STANDARD 20)
    set(CXX_STANDARD_FLAG /std:c++latest /Zc:__cplusplus /cgthreads8)
endif ()

set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#check_cxx_compiler_flag(-std=c2x has_std_c_2x_flag)
#check_cxx_compiler_flag(-std=c18 has_std_c_18_flag)
#check_cxx_compiler_flag(-std=c17 has_std_c_17_flag)
check_cxx_compiler_flag(-std=c11 has_std_c_11_flag)
#check_cxx_compiler_flag(/std:c17 has_msvc_c_17_flag)
check_cxx_compiler_flag(/std:c11 has_msvc_c_11_flag)

#if (has_std_c_2x_flag)
#    set(CMAKE_C_STANDARD 2x)
#    set(C_STANDARD_FLAG -std=c2x)
#if (has_std_c_18_flag)
#    set(CMAKE_C_STANDARD 18)
#    set(C_STANDARD_FLAG -std=c18)
#if (has_std_c_17_flag)
#    set(CMAKE_C_STANDARD 17)
#    set(C_STANDARD_FLAG -std=c17)
if (has_std_c_11_flag)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_EXTENSIONS ON)
    set(C_STANDARD_FLAG -std=c11)
#elseif (has_msvc_c_17_flag)
#    set(CMAKE_C_STANDARD 17)
#    set(CMAKE_C_EXTENSIONS ON)
#    set(C_STANDARD_FLAG /std:17)
elseif (has_msvc_c_11_flag)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_EXTENSIONS ON)
    set(C_STANDARD_FLAG /std:11)
endif ()

set(CMAKE_C_STANDARD_REQUIRED ON)
