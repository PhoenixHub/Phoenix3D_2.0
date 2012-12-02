/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2WindowApplication.hpp
*
* 版本		:	1.0 (2011/02/02)
*
* 作者		：	more
*
*/

#ifndef PX2WINDOWAPPLICATION_HPP
#define PX2WINDOWAPPLICATION_HPP

#include "PX2ApplicationBase.hpp"

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#include <ShellAPI.h>
#endif

#ifdef PX2_USE_DX9
#include "PX2Dx9RendererInput.hpp"
#include "PX2Dx9RendererData.hpp"
#endif

#ifdef PX2_USE_OPENGLES2
#include "PX2OpenGLES2RendererInput.hpp"
#include "PX2OpenGLES2RendererData.hpp"
#endif

namespace PX2
{

#define PX2_DECLARE_APPLICATION(classname) \
	\
	static bool RegisterInitTerm (); \
	static bool AppInitialize (); \
	static bool AppTerminate ();

#define PX2_REGISTER_APPLICATION(classname) \
	static bool gsAppInitializeRegistered_##classname = \
	classname::RegisterInitTerm ();

#define PX2_IMPLEMENT_APPLICATION(classname) \
	\
	bool classname::RegisterInitTerm () \
	{ \
		ApplicationBase::msAppInitlizeFun = &classname::AppInitialize; \
		ApplicationBase::msAppTernamateFun = &classname::AppTerminate; \
		ApplicationBase::msEntry = &Application::Entry; \
		return true; \
	} \
	\
	bool classname::AppInitialize () \
	{ \
		msApplication = new classname(); \
		return true; \
	} \
	\
	bool classname::AppTerminate () \
	{ \
		delete (msApplication); \
		return true; \
	}
	//----------------------------------------------------------------------------

	class Application : public ApplicationBase
	{
	public:
		Application ();
		virtual ~Application ();

		static int Entry (int numArguments, char** arguments);
		virtual int Main (int numArguments, char** arguments);

	protected:
		virtual bool OnInitlizeApp ();
		virtual bool OnTernamateApp ();

#if defined(_WIN32) || defined(WIN32)
		// 窗口
		HWND mhWnd;
#endif

		RendererInput mInput;
	};

}

#endif