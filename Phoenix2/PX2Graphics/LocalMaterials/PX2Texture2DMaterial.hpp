/*
* Phoenix 3D ��Ϸ���� Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* �ļ�����	��	PX2Texture2DMaterial.hpp
*
* �汾		:	1.0 (2011/04/05)
*
* ����		��	more
*
*/

#ifndef PX2TEXTURE2DMATERIAL_HPP
#define PX2TEXTURE2DMATERIAL_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2MaterialInstance.hpp"
#include "PX2Texture2D.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY Texture2DMaterial : public Material
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Texture2DMaterial);

	public:
		Texture2DMaterial (
			Shader::SamplerFilter filter = Shader::SF_NEAREST,
			Shader::SamplerCoordinate coordinate0 = Shader::SC_CLAMP_EDGE,
			Shader::SamplerCoordinate coordinate1 = Shader::SC_CLAMP_EDGE);

		virtual ~Texture2DMaterial ();

		PixelShader* GetPixelShader () const;

		MaterialInstance* CreateInstance (Texture2D* texture) const;
		static MaterialInstance* CreateUniqueInstance (Texture2D* texture,
			Shader::SamplerFilter filter, Shader::SamplerCoordinate coordinate0,
			Shader::SamplerCoordinate coordinate1);

	private:
		static int msDx9VRegisters[1];
		static int msOglVRegisters[1];
		static int* msVRegisters[Shader::MAX_PROFILES];
		static std::string msVPrograms[Shader::MAX_PROFILES];
		static int msAllPTextureUnits[1];
		static int* msPTextureUnits[Shader::MAX_PROFILES];
		static std::string msPPrograms[Shader::MAX_PROFILES];
	};

	PX2_REGISTER_STREAM(Texture2DMaterial);
	typedef Pointer0<Texture2DMaterial> Texture2DMaterialPtr;

}

#endif