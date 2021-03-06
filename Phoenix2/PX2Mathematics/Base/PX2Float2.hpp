/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Float2.hpp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2FLOAT2_HPP
#define PX2FLOAT2_HPP

#include "PX2MathematicsPrerequisites.hpp"
#include "PX2Tuple.hpp"

namespace PX2
{

	class PX2_MATHEMATICS_ENTRY Float2 : public Tuple<2,float>
	{
	public:
		Float2 ();   //< 未初始化
		~Float2 ();  // hides ~Tuple<2,float>
		Float2 (float f0, float f1);
		Float2 (const Float2& tuple);

		// 赋值
		Float2& operator= (const Float2& tuple);
	};

}

#endif