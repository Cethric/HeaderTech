function(FinaliseInstall)
    set(CPACK_GENERATOR NSIS64)
    set(CPACK_PACKAGE_NAME "HeaderTech")
    set(CPACK_PACKAGE_VENDOR "Blake Rogan")

    include(CPack)
endfunction(FinaliseInstall)