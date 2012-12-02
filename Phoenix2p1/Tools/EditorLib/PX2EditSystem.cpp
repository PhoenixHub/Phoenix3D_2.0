/*
*
* �ļ�����	��	PX2EditSystem.cpp
*
*/

#include "PX2EditSystem.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditMap.hpp"
#include "PX2ActorSelection.hpp"
using namespace PX2;
using namespace PX2Editor;

//----------------------------------------------------------------------------
EditSystem::EditSystem ()
	:
mEditMode(EM_NONE),
mCM(0),
mEditMap(0),
mSelection(0)
{
}
//----------------------------------------------------------------------------
EditSystem::~EditSystem ()
{
}
//----------------------------------------------------------------------------
bool EditSystem::Initlize ()
{
	EventWorld *entWorld = new0 EventWorld();
	PX2_UNUSED(entWorld);

	GraphicsRoot *root = new0 GraphicsRoot();
	if (root)
	{
		root->Initlize();
	}
	else
	{
		return false;
	}

	ResourceManager *resMan = new0 ResourceManager();
	PX2_UNUSED(resMan);

	mEditMap = new0 EditMap();
	mCM = new0 EditCommandManager();
	mSelection = new0 ActorSelection();

	mHelpScene = new0 Node();

	StandardMesh stdMesh(VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0));
	mXYPlane = stdMesh.Rectangle(2, 2, 10000.0f, 10000.0f);
	mXYPlane->Update();

	mXZPlane = stdMesh.Rectangle(2, 2, 10000.0f, 10000.0f);
	mXZPlane->WorldTransform.SetRotate(Matrix3f().MakeEulerXYZ(Mathf::HALF_PI,
		0.0f, 0.0f));
	mXZPlane->WorldTransformIsCurrent = true;
	mXZPlane->Update();

	mYZPlane = stdMesh.Rectangle(2, 2, 10000.0f, 10000.0f);
	mYZPlane->WorldTransform.SetRotate(Matrix3f().MakeEulerXYZ(0.0f,
		Mathf::HALF_PI, 0.0f));
	mYZPlane->WorldTransformIsCurrent = true;
	mYZPlane->Update();

	return true;
}
//----------------------------------------------------------------------------
bool EditSystem::Terminate ()
{
	mHelpScene = 0;

	if (mSelection)
	{
		delete0(mSelection);
		mSelection = 0;
	}

	if (mCM)
	{
		delete0(mCM);
		mCM = 0;
	}

	if (mEditMap)
	{
		delete0(mEditMap);
		mEditMap = 0;
	}

	ResourceManager *resMan = ResourceManager::GetSingletonPtr();
	if (resMan)
	{
		delete0(resMan);
	}

	GraphicsRoot *graphicsRoot = GraphicsRoot::GetSingletonPtr();
	if (graphicsRoot)
	{
		graphicsRoot->Terminate();
		delete0(graphicsRoot);
	}

	EventWorld *entWorld = EventWorld::GetSingletonPtr();
	if (entWorld)
	{
		delete0(entWorld);
	}

	return true;
}
//----------------------------------------------------------------------------
void EditSystem::Update (double detalSeconds)
{
	if (EventWorld::GetSingletonPtr())
		EventWorld::GetSingleton().Update((float)detalSeconds);

	GetEditMap()->GetScene()->GetSceneNode()->Update(0);
}
//----------------------------------------------------------------------------
void EditSystem::SetEditMode (EditSystem::EditMode mode)
{
	mEditMode = mode;

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::SetEditMode);
	event->SetData<EditSystem::EditMode>(mEditMode);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	mHelpScene->Update();
}
//----------------------------------------------------------------------------
void EditSystem::SetPreViewObject (PX2::Object *obj)
{
	mPreViewObject = obj;

	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::SetPreView);
	ent->SetData<PX2::Object*>(obj);
	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------