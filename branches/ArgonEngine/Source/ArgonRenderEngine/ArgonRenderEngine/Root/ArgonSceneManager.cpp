#include "ArgonSceneManager.h"

namespace Argon
{
	SceneManager::SceneManager(QString Name, Root *Creator)
		: m_Creator(Creator),
		m_Name(Name)
	{
		
	}

	SceneManager::~SceneManager()
	{

	}

	bool SceneManager::Load()
	{
		return true;
	}

	IRoot* SceneManager::GetCreator()
	{
		return m_Creator;
	}

	QString SceneManager::GetName()
	{
		return m_Name;
	}

	bool SceneManager::FrameUpdate(float DeltaT)
	{
		for(

		return false;
	}

	bool SceneManager::FrameDraw(RenderPass Pass)
	{
		return false;
	}

	bool SceneManager::SupportsPass(IFrameListner::RenderPass Pass)
	{
		return IFrameListner::RENDERPASS_Normal;
	}

} //Namespace