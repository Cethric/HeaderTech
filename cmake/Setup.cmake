include_guard(GLOBAL)

if (EMSCRIPTEN)
    include(setup/Emscripten)
else (EMSCRIPTEN)
    include(setup/Native)
endif (EMSCRIPTEN)

include(GenerateExportHeader)
include(GNUInstallDirs)
include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)