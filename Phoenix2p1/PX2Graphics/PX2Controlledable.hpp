/*
*
* 文件名称	：	PX2Controlledable.hpp
*
*/

#ifndef PX2CONTROLLEDOBJECT_HPP
#define PX2CONTROLLEDOBJECT_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Controller.hpp"

namespace PX2
{
	
	/// 控制器基类
	/**
	* 从此类派生的类具有绑定控制器的功能。
	*/
	class Controlledable : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Controlledable);

	protected:
		Controlledable ();
	public:
		virtual ~Controlledable ();

		// 访问控制对象的控制器
		int GetNumControllers () const;
		inline Controller* GetController (int i) const;
		void AttachController (Controller* controller);
		void DetachController (Controller* controller);
		void DetachAllControllers ();
		bool UpdateControllers (double applicationTime);

	private:
		// 控制这个对象的控制器数组
		enum { CO_GROW_BY = 4 };
		int mNumControllers, mCapacity;
		ControllerPtr* mControllers;
	};

	PX2_REGISTER_STREAM(Controlledable);
	typedef Pointer0<Controlledable> ControlledablePtr;
#include "PX2Controlledable.inl"

}

#endif