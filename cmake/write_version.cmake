set(VERSION_SOURCE_FILE ${CMAKE_SOURCE_DIR}/cmake/version.h.in)

function(ConfigureVersion TargetName TargetVersionFile VersionDir)
    file(READ ${TargetVersionFile} VersionContents)
    list(GET VersionContents 0 VersionMajor)
    list(GET VersionContents 1 VersionMinor)
    list(GET VersionContents 2 VersionPatch)
    list(GET VersionContents 3 VersionMeta)
    configure_file(
            ${VERSION_SOURCE_FILE}
            ${VersionDir}/${TargetName}_Version.h
            @ONLY
            NO_SOURCE_PERMISSIONS
            NEWLINE_STYLE CRLF
    )
endfunction(ConfigureVersion)
