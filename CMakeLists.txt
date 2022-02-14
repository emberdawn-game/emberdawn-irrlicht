cmake_minimum_required(VERSION 3.5)

# Set policies up to 3.9 since we want to enable the IPO option
if(${CMAKE_VERSION} VERSION_LESS 3.9)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
	cmake_policy(VERSION 3.9)
endif()

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.15)
	cmake_policy(SET CMP0091 NEW)
endif()

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(EmberdawnIrrlicht
	VERSION 1.9.0
	LANGUAGES CXX
)
set(PROJECT_VERSION_PRERELEASE "alpha.1")
if(PROJECT_VERSION_PRERELEASE)
	set(PROJECT_VERSION "${PROJECT_VERSION}-${PROJECT_VERSION_PRERELEASE}")
	set(${PROJECT_NAME}_VERSION ${PROJECT_VERSION})
	set(${PROJECT_NAME}_VERSION_PRERELEASE ${PROJECT_VERSION_PRERELEASE})
endif()

include(GNUInstallDirs)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

configure_file(
	${PROJECT_SOURCE_DIR}/include/IrrCmakeConfigured.h.in
	${PROJECT_BINARY_DIR}/include/IrrCmakeConfigured.h)

include_directories(${PROJECT_BINARY_DIR}/include)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_subdirectory(source/Irrlicht)

option(BUILD_EXAMPLES "Build example applications" FALSE)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

# Export a file that describes the targets that EmberdawnIrrlicht creates.
# The file is placed in the location FILE points to, where CMake can easily
# locate it by pointing CMAKE_PREFIX_PATH to this project root.
export(EXPORT EmberdawnIrrlicht-export
	FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/EmberdawnIrrlichtTargets.cmake"
	NAMESPACE EmberdawnIrrlicht::
)

# Installation of headers.
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/emberdawn-irrlicht"
)

# Installation of CMake target and configuration files.
install(EXPORT EmberdawnIrrlicht-export
	FILE EmberdawnIrrlichtTargets.cmake
	NAMESPACE EmberdawnIrrlicht::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/EmberdawnIrrlicht"
)

include(CMakePackageConfigHelpers)
configure_package_config_file("${PROJECT_SOURCE_DIR}/Config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/EmberdawnIrrlichtConfig.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/EmberdawnIrrlicht"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/EmberdawnIrrlichtConfigVersion.cmake"
	COMPATIBILITY AnyNewerVersion
)

install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/EmberdawnIrrlichtConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/EmberdawnIrrlichtConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/EmberdawnIrrlicht"
)
