add_executable(CheckVersion CheckVersion.cpp)
target_link_libraries(CheckVersion PRIVATE Common)
RegisterTests(CheckVersion)
