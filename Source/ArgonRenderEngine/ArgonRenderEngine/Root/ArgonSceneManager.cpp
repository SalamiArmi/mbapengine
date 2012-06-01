#include "ArgonRoot.h"
#include "ArgonSceneManager.h"
#include "ArgonText.h"
#include "ArgonEntity.h"
#include "ArgonGUIResource.h"
#include "ArgonGUIManager.h"

namespace Argon
{
	SceneManager::SceneManager(QString Name, Root *Creator)
		: m_Creator(Creator),
		m_Name(Name),
		m_RootEntity(new Entity("Root", Entity::TYPE_Root))
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

		//Start updating all the Entities
		m_RootEntity->FrameUpdate(DeltaT);

		return true;
	}

	bool SceneManager::FrameDraw(RenderPass Pass)
	{
		if(Root::instance()->GetCurrentSceneManager() != this) return false;

		for(Vector<IDrawable*>::Iterator DrawableIt = m_Renderable.Begin(); DrawableIt != m_Renderable.End(); ++DrawableIt)
		{
			if((*DrawableIt)->SupportsPass(Pass))
			{
				if((*DrawableIt)->Bind())
				{
					(*DrawableIt)->FrameDraw();
					(*DrawableIt)->UnBind();
				}
			}
		}

		return true;
	}

	Camera* SceneManager::CreateCamera(String Name)
	{
		//Create a new Camera
		Camera* Cam = new Camera(Name);

		m_RootEntity->AddSubnode(Cam);
		m_Entities.Push_Back(Cam);

		return Cam;
	}

	bool SceneManager::SupportsPass(IFrameListner::RenderPass Pass)
	{
		return true;
	}

	Text* SceneManager::CreateText(String Name)
	{
		Text* Txt = new Text(Name);
		Txt->Load();

		m_RootEntity->AddSubnode(Txt);
		m_Renderable.Push_Back(Txt);
		m_Entities.Push_Back(Txt);

		return Txt;
	}

	GUIResource* SceneManager::CreateGUI(String Name)
	{
		GUIManager* UIManager = (GUIManager* )Root::instance()->GetComponent("GUI Manager");
		GUIResource* Gui = UIManager->CreateResource(Name);
		Gui->Load();

		m_RootEntity->AddSubnode(Gui);
		m_Renderable.Push_Back(Gui);
		m_Entities.Push_Back(Gui);

		return Gui;
	}

	Entity* SceneManager::GetEntity(String EntityName)
	{
		for(Vector<Entity*>::Iterator it = m_Entities.Begin(); it != m_Entities.End(); ++it)
		{
			if((*it)->GetName() == EntityName)
			{
				return (*it);
			}
		}

		return NULL;
	}

} //Namespace