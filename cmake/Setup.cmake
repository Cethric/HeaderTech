include_guard(GLOBAL)

include(GenerateExportHeader)
include(GNUInstallDirs)
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)
include(InstallRequiredSystemLibraries)
include(FeatureSummary)
include(FetchContent)

if (EMSCRIPTEN)
    include(setup/Emscripten)
else (EMSCRIPTEN)
    include(setup/Native)
endif (EMSCRIPTEN)

include(setup/Shared)
