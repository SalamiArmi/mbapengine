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
		for(Vector<ISceneNode*>::Iterator it = m_SceneNodes.Begin(); it != m_SceneNodes.End(); ++it)
		{
			(*it)->FrameUpdate(DeltaT);
		}

		return false;
	}

	bool SceneManager::FrameDraw(RenderPass Pass)
	{
		for(Vector<ISceneNode*>::Iterator it = m_SceneNodes.Begin(); it != m_SceneNodes.End(); ++it)
		{
			(*it)->FrameDraw();
		}

		return false;
	}

	ISceneNode* SceneManager::CreateSceneNode(QString Name)
	{
		return NULL;
	}

	bool SceneManager::SupportsPass(IFrameListner::RenderPass Pass)
	{
		return (Pass & IFrameListner::RENDERPASS_Normal);
	}

} //Namespace