configure_file(
        ${PROJECT_SOURCE_DIR}/include/IrrCmakeConfigured.h.in
        ${PROJECT_BINARY_DIR}/include/IrrCmakeConfigured.h)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" "${PROJECT_BINARY_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/emberdawn-irrlicht"
        FILES_MATCHING PATTERN "*.h")