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
		for(Vector<SceneNode*>::Iterator it = m_SceneNodes.Begin(); it != m_SceneNodes.End(); ++it)
		{
			(*it)->FrameUpdate(DeltaT);
		}

		return false;
	}

	bool SceneManager::FrameDraw(RenderPass Pass)
	{
		for(Vector<SceneNode*>::Iterator it = m_SceneNodes.Begin(); it != m_SceneNodes.End(); ++it)
		{
			(*it)->FrameDraw();
		}

		return false;
	}

	SceneNode* SceneManager::CreateSceneNode(QString Name)
	{
		//Create a new SceneNode
		SceneNode* Node = new SceneNode(Name);
		m_SceneNodes.Push_Back(Node);
		return Node;
	}

	Camera* SceneManager::CreateCamera(QString Name)
	{
		//Create a new Camera
		Camera* Cam = new Camera(Name);
		m_Cameras.Push_Back(Cam);
		return Cam;
	}

	Camera* SceneManager::GetCamera(QString Name)
	{
		for(Vector<Camera*>::Iterator it = m_Cameras.Begin(); it != m_Cameras.End(); ++it)
		{
			if((*it)->GetName() == Name)
			{
				return (*it);
			}
		}

		return NULL;
	}

	bool SceneManager::SupportsPass(IFrameListner::RenderPass Pass)
	{
		return (Pass & IFrameListner::RENDERPASS_Normal);
	}

} //Namespace