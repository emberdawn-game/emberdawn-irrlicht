cmake_minimum_required(VERSION 3.16...3.22)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

option(USE_OPENGL "Build OpenGL renderer" ON)

if(USE_OPENGL)
	list(APPEND VCPKG_MANIFEST_FEATURES opengl)
endif()

option(USE_OGLES2 "Build OpenGL ES 2 renderer" OFF)

project(emberdawn-irrlicht VERSION 1.9.0
	DESCRIPTION "A fork of the Irrlicht 3D engine, specifically for Emberdawn"
	LANGUAGES CXX)
SET(PROJECT_VERSION_PRERELEASE "dev")

if(PROJECT_VERSION_PRERELEASE)
	set(PROJECT_VERSION "${PROJECT_VERSION}-${PROJECT_VERSION_PRERELEASE}")
endif()

include(GNUInstallDirs)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(include)

add_subdirectory(src)

option(BUILD_EXAMPLES "Build example applications" FALSE)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

# Export a file that describes the targets that emberdawn-irrlicht creates.
# The file is placed in the location FILE points to, where CMake can easily
# locate it by pointing CMAKE_PREFIX_PATH to this project root.
export(EXPORT emberdawn-irrlicht-export
	FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/emberdawn-irrlicht-targets.cmake"
	NAMESPACE EmberdawnIrrlicht::
)

# Installation of CMake target and configuration files.
install(EXPORT emberdawn-irrlicht-export
	FILE emberdawn-irrlicht-targets.cmake
	NAMESPACE EmberdawnIrrlicht::
	DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/emberdawn-irrlicht"
)

include(CMakePackageConfigHelpers)
configure_package_config_file("${PROJECT_SOURCE_DIR}/Config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/emberdawn-irrlicht-config.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/emberdawn-irrlicht"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/emberdawn-irrlicht-config-version.cmake"
	COMPATIBILITY AnyNewerVersion
)

install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/emberdawn-irrlicht-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/emberdawn-irrlicht-config-version.cmake"
	DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/emberdawn-irrlicht"
)
