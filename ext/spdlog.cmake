set(SPDLOG_BUILD_ALL OFF CACHE INTERNAL "" FORCE)
set(SPDLOG_BUILD_SHARED ON CACHE INTERNAL "" FORCE)
set(SPDLOG_ENABLE_PCH ON CACHE INTERNAL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE INTERNAL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE_HO OFF CACHE INTERNAL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(SPDLOG_BUILD_TESTS_HO OFF CACHE INTERNAL "" FORCE)
set(SPDLOG_BUILD_BENCH OFF CACHE INTERNAL "" FORCE)
set(SPDLOG_SANITIZE_ADDRESS OFF CACHE INTERNAL "" FORCE)
set(SPDLOG_BUILD_WARNINGS ON CACHE INTERNAL "" FORCE)
set(SPDLOG_INSTALL OFF CACHE INTERNAL "" FORCE)
set(SPDLOG_FMT_EXTERNAL ON CACHE INTERNAL "" FORCE)
set(SPDLOG_FMT_EXTERNAL_HO OFF CACHE INTERNAL "" FORCE)
set(SPDLOG_NO_EXCEPTIONS OFF CACHE INTERNAL "" FORCE)
add_subdirectory(spdlog/ EXCLUDE_FROM_ALL)

# lib spdlog::spdlog
