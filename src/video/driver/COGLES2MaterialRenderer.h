// Copyright (C) 2014 Patryk Nadrowski
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_OGLES2_SL_MATERIAL_RENDERER_H_INCLUDED__
#define __C_OGLES2_SL_MATERIAL_RENDERER_H_INCLUDED__

#include "IrrCompileConfig.h"

#ifdef _IRR_COMPILE_WITH_OGLES2_

#include "EMaterialTypes.h"
#include "IMaterialRenderer.h"
#include "IMaterialRendererServices.h"
#include "IGPUProgrammingServices.h"
#include "irrArray.h"
#include "irrString.h"

#include "COGLES2Common.h"

namespace irr
{
namespace video
{

class COGLES2Driver;

class COGLES2MaterialRenderer : public IMaterialRenderer, public IMaterialRendererServices
{
public:

	COGLES2MaterialRenderer(
		COGLES2Driver* driver,
		s32& outMaterialTypeNr,
		const c8* vertexShaderProgram = 0,
		const c8* pixelShaderProgram = 0,
		IShaderConstantSetCallBack* callback = 0,
		E_MATERIAL_TYPE baseMaterial = EMT_SOLID,
		s32 userData = 0);

	virtual ~COGLES2MaterialRenderer();

	GLuint getProgram() const;

	virtual void OnSetMaterial(const SMaterial& material, const SMaterial& lastMaterial,
		bool resetAllRenderstates, IMaterialRendererServices* services);

	virtual bool OnRender(IMaterialRendererServices* service, E_VERTEX_TYPE vtxtype);

	virtual void OnUnsetMaterial();

	virtual bool isTransparent() const;

	virtual s32 getRenderCapability() const;

	virtual void setBasicRenderStates(const SMaterial& material, const SMaterial& lastMaterial, bool resetAllRenderstates) _IRR_OVERRIDE_;

	virtual s32 getVertexShaderConstantID(const c8* name) _IRR_OVERRIDE_;
	virtual s32 getPixelShaderConstantID(const c8* name) _IRR_OVERRIDE_;
	virtual void setVertexShaderConstant(const f32* data, s32 startRegister, s32 constantAmount=1) _IRR_OVERRIDE_;
	virtual void setPixelShaderConstant(const f32* data, s32 startRegister, s32 constantAmount=1) _IRR_OVERRIDE_;
	virtual bool setVertexShaderConstant(s32 index, const f32* floats, int count) _IRR_OVERRIDE_;
	virtual bool setVertexShaderConstant(s32 index, const s32* ints, int count) _IRR_OVERRIDE_;
	virtual bool setVertexShaderConstant(s32 index, const u32* ints, int count) _IRR_OVERRIDE_;
	virtual bool setPixelShaderConstant(s32 index, const f32* floats, int count) _IRR_OVERRIDE_;
	virtual bool setPixelShaderConstant(s32 index, const s32* ints, int count) _IRR_OVERRIDE_;
	virtual bool setPixelShaderConstant(s32 index, const u32* ints, int count) _IRR_OVERRIDE_;

	virtual IVideoDriver* getVideoDriver() _IRR_OVERRIDE_;

protected:

	COGLES2MaterialRenderer(COGLES2Driver* driver,
					IShaderConstantSetCallBack* callback = 0,
					E_MATERIAL_TYPE baseMaterial = EMT_SOLID,
					s32 userData = 0);

	void init(s32& outMaterialTypeNr, const c8* vertexShaderProgram, const c8* pixelShaderProgram, bool addMaterial = true);

	bool createShader(GLenum shaderType, const char* shader);
	bool linkProgram();

	COGLES2Driver* Driver;
	IShaderConstantSetCallBack* CallBack;

	bool Alpha;
	bool Blending;
	bool FixedBlending;

	struct SUniformInfo
	{
		core::stringc name;
		GLenum type;
		GLint location;
	};

	GLuint Program;
	core::array<SUniformInfo> UniformInfo;
	s32 UserData;
};


}
}

#endif
#endif

