/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Renderers.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2RENDERERS_HPP
#define PX2RENDERERS_HPP

#include "PX2Renderer.hpp"

#ifdef PX2_USE_DX9
#include "PX2Dx9IndexBuffer.hpp"
#include "PX2Dx9Mapping.hpp"
#include "PX2Dx9PixelShader.hpp"
#include "PX2Dx9RenderTarget.hpp"
#include "PX2Dx9Shader.hpp"
#include "PX2Dx9Texture1D.hpp"
#include "PX2Dx9Texture2D.hpp"
#include "PX2Dx9Texture3D.hpp"
#include "PX2Dx9TextureCube.hpp"
#include "PX2Dx9VertexBuffer.hpp"
#include "PX2Dx9VertexFormat.hpp"
#include "PX2Dx9VertexShader.hpp"
#endif

#ifdef PX2_USE_OPENGL
#include "PX2OpenGLBitmapFont.hpp"
#include "PX2OpenGLIndexBuffer.hpp"
#include "PX2OpenGLMapping.hpp"
#include "PX2OpenGLPixelShader.hpp"
#include "PX2OpenGLRenderTarget.hpp"
#include "PX2OpenGLShader.hpp"
#include "PX2OpenGLTexture1D.hpp"
#include "PX2OpenGLTexture2D.hpp"
#include "PX2OpenGLTexture3D.hpp"
#include "PX2OpenGLTextureCube.hpp"
#include "PX2OpenGLVertexBuffer.hpp"
#include "PX2OpenGLVertexFormat.hpp"
#include "PX2OpenGLVertexShader.hpp"
#endif

#ifdef PX2_USE_OPENGLES2
#include "PX2OpenGLES2IndexBuffer.hpp"
#include "PX2OpenGLES2Mapping.hpp"
#include "PX2OpenGLES2MaterialPass.hpp"
#include "PX2OpenGLES2RendererData.hpp"
#include "PX2OpenGLES2Shader.hpp"
#include "PX2OpenGLES2Texture2D.hpp"
#include "PX2OpenGLES2VertexBuffer.hpp"
#include "PX2OpenGLES2VertexFormat.hpp"
#include "PX2OpenGLES2VertexShader.hpp"
#endif

#endif
