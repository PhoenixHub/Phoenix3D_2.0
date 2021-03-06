/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Movable.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2SPATIAL_HPP
#define PX2SPATIAL_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Controlledable.hpp"
#include "PX2Bound.hpp"
#include "PX2Transform.hpp"

namespace PX2
{

	class Culler;
	
	/// 空间几何体类
	/**
	* 所有需要空间数据支持的类型都从此类派生，同时支持截头体裁剪功能。空间数据
	* 包括：空间变换，包围盒。
	*/
	class Movable : public Controlledable
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(Movable);

	protected:
		Movable ();
	public:
		virtual ~Movable ();

		/// 本地和世界变换
		/**
		* 在某些情况下，你也许需要直接设置世界变换。如果World被设置了，
		* WorldIsCurrent标识也因该被设置为true。
		*/
		Transform LocalTransform;
		Transform WorldTransform;
		bool WorldTransformIsCurrent;

		/// 世界包围盒访问
		/**
		* 在某些情况下，你也许需要直接设置世界包围盒。如果WorldBound被直接设置
		* ，WorldBoundIsCurrent应该被设置为true。
		*/
		Bound WorldBound;
		bool WorldBoundIsCurrent;

		/// 裁剪类型
		enum CullingMode
		{
			/// 通过比较包围盒和裁剪面，决定物体的可见性。
			CULL_DYNAMIC,

			/// 强制物体被裁剪。如果是一个Node被裁剪了，该Node下的所有子节点也
			/// 被裁剪。	
			CULL_ALWAYS,

			/// 永远不裁剪物体。如果一个Node不被裁剪，该Node下的所有子节点也不
			/// 被裁剪。
			CULL_NEVER
		};

		CullingMode Culling;

		/// 更新几何状态和控制器
		/**
		* 函数向下更新场景变换，向上更新世界包围盒。
		*/
		void Update (double applicationTime = -Mathd::MAX_REAL,
			bool initiator = true);

		/// 获得父亲
		Movable* GetParent ();

		// 挂接
		/*
		* 当节点被加载到场景中时，重载此函数可以实现自己想要的操作。通常是在
		* 父节点的Attach，Detach里调用这两个函数。默认函数体为空。
		*/
		virtual void OnAttach ();
		virtual void OnDetach (); 

		virtual void OnPicked (int pickInfo); // called during Picker::Execute
		virtual void OnNotPicked (int pickInfo);

	protected:
		// 几何状态更新
		virtual void UpdateWorldData (double applicationTime);
		virtual void UpdateWorldBound () = 0;
		void PropagateBoundToRoot ();

public_internal:
		// 场景裁剪
		void OnGetVisibleSet (Culler& culler, bool noCull);
		virtual void GetVisibleSet (Culler& culler, bool noCull) = 0;

		// 设置父节点，节点在attach/detach的时候调用此函数。
		void SetParent (Movable* parent);

	protected:
		Movable* mParent;
	};

	PX2_REGISTER_STREAM(Movable);
	typedef Pointer0<Movable> MovablePtr;
#include "PX2Movable.inl"

}

#endif