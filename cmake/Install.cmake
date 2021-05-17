include_guard(GLOBAL)
set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output/install)
set(CMAKE_INSTALL_PREFIX ${OUTPUT_DIRECTORY})

function(FinaliseInstall)

    install(
            EXPORT HeaderTechLibsDebug
            NAMESPACE ht_
            CONFIGURATIONS Debug
            DESTINATION lib/
    )
    install(
            EXPORT_ANDROID_MK HeaderTechLibsDebug
            CONFIGURATIONS Debug
            DESTINATION share/ndk-modules
    )

    install(
            EXPORT HeaderTechLibsRelease
            NAMESPACE ht_
            CONFIGURATIONS Release
            DESTINATION lib/
    )
    install(
            EXPORT_ANDROID_MK HeaderTechLibsRelease
            CONFIGURATIONS Release
            DESTINATION share/ndk-modules
    )

    set(CPACK_GENERATOR NSIS64)
    set(CPACK_PACKAGE_NAME "HeaderTech")
    set(CPACK_PACKAGE_VENDOR "Blake Rogan")

    include(CPack)
endfunction(FinaliseInstall)