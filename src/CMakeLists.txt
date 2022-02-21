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
target_include_directories(Irrlicht PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${JPEG_INCLUDE_DIR}"
	"${OPENGL_INCLUDE_DIR}"
	"${OPENGL_REGISTRY_INCLUDE_DIRS}"
	"${OPENGLES2_INCLUDE_DIR}"
	"${EGL_INCLUDE_DIR}"
	"${X11_INCLUDE_DIR}")
target_link_libraries(Irrlicht
	PUBLIC Include
	PRIVATE
		ZLIB::ZLIB
		"${JPEG_LIBRARIES}"
		$<IF:$<TARGET_EXISTS:png>,png,png_static>
		"${OPENGL_LIBRARIES}"
		"${OPENGLES_LIBRARY}"
		"${OPENGLES2_LIBRARIES}"
		"${EGL_LIBRARY}"
		"${XINPUT_LIBRARY}"
		$<$<PLATFORM_ID:Android>:NativeAppGlue>
		$<$<PLATFORM_ID:Android>:android>
		$<$<PLATFORM_ID:Android>:log>
		"${COCOA_LIB}"
		"${IOKIT_LIB}"
		"${X11_X11_LIB}"
		"${X11_Xxf86vm_LIB}")
set_target_properties(Irrlicht PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	DEFINE_SYMBOL IRRLICHT_EXPORTS
	POSITION_INDEPENDENT_CODE ON)

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
elseif(WIN32)
	set_target_properties(Irrlicht PROPERTIES PREFIX "") # for DLL name
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(Irrlicht PRIVATE -D_DEBUG)
endif()

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

if(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
	target_compile_options(Irrlicht PRIVATE -Wall -pipe -fno-exceptions -fno-rtti)
	# Use SSE for floating point math on 32-bit x86.
	# See: github.com/minetest/minetest/issues/11810
	# See: https://gcc.gnu.org/wiki/FloatingPointMath
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		include(CheckCXXSourceCompiles)
		check_cxx_source_compiles("#ifndef __i686__\n#error\n#endif\nint main(){}" IS_I686)
		if(IS_I686)
			target_compile_options(Irrlicht PRIVATE -mfpmath=sse -msse)
		endif()
	endif()
elseif(MSVC)
	target_compile_options(Irrlicht PRIVATE /GR-)

	# Use SSE for floating point math on 32-bit x86.
	# See: github.com/minetest/minetest/issues/11810
	# See: https://gcc.gnu.org/wiki/FloatingPointMath
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		target_compile_options(Irrlicht PRIVATE /arch:SSE)
	endif()
endif()

# Alias target provides submodule compatibility
add_library(EmberdawnIrrlicht::Irrlicht ALIAS Irrlicht)

install(TARGETS Irrlicht EXPORT emberdawn-irrlicht-export)

if(ANDROID)
	install(TARGETS NativeAppGlue EXPORT emberdawn-irrlicht-export)
endif()
