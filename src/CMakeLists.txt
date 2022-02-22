find_package(JPEG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(libpng CONFIG REQUIRED)

if(USE_OPENGL)
	find_package(OpenGL REQUIRED)
	find_path(OPENGL_REGISTRY_INCLUDE_DIRS GL/glcorearb.h)
endif()

if(USE_OGLES2)
	find_package(OpenGLES2 REQUIRED)
endif()

# Compiler flags

add_definitions(-DIRRLICHT_EXPORTS)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-D_DEBUG)
endif()
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

if(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")

	add_compile_options(-Wall -pipe -fno-exceptions -fno-rtti)

	# Enable SSE for floating point math on 32-bit x86 by default
	# reasoning see minetest issue #11810 and https://gcc.gnu.org/wiki/FloatingPointMath
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		include(CheckCXXSourceCompiles)
		check_cxx_source_compiles("#ifndef __i686__\n#error\n#endif\nint main(){}" IS_I686)
		if(IS_I686)
			message(STATUS "Detected Intel x86: using SSE instead of x87 FPU")
			add_compile_options(-mfpmath=sse -msse)
		endif()
	endif()

elseif(MSVC)
	add_compile_options(/GR-)

	# Enable SSE for floating point math on 32-bit x86 by default
	# reasoning see minetest issue #11810 and https://gcc.gnu.org/wiki/FloatingPointMath
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		add_compile_options(/arch:SSE)
	endif()
endif()

# To configure the features available in this Irrlicht build please edit
# include/IrrLegacyCompileConfig.h and re-run CMake from a clean state
include(CheckSymbolExists)
set(CMAKE_REQUIRED_INCLUDES ${PROJECT_SOURCE_DIR}/include)
unset(OGLES1_ENABLED CACHE)
unset(XINPUT2_ENABLED CACHE)

check_symbol_exists(_IRR_COMPILE_WITH_OGLES1_ "IrrLegacyCompileConfig.h" OGLES1_ENABLED)
if(OGLES1_ENABLED)
	# only tested on Android, probably works on Linux (is this needed anywhere else?)
	find_library(OPENGLES_LIBRARY NAMES GLESv1_CM REQUIRED)
	find_library(EGL_LIBRARY NAMES EGL REQUIRED)

	message(STATUS "Found OpenGLES: ${OPENGLES_LIBRARY}")
endif()
check_symbol_exists(_IRR_LINUX_X11_XINPUT2_ "IrrLegacyCompileConfig.h" XINPUT2_ENABLED)
if(XINPUT2_ENABLED)
	find_library(XINPUT_LIBRARY Xi REQUIRED)
endif()

# Platform-specific libs

if(ANDROID)
	enable_language(C)
	add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
elseif(APPLE)
	find_library(COCOA_LIB Cocoa REQUIRED)
	find_library(IOKIT_LIB IOKit REQUIRED)

	add_definitions(-DGL_SILENCE_DEPRECATION)
else()
	# Unix probably
	find_package(X11 REQUIRED)
endif()

set(link_includes
	"${CMAKE_CURRENT_SOURCE_DIR}"

	"${JPEG_INCLUDE_DIR}"

	${OPENGL_INCLUDE_DIR}
	${OPENGL_REGISTRY_INCLUDE_DIRS}
	${OPENGLES2_INCLUDE_DIR}
	${EGL_INCLUDE_DIR}

	"$<$<PLATFORM_ID:Android>:${ANDROID_NDK}/sources/android/native_app_glue>"
	${X11_INCLUDE_DIR}
)

set(link_libs
	"ZLIB::ZLIB"
	"${JPEG_LIBRARIES}"
	"$<IF:$<TARGET_EXISTS:png>,png,png_static>"

	${OPENGL_LIBRARIES}
	${OPENGLES_LIBRARY}
	${OPENGLES2_LIBRARIES}
	${EGL_LIBRARY}
	${XINPUT_LIBRARY}

	"$<$<PLATFORM_ID:Android>:native_app_glue -landroid -llog>"
	${COCOA_LIB}
	${IOKIT_LIB}
	"$<$<PLATFORM_ID:Windows>:gdi32>"
	"$<$<PLATFORM_ID:Windows>:winmm>"
	${X11_X11_LIB}
	${X11_Xxf86vm_LIB}
)

# Source files

set(IRRMESHLOADER
	scene/mesh/loader/CB3DMeshFileLoader.cpp
	scene/mesh/loader/COBJMeshFileLoader.cpp
	scene/mesh/loader/CXMeshFileLoader.cpp
)

add_library(IRRMESHOBJ OBJECT
	scene/mesh/CSkinnedMesh.cpp
	scene/mesh/CBoneSceneNode.cpp
	scene/mesh/CMeshSceneNode.cpp
	scene/mesh/CAnimatedMeshSceneNode.cpp
	${IRRMESHLOADER}
)

add_library(IRROBJ OBJECT
	scene/CBillboardSceneNode.cpp
	scene/CCameraSceneNode.cpp
	scene/CDummyTransformationSceneNode.cpp
	scene/CEmptySceneNode.cpp
	scene/CMeshManipulator.cpp
	scene/CSceneCollisionManager.cpp
	scene/CSceneManager.cpp
	scene/CMeshCache.cpp
	scene/CDefaultSceneNodeFactory.cpp
)

set(IRRDRVROBJ
	video/driver/CNullDriver.cpp
	video/driver/COpenGLCacheHandler.cpp
	video/driver/COpenGLDriver.cpp
	video/driver/COpenGLShaderMaterialRenderer.cpp
	video/driver/COpenGLSLMaterialRenderer.cpp
	video/driver/COpenGLExtensionHandler.cpp
	video/driver/COGLESDriver.cpp
	video/driver/COGLESExtensionHandler.cpp
	video/driver/COGLES2Driver.cpp
	video/driver/COGLES2ExtensionHandler.cpp
	video/driver/COGLES2FixedPipelineRenderer.cpp
	video/driver/COGLES2MaterialRenderer.cpp
	video/driver/COGLES2Renderer2D.cpp
	video/driver/CWebGL1Driver.cpp
	video/driver/CGLXManager.cpp
	video/driver/CWGLManager.cpp
	video/driver/CEGLManager.cpp
)

set(IRRIMAGEOBJ
	video/image/CColorConverter.cpp
	video/image/CImage.cpp
	video/image/CImageLoaderBMP.cpp
	video/image/CImageLoaderJPG.cpp
	video/image/CImageLoaderPNG.cpp
	video/image/CImageLoaderTGA.cpp
	video/image/CImageWriterJPG.cpp
	video/image/CImageWriterPNG.cpp
)

add_library(IRRVIDEOOBJ OBJECT
	video/driver/CVideoModeList.cpp
	video/CFPSCounter.cpp
	${IRRDRVROBJ}
	${IRRIMAGEOBJ}
)

add_library(IRRIOOBJ OBJECT
	io/CFileList.cpp
	io/CFileSystem.cpp
	io/CLimitReadFile.cpp
	io/CMemoryFile.cpp
	io/CReadFile.cpp
	io/CWriteFile.cpp
	io/CZipReader.cpp
	io/CMountPointReader.cpp
	io/CAttributes.cpp
)

add_library(IRROTHEROBJ OBJECT
	video/driver/CIrrDeviceSDL.cpp
	video/driver/CIrrDeviceLinux.cpp
	video/driver/CIrrDeviceConsole.cpp
	video/driver/CIrrDeviceStub.cpp
	video/driver/CIrrDeviceWin32.cpp
	video/driver/CIrrDeviceFB.cpp
	CLogger.cpp
	COSOperator.cpp
	Irrlicht.cpp
	os.cpp
	leakHunter.cpp
	CProfiler.cpp
)

if(ANDROID)
	target_sources(IRROTHEROBJ PRIVATE
		Android/CIrrDeviceAndroid.cpp
		Android/CAndroidAssetReader.cpp
		Android/CAndroidAssetFileArchive.cpp
		Android/CKeyEventWrapper.cpp
	)
elseif(APPLE)
	# Build all IRROTHEROBJ sources as objc++, including the .cpp's
	set_target_properties(IRROTHEROBJ PROPERTIES COMPILE_OPTIONS "-xobjective-c++")
	target_sources(IRROTHEROBJ PRIVATE
		video/driver/CIrrDeviceOSX.mm
		video/driver/CNSOGLManager.mm
	)
endif()

add_library(IRRGUIOBJ OBJECT
	gui/CGUIButton.cpp
	gui/CGUICheckBox.cpp
	gui/CGUIComboBox.cpp
	gui/CGUIContextMenu.cpp
	gui/CGUIEditBox.cpp
	gui/CGUIEnvironment.cpp
	gui/CGUIFileOpenDialog.cpp
	gui/CGUIFont.cpp
	gui/CGUIImage.cpp
	gui/CGUIInOutFader.cpp
	gui/CGUIListBox.cpp
	gui/CGUIMenu.cpp
	gui/CGUIMeshViewer.cpp
	gui/CGUIMessageBox.cpp
	gui/CGUIModalScreen.cpp
	gui/CGUIScrollBar.cpp
	gui/CGUISpinBox.cpp
	gui/CGUISkin.cpp
	gui/CGUIStaticText.cpp
	gui/CGUITabControl.cpp
	gui/CGUITable.cpp
	gui/CGUIToolBar.cpp
	gui/CGUIWindow.cpp
	gui/CGUIColorSelectDialog.cpp
	gui/CDefaultGUIElementFactory.cpp
	gui/CGUISpriteBank.cpp
	gui/CGUIImageList.cpp
	gui/CGUITreeView.cpp
	gui/CGUIProfiler.cpp
)

# Library

add_library(Irrlicht)
foreach(object_lib
	IRRMESHOBJ IRROBJ IRRVIDEOOBJ
	IRRIOOBJ IRROTHEROBJ IRRGUIOBJ)
	# Set include directories for object library compilation
	target_include_directories(${object_lib} PRIVATE ${link_includes})
	target_link_libraries(${object_lib} PUBLIC Include)
	# Add objects from object library to main library
	target_sources(Irrlicht PRIVATE $<TARGET_OBJECTS:${object_lib}>)
endforeach()

# Alias target provides add_submodule compatibility
add_library(EmberdawnIrrlicht::Irrlicht ALIAS Irrlicht)

target_include_directories(Irrlicht PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${link_includes})

target_link_libraries(Irrlicht
	PUBLIC Include
	PRIVATE ${link_libs})

set_target_properties(Irrlicht PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(WIN32)
	set_target_properties(Irrlicht PROPERTIES PREFIX "") # for DLL name
endif()

# Installation of library
if(ANDROID)
	set(INSTALL_TARGETS Irrlicht native_app_glue)
else()
	set(INSTALL_TARGETS Irrlicht)
endif()

install(TARGETS ${INSTALL_TARGETS}
	EXPORT emberdawn-irrlicht-export
	DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
