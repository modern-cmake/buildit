include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(buildit_INSTALL_CMAKEDIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/buildit"
    CACHE STRING "Path to buildit cmake files")

set(CONFIG_DIR $<IF:$<CONFIG:Debug>,Debug,Release>)

install(TARGETS buildit_buildit
        EXPORT buildit_Targets

        RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}/${CONFIG_DIR}
        COMPONENT buildit_Runtime

        LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CONFIG_DIR}
        COMPONENT buildit_Runtime
        NAMELINK_COMPONENT buildit_Development

        ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CONFIG_DIR}
        COMPONENT buildit_Development

        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY ${buildit_SOURCE_DIR}/include/ TYPE INCLUDE)

install(EXPORT buildit_Targets
        DESTINATION ${buildit_INSTALL_CMAKEDIR}
        NAMESPACE buildit::
        FILE buildit-config.cmake
        COMPONENT buildit_Development)

write_basic_package_version_file(buildit-config-version.cmake COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/buildit-config-version.cmake
        DESTINATION ${buildit_INSTALL_CMAKEDIR})

set(CPACK_PACKAGE_VENDOR "buildit")
set(CPACK_RESOURCE_FILE_LICENSE "${buildit_SOURCE_DIR}/LICENSE")
if (WIN32)
    set(CPACK_GENERATOR "ZIP")
else ()
    set(CPACK_GENERATOR "TGZ")
endif ()

include(CPack)

