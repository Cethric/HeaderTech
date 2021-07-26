set(JSON_BuildTests OFF CACHE INTERNAL "" FORCE)
set(JSON_Install OFF CACHE INTERNAL "" FORCE)
set(JSON_MultipleHeaders ON CACHE INTERNAL "" FORCE)
set(JSON_ImplicitConversions OFF CACHE INTERNAL "" FORCE)

add_subdirectory(json/ EXCLUDE_FROM_ALL)

add_library(json::json ALIAS nlohmann_json)

RegisterLibrary(nlohmann_json INTERFACE)

# lib json::json
