/*
*
* �ļ�����	��	PX2Scene.inl
*
*/

//----------------------------------------------------------------------------
inline void Scene::SetSceneID (int id)
{
	mSceneID = id;
}
//----------------------------------------------------------------------------
inline int Scene::GetSceneID ()
{
	return mSceneID;
}
//----------------------------------------------------------------------------
inline PX2::Node *Scene::GetSceneNode ()
{
	return mSceneNode;
}
//----------------------------------------------------------------------------
inline int Scene::GetActorQuantity ()
{
	return (int)mActors.size();
}
//----------------------------------------------------------------------------
inline CameraActor *Scene::GetDefaultCameraActor ()
{
	return mDefaultCameraActor;
}
//----------------------------------------------------------------------------