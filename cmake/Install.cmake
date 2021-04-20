include_guard(GLOBAL)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/cmake-install-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID})

function(FinaliseInstall)

    install(
            EXPORT HeaderTechLibsDebug
            NAMESPACE ht_
            CONFIGURATIONS Debug
            DESTINATION Debug/lib/
    )
    install(
            EXPORT_ANDROID_MK HeaderTechLibsDebug
            CONFIGURATIONS Debug
            DESTINATION Debug/share/ndk-modules
    )

    install(
            EXPORT HeaderTechLibsRelease
            NAMESPACE ht_
            CONFIGURATIONS Release
            DESTINATION Release/lib/
    )
    install(
            EXPORT_ANDROID_MK HeaderTechLibsRelease
            CONFIGURATIONS Release
            DESTINATION Release/share/ndk-modules
    )

    set(CPACK_GENERATOR NSIS64)
    set(CPACK_PACKAGE_NAME "HeaderTech")
    set(CPACK_PACKAGE_VENDOR "Blake Rogan")

    include(CPack)
endfunction(FinaliseInstall)