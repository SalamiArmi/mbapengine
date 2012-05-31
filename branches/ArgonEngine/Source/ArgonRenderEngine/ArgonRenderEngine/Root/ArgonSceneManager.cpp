#include "ArgonRoot.h"
#include "ArgonSceneManager.h"
#include "ArgonText.h"
#include "ArgonEntity.h"

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

		m_RootEntity->Update(DeltaT);

		return true;
	}

	bool SceneManager::FrameDraw(RenderPass Pass)
	{
		if(Root::instance()->GetCurrentSceneManager() != this) return false;

		for(Vector<IRenderable*>::Iterator RenderableIt = m_Renderable.Begin(); RenderableIt != m_Renderable.End(); ++RenderableIt)
		{
			if((*RenderableIt)->SupportsPass(Pass))
			{
				if((*RenderableIt)->Bind())
				{
					(*RenderableIt)->FrameDraw();
					(*RenderableIt)->UnBind();
				}
			}
		}

		return false;
	}

	Camera* SceneManager::CreateCamera(QString Name)
	{
		//Create a new Camera
		Camera* Cam = new Camera(Name.c_str());
		m_Entities.Push_Back(Cam);
		return Cam;
	}

	Camera* SceneManager::GetCamera(QString Name)
	{
		for(Vector<Entity*>::Iterator it = m_Entities.Begin(); it != m_Entities.End(); ++it)
		{
			if((*it)->GetName() == Name.c_str() && (*it)->GetType() == Entity::TYPE_Camera)
			{
				return (Camera*)(*it);
			}
		}

		return NULL;
	}

	bool SceneManager::SupportsPass(IFrameListner::RenderPass Pass)
	{
		return true;
	}

	Text* SceneManager::CreateText(QString Name)
	{
		Text* Return = new Text("Hello World");
		Return->Load();
		m_Renderable.Push_Back(Return);

		return Return;
	}

	Text* SceneManager::GetText(QString Name)
	{
		return NULL;
	}

} //Namespace