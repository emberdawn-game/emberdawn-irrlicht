cmake_minimum_required(VERSION 3.16...3.22)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

option(USE_OPENGL "Build OpenGL renderer" ON)

if(USE_OPENGL)
	list(APPEND VCPKG_MANIFEST_FEATURES opengl)
endif()

option(USE_OGLES2 "Build OpenGL ES 2 renderer" OFF)

option(BUILD_EXAMPLES "Build example applications" FALSE)

project(emberdawn-irrlicht VERSION 1.9.0
	DESCRIPTION "A fork of the Irrlicht 3D engine, specifically for Emberdawn"
	LANGUAGES CXX)
SET(PROJECT_VERSION_PRERELEASE "dev")

if(PROJECT_VERSION_PRERELEASE)
	set(PROJECT_VERSION "${PROJECT_VERSION}-${PROJECT_VERSION_PRERELEASE}")
endif()

add_subdirectory(include)
add_subdirectory(src)

if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
