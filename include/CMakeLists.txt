if(USE_OPENGL)
	set(_IRR_COMPILE_WITH_OPENGL_ ON)
endif()

if(USE_OGLES2)
	set(_IRR_COMPILE_WITH_OGLES2_ ON)
endif()

configure_file(IrrCmakeConfigured.h.in "${CMAKE_CURRENT_BINARY_DIR}/IrrCmakeConfigured.h")

add_library(Include INTERFACE)
target_include_directories(Include INTERFACE
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/emberdawn-irrlicht>")

install(TARGETS Include EXPORT emberdawn-irrlicht-export)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/emberdawn-irrlicht"
	FILES_MATCHING PATTERN "*.h")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/IrrCmakeConfigured.h"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/emberdawn-irrlicht")
