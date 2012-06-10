/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2CreateClodMesh.hpp
*
* 版本		:	1.0 (2011/03/17)
*
* 作者		：	more
*
*/

#ifndef PX2CREATECLODMESH_HPP
#define PX2CREATECLODMESH_HPP

#include "PX2GraphicsPrerequisites.hpp"
#include "PX2CollapseRecord.hpp"
#include "PX2EdgeKey.hpp"
#include "PX2MinHeap.hpp"
#include "PX2TriangleKey.hpp"
#include "PX2TriMesh.hpp"

namespace PX2
{

	class PX2_GRAPHICS_ENTRY CreateClodMesh
	{
	public:
		CreateClodMesh (TriMesh* mesh, int& numRecords, CollapseRecord*& records);
		~CreateClodMesh ();

	private:
		typedef std::set<TriangleKey> TriangleKeySet;
		typedef std::set<EdgeKey> EdgeKeySet;

		class Vertex
		{
		public:
			Vertex ();

			EdgeKeySet AdjEdges;
			TriangleKeySet AdjTriangles;
			bool Collapsible;
		};

		class Edge
		{
		public:
			Edge ();

			TriangleKeySet AdjTriangles;
			const MinHeapRecord<EdgeKey,float>* Record;
		};

		typedef int Triangle;

		typedef std::vector<Vertex> VertexArray;
		typedef std::map<EdgeKey,Edge> EdgeMap;
		typedef std::map<TriangleKey,Triangle> TriangleMap;

		// 边塌陷信息
		class CollapseInfo
		{
		public:
			CollapseInfo (int vKeep = -1, int vThrow = -1);

			int VKeep, VThrow, TThrow0, TThrow1;
		};

		bool ValidBuffers () const;
		void InsertTriangle (const TriangleKey& tKey, Triangle t);
		void RemoveTriangle (const TriangleKey& tKey);
		void ClassifyCollapsibleVertices ();
		float ComputeMetric (const EdgeKey& eKey);
		int CanCollapse (const EdgeKey& eKey);
		void Collapse (const EdgeKey& eKey, int indexThrow);
		bool ValidResults ();
		void ReorderBuffers ();
		void ComputeRecords (int& numRecords, CollapseRecord*& records);

		// 会被退化的三角形网格
		int mNumVertices, mNumIndices, mNumTriangles;
		int* mIndices;
		VertexBufferAccessor mVBA;

		// 顶点-边-三角形
		VertexArray mVertices;
		EdgeMap mEdges;
		TriangleMap mTriangles;

		// 支持顶点塌陷操作的边“最小堆”
		MinHeap<EdgeKey,float> mHeap;

		// The sequence of edge collapses.
		std::vector<CollapseInfo> mCollapses;

		// Postprocessing of the edge collapses.
		std::vector<int> mVerticesRemaining;
		std::vector<int> mTrianglesRemaining;
	};

}

#endif