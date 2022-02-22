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

add_library(Irrlicht SHARED
	gui/BuiltInFont.h
	gui/CDefaultGUIElementFactory.cpp
	gui/CDefaultGUIElementFactory.h
	gui/CGUIButton.cpp
	gui/CGUIButton.h
	gui/CGUICheckBox.cpp
	gui/CGUICheckBox.h
	gui/CGUIColorSelectDialog.cpp
	gui/CGUIColorSelectDialog.h
	gui/CGUIComboBox.cpp
	gui/CGUIComboBox.h
	gui/CGUIContextMenu.cpp
	gui/CGUIContextMenu.h
	gui/CGUIEditBox.cpp
	gui/CGUIEditBox.h
	gui/CGUIEnvironment.cpp
	gui/CGUIEnvironment.h
	gui/CGUIFileOpenDialog.cpp
	gui/CGUIFileOpenDialog.h
	gui/CGUIFont.cpp
	gui/CGUIFont.h
	gui/CGUIImage.cpp
	gui/CGUIImage.h
	gui/CGUIImageList.cpp
	gui/CGUIImageList.h
	gui/CGUIInOutFader.cpp
	gui/CGUIInOutFader.h
	gui/CGUIListBox.cpp
	gui/CGUIListBox.h
	gui/CGUIMenu.cpp
	gui/CGUIMenu.h
	gui/CGUIMeshViewer.cpp
	gui/CGUIMeshViewer.h
	gui/CGUIMessageBox.cpp
	gui/CGUIMessageBox.h
	gui/CGUIModalScreen.cpp
	gui/CGUIModalScreen.h
	gui/CGUIProfiler.cpp
	gui/CGUIProfiler.h
	gui/CGUIScrollBar.cpp
	gui/CGUIScrollBar.h
	gui/CGUISkin.cpp
	gui/CGUISkin.h
	gui/CGUISpinBox.cpp
	gui/CGUISpinBox.h
	gui/CGUISpriteBank.cpp
	gui/CGUISpriteBank.h
	gui/CGUIStaticText.cpp
	gui/CGUIStaticText.h
	gui/CGUITabControl.cpp
	gui/CGUITabControl.h
	gui/CGUITable.cpp
	gui/CGUITable.h
	gui/CGUIToolBar.cpp
	gui/CGUIToolBar.h
	gui/CGUITreeView.cpp
	gui/CGUITreeView.h
	gui/CGUIWindow.cpp
	gui/CGUIWindow.h
	io/CAttributeImpl.h
	io/CAttributes.cpp
	io/CAttributes.h
	io/CFileList.cpp
	io/CFileList.h
	io/CFileSystem.cpp
	io/CFileSystem.h
	io/CLimitReadFile.cpp
	io/CLimitReadFile.h
	io/CMemoryFile.cpp
	io/CMemoryFile.h
	io/CMountPointReader.cpp
	io/CMountPointReader.h
	io/CReadFile.cpp
	io/CReadFile.h
	io/CWriteFile.cpp
	io/CWriteFile.h
	io/CZipReader.cpp
	io/CZipReader.h
	io/IAttribute.h
	scene/CBillboardSceneNode.cpp
	scene/CBillboardSceneNode.h
	scene/CCameraSceneNode.cpp
	scene/CCameraSceneNode.h
	scene/CDefaultSceneNodeFactory.cpp
	scene/CDefaultSceneNodeFactory.h
	scene/CDummyTransformationSceneNode.cpp
	scene/CDummyTransformationSceneNode.h
	scene/CEmptySceneNode.cpp
	scene/CEmptySceneNode.h
	scene/CMeshCache.cpp
	scene/CMeshCache.h
	scene/CMeshManipulator.cpp
	scene/CMeshManipulator.h
	scene/CSceneCollisionManager.cpp
	scene/CSceneCollisionManager.h
	scene/CSceneManager.cpp
	scene/CSceneManager.h
	scene/mesh/CAnimatedMeshSceneNode.cpp
	scene/mesh/CAnimatedMeshSceneNode.h
	scene/mesh/CBoneSceneNode.cpp
	scene/mesh/CBoneSceneNode.h
	scene/mesh/CMeshSceneNode.cpp
	scene/mesh/CMeshSceneNode.h
	scene/mesh/CSkinnedMesh.cpp
	scene/mesh/CSkinnedMesh.h
	scene/mesh/loader/CB3DMeshFileLoader.cpp
	scene/mesh/loader/CB3DMeshFileLoader.h
	scene/mesh/loader/COBJMeshFileLoader.cpp
	scene/mesh/loader/COBJMeshFileLoader.h
	scene/mesh/loader/CXMeshFileLoader.cpp
	scene/mesh/loader/CXMeshFileLoader.h
	scene/mesh/loader/SB3DStructs.h
	video/CFPSCounter.cpp
	video/CFPSCounter.h
	video/driver/CEGLManager.cpp
	video/driver/CEGLManager.h
	video/driver/CGLXManager.cpp
	video/driver/CGLXManager.h
	video/driver/CIrrDeviceConsole.cpp
	video/driver/CIrrDeviceConsole.h
	video/driver/CIrrDeviceFB.cpp
	video/driver/CIrrDeviceFB.h
	video/driver/CIrrDeviceLinux.cpp
	video/driver/CIrrDeviceLinux.h
	video/driver/CIrrDeviceSDL.cpp
	video/driver/CIrrDeviceSDL.h
	video/driver/CIrrDeviceStub.cpp
	video/driver/CIrrDeviceStub.h
	video/driver/CIrrDeviceWin32.cpp
	video/driver/CIrrDeviceWin32.h
	video/driver/CNullDriver.cpp
	video/driver/CNullDriver.h
	video/driver/COGLES2Common.h
	video/driver/COGLES2Driver.cpp
	video/driver/COGLES2Driver.h
	video/driver/COGLES2ExtensionHandler.cpp
	video/driver/COGLES2ExtensionHandler.h
	video/driver/COGLES2FixedPipelineRenderer.cpp
	video/driver/COGLES2FixedPipelineRenderer.h
	video/driver/COGLES2MaterialRenderer.cpp
	video/driver/COGLES2MaterialRenderer.h
	video/driver/COGLES2Renderer2D.cpp
	video/driver/COGLES2Renderer2D.h
	video/driver/COGLESCommon.h
	video/driver/COGLESCoreExtensionHandler.h
	video/driver/COGLESDriver.cpp
	video/driver/COGLESDriver.h
	video/driver/COGLESExtensionHandler.cpp
	video/driver/COGLESExtensionHandler.h
	video/driver/COGLESMaterialRenderer.h
	video/driver/COpenGLCacheHandler.cpp
	video/driver/COpenGLCacheHandler.h
	video/driver/COpenGLCommon.h
	video/driver/COpenGLCoreCacheHandler.h
	video/driver/COpenGLCoreFeature.h
	video/driver/COpenGLCoreRenderTarget.h
	video/driver/COpenGLCoreTexture.h
	video/driver/COpenGLDriver.cpp
	video/driver/COpenGLDriver.h
	video/driver/COpenGLExtensionHandler.cpp
	video/driver/COpenGLExtensionHandler.h
	video/driver/COpenGLMaterialRenderer.h
	video/driver/COpenGLShaderMaterialRenderer.cpp
	video/driver/COpenGLShaderMaterialRenderer.h
	video/driver/COpenGLSLMaterialRenderer.cpp
	video/driver/COpenGLSLMaterialRenderer.h
	video/driver/CVideoModeList.cpp
	video/driver/CVideoModeList.h
	video/driver/CWebGL1Driver.cpp
	video/driver/CWebGL1Driver.h
	video/driver/CWebGLExtensionHandler.h
	video/driver/CWGLManager.cpp
	video/driver/CWGLManager.h
	video/driver/IImagePresenter.h
	video/image/CBlit.h
	video/image/CColorConverter.cpp
	video/image/CColorConverter.h
	video/image/CImage.cpp
	video/image/CImage.h
	video/image/CImageLoaderBMP.cpp
	video/image/CImageLoaderBMP.h
	video/image/CImageLoaderJPG.cpp
	video/image/CImageLoaderJPG.h
	video/image/CImageLoaderPNG.cpp
	video/image/CImageLoaderPNG.h
	video/image/CImageLoaderTGA.cpp
	video/image/CImageLoaderTGA.h
	video/image/CImageWriterJPG.cpp
	video/image/CImageWriterJPG.h
	video/image/CImageWriterPNG.cpp
	video/image/CImageWriterPNG.h
	CLogger.cpp
	COSOperator.cpp
	CProfiler.cpp
	Irrlicht.cpp
	leakHunter.cpp
	os.cpp
	CLogger.h
	COSOperator.h
	CProfiler.h
	CTimer.h
	EProfileIDs.h
	os.h
	resource.h
	SoftwareDriver2_compile_config.h
	SoftwareDriver2_helper.h)

if(ANDROID)
	target_sources(Irrlicht PRIVATE
		Android/CAndroidAssetFileArchive.cpp
		Android/CAndroidAssetFileArchive.h
		Android/CAndroidAssetReader.cpp
		Android/CAndroidAssetReader.h
		Android/CIrrDeviceAndroid.cpp
		Android/CIrrDeviceAndroid.h
		Android/CKeyEventWrapper.cpp
		Android/CKeyEventWrapper.h)
elseif(APPLE)
	enable_language(OBJCXX)
	target_sources(Irrlicht PRIVATE
		video/driver/CIrrDeviceOSX.mm
		video/driver/CIrrDeviceOSX.h
		video/driver/CNSOGLManager.mm
		video/driver/CNSOGLManager.h)
	set_source_files_properties(Irrlicht.cpp COSOperator.cpp PROPERTIES
		COMPILE_OPTIONS -xobjective-c++)
endif()

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
