if (USE_OPENGL)
	set(_IRR_COMPILE_WITH_OPENGL_ ON)
endif()

if (USE_OGLES2)
	set(_IRR_COMPILE_WITH_OGLES2_ ON)
endif()

configure_file(IrrCmakeConfigured.h.in "${CMAKE_CURRENT_BINARY_DIR}/IrrCmakeConfigured.h")

add_library(emberdawn-irrlicht-headers INTERFACE)
target_include_directories(emberdawn-irrlicht-headers INTERFACE . "${CMAKE_CURRENT_BINARY_DIR}")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/emberdawn-irrlicht"
	FILES_MATCHING PATTERN "*.h")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/IrrCmakeConfigured.h"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/emberdawn-irrlicht")
