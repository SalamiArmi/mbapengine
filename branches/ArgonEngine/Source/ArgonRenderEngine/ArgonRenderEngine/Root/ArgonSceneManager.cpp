#include "ArgonRoot.h"
#include "ArgonSceneManager.h"
#include "ArgonText.h"

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

	Root* SceneManager::GetCreator()
	{
		return m_Creator;
	}

	QString SceneManager::GetName()
	{
		return m_Name;
	}

	bool SceneManager::FrameUpdate(float DeltaT)
	{	
		if(Root::instance()->GetCurrentSceneManager() != this) return false;

		for(Vector<SceneNode*>::Iterator it = m_SceneNodes.Begin(); it != m_SceneNodes.End(); ++it)
		{
			(*it)->FrameUpdate(DeltaT);
		}

		return true;
	}

	bool SceneManager::FrameDraw(RenderPass Pass)
	{
		if(Root::instance()->GetCurrentSceneManager() != this) return false;
		
		for(Vector<IRenderable*>::Iterator it = m_Renderables.Begin(); it != m_Renderables.End(); ++it)
		{
			if((*it)->Bind())
			{
				(*it)->FrameDraw();
				(*it)->UnBind();
			}
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

	Text* SceneManager::CreateText(QString Name)
	{
		Text* Txt = new Text(Name);
		m_SceneNodes.Push_Back(Txt);
		m_Renderables.Push_Back(Txt);

		return Txt;
	}

	Text* SceneManager::GetText(QString Name)
	{
		return NULL;
	}

} //Namespace