/*
*
* Filename	:	SampleApp.cpp
*
*/

#include "SampleApp.hpp"

PX2_IMPLEMENT_APPLICATION(SampleApp)
//----------------------------------------------------------------------------
SampleApp::SampleApp ()
{
	mWindowTitle = std::string("SampleApp");
}
//----------------------------------------------------------------------------
SampleApp::~SampleApp ()
{
}
//----------------------------------------------------------------------------
bool SampleApp::OnInitlize ()
{
	Application::OnInitlize();

	CreateScene();

	mScene->Update();
	mCamera->SetFrustum(60.0f, ((float)mWidth)/(float)mHeight, 1.0f, 100.0f);
	AVector camDVector(0.0f, 0.0f, 1.0f);
	AVector camUVector(0.0f,1.0f,0.0f);
	AVector camRVector = camDVector.Cross(camUVector);
	APoint camPosition = APoint::ORIGIN -
		2.0f*mScene->WorldBound.GetRadius()*camDVector;
	mCamera->SetFrame(camPosition, camDVector, camUVector, camRVector);

	// init update
	mScene->Update();

	// set culler camera
	mCuller.SetCamera(mCamera);
	mCuller.ComputeVisibleSet(mScene);

	return true;
}
//----------------------------------------------------------------------------
bool SampleApp::OnTernamate ()
{
	mScene = 0;

	Application::OnTernamate();

	return true;
}
//----------------------------------------------------------------------------
bool SampleApp::OnResume()
{
	return true;
}
//----------------------------------------------------------------------------
bool SampleApp::OnPause()
{
	return true;
}
//----------------------------------------------------------------------------
void SampleApp::OnIdle ()
{
	mRenderer->SetClearColor(Float4(1.0f, 0.0f, 0.0f, 1.0f));

	MeasureTime();

	mScene->Update();
	mCuller.ComputeVisibleSet(mScene);

	if (mRenderer->PreDraw())
	{
		mRenderer->ClearBuffers();

		mRenderer->Draw(mCuller.GetVisibleSet().Sort());

		DrawFrameRate(8, mHeight-8, mTextColor);

		mRenderer->PostDraw();
		mRenderer->DisplayColorBuffer();
	}

	UpdateFrameCount();
}
//----------------------------------------------------------------------------
void SampleApp::CreateScene ()
{
	mScene = new0 Node();
}
//----------------------------------------------------------------------------