/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Dx9Mapping.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2DX9MAPPING_HPP
#define PX2DX9MAPPING_HPP

#include "PX2Dx9RendererPrerequisites.hpp"
#include "PX2AlphaProperty.hpp"
#include "PX2Buffer.hpp"
#include "PX2CullProperty.hpp"
#include "PX2DepthProperty.hpp"
#include "PX2Shader.hpp"
#include "PX2StencilProperty.hpp"
#include "PX2Texture.hpp"
#include "PX2VertexFormat.hpp"
#include "PX2Renderable.hpp"

namespace PX2
{

	extern BYTE gDX9AttributeType[VertexFormat::AT_QUANTITY];
	extern BYTE gDX9AttributeUsage[VertexFormat::AU_QUANTITY];
	extern DWORD gDX9BufferUsage[Buffer::BU_QUANTITY];
	extern DWORD gDX9BufferLocking[Buffer::BL_QUANTITY];
	extern D3DFORMAT gDX9TextureFormat[Texture::TF_QUANTITY];
	extern DWORD gDX9MinFilter[Shader::SF_QUANTITY];
	extern DWORD gDX9MipFilter[Shader::SF_QUANTITY];
	extern DWORD gDX9WrapMode[Shader::SC_QUANTITY];
	extern DWORD gDX9AlphaSrcBlend[AlphaProperty::SBM_QUANTITY];
	extern DWORD gDX9AlphaDstBlend[AlphaProperty::DBM_QUANTITY];
	extern DWORD gDX9AlphaCompare[AlphaProperty::CM_QUANTITY];
	extern DWORD gDX9CullOrder[2];
	extern DWORD gDX9DepthCompare[DepthProperty::CM_QUANTITY];
	extern DWORD gDX9StencilCompare[StencilProperty::CM_QUANTITY];
	extern DWORD gDX9StencilOperation[StencilProperty::OT_QUANTITY];
	extern D3DPRIMITIVETYPE gDX9PrimitiveType[Renderable::PT_MAX_QUANTITY];

}

#endif
