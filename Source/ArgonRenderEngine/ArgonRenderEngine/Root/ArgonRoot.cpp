#include <Standard/ArgonTimer.h>
#include <Standard/ArgonLog.h>

#include "ArgonSceneManager.h"
#include "ArgonRoot.h"

#include "ArgonGUIManager.h"
#include "ArgonGeometryManager.h"
#include "ArgonTextureManager.h"

namespace Argon
{
	void ArgonCreateRoot(Root** Root, IPlatform* Platform)
	{
		(*Root) = new Argon::Root(Platform);
	}

	Root::Root(IPlatform* Platform)
		: m_Platform(Platform)
	{
		m_instance = this;
		m_Platform->AddRef();
	}

	Root::Root()
		: m_Platform(NULL)
	{

	}

	Root::~Root()
	{
	}

	bool Root::Load()
	{
		FindSupportedComponents();		//Find all Supported Components
		ImportRenderSystems();			//Import and prepare the render systems

		AddComponent(new TextureManager());
		AddComponent(new GeometryManager());
		AddComponent(new GUIManager());

		return true;
	}

	bool Root::UnLoad()
	{
		m_Platform->UnLoad();
		return true;
	}

	IPlatform* Root::GetPlatform()
	{
		return m_Platform;
	}

	void Root::AddComponent(IComponent* Component)
	{
		QString Name = Component->GetName();

		for(Vector<IComponent*>::Iterator it = m_Components.Begin(); it != m_Components.End(); it++)
		{
			if((*it)->GetName() == Name)
			{
				(*it)->UnLoad();
				return;
			}
		}

		m_Components.Push_Back(Component);

#if _DEBUG
		ArgonAssert(Component->Load());
#else
		Component->Load();
#endif

		
	}

	void Root::RemoveComponent(IComponent* Component)
	{
		for(Vector<IComponent*>::Iterator it = m_Components.Begin(); it != m_Components.End(); it++)
		{
			if((*it) == Component)
			{
				m_Components.Erase(it);
				(*it)->UnLoad();
				return;
			}
		}
	}

	IComponent* Root::GetComponent(String ComponentName)
	{
		for(Vector<IComponent*>::Iterator it = m_Components.Begin(); it != m_Components.End(); it++)
		{
			if((*it)->GetName() == ComponentName)
			{
				return (*it);
			}
		}
		return NULL;
	}

	void Root::RemoveComponent(String ComponentName)
	{
		for(Vector<IComponent*>::Iterator it = m_Components.Begin(); it != m_Components.End(); it++)
		{
			if((*it)->GetName() == ComponentName)
			{
				m_Components.Erase(it);
				return;
			}
		}
	}

	IRenderSystem* Root::GetActiveRenderSystem() const
	{
		return m_ActiveRenderSystem;
	}

	bool Root::Create(void* Window, size_t RenderSystemIndex, size_t DriverIndex, size_t ModeIndex)
	{
		m_ActiveRenderSystem = m_LoadedRenderSystems.At(RenderSystemIndex);
		m_ActiveRenderSystem->CreateDevice(DriverIndex, ModeIndex, Window);
		m_ActiveRenderSystem->AddRef();

		for(Vector<IRenderSystem*>::Iterator it = m_LoadedRenderSystems.Begin(); it != m_LoadedRenderSystems.End(); ++it)
		{
			(*it)->UnLoad();
		}

		//Create default Viewport
		IViewport* Viewport = m_ActiveRenderSystem->CreateViewport(256, 256, 0, 0);
		if(Viewport)
		{
			m_ActiveRenderSystem->SetViewport(Viewport);
		}

		return true;
	}

	bool Root::FrameUpdate(float DeltaT)
	{
		return m_ActiveSceneManager->FrameUpdate(DeltaT);
	}


	bool Root::DrawOneFrame()
	{
		//Render Listners
		m_ActiveRenderSystem->BeginFrame();

		//Render the Normal Pass
		RenderListners(IFrameListner::RENDERPASS_Normal);

		//Render Post Pass
		RenderListners(IFrameListner::RENDERPASS_Post);

		//Render Topmost Pass
		RenderListners(IFrameListner::RENDERPASS_TopMost);

		GUIManager* Manager = (GUIManager* )GetComponent("GUI Manager");
		if(Manager)
		{
			Manager->DrawBufferedInstances(true); //Use the GUI Manager to render the Instanced Sprites very fast
		}

		//End the Frame and also present to the screen
		m_ActiveRenderSystem->EndFrame();

		return false;
	}

	size_t Root::GetRenderSystemCount()
	{
		return m_LoadedRenderSystems.Size();
	}

	IRenderSystem* Root::GetRenderSystem(size_t Index) const
	{
		return m_LoadedRenderSystems.At(Index);
	}

	SceneManager* Root::CreateSceneManager(QString Name)
	{
		SceneManager* Manager = new SceneManager(Name, this);
		Manager->Load();
		m_Components.Push_Back(Manager);
		AddFrameListner(Manager);
		return Manager;
	}

	void Root::UnLoadSceneManager(SceneManager* Manager)
	{
		for(Vector<SceneManager*>::Iterator it = m_SceneManagers.Begin(); it != m_SceneManagers.End(); ++it)
		{
			if((*it) == Manager)
			{
				m_SceneManagers.Erase(it);
			}
		}

		if(m_ActiveSceneManager == Manager)
		{
			m_ActiveSceneManager = NULL;
		}

		Manager->UnLoad();
	}

	SceneManager* Root::GetCurrentSceneManager() const
	{
		return m_ActiveSceneManager;
	}

	void Root::SetCurrentSceneManager(SceneManager* Manager)
	{
		m_ActiveSceneManager = (SceneManager*)Manager;
	}

	void Root::AddFrameListner(IFrameListner *FrameListner)
	{
		m_FrameListners.Push_Back(FrameListner);
	}

	void Root::RemoveFrameListner(IFrameListner *FrameListner)
	{
		for(Vector<IFrameListner*>::Iterator it = m_FrameListners.Begin(); it != m_FrameListners.End(); ++it)
		{
			if((*it) == FrameListner)
			{
				m_FrameListners.Erase(it);
				break;
			}
		}
	}

	typedef bool (*ComponentEntryPoint)(bool Create, void** OutComponent, GUID* GuidType);

	void Root::ImportComponents()
	{
		for(size_t Index = 0; Index < m_FoundComponents.Size(); ++Index)
		{
			void* Component = m_Platform->LoadArgonLibrary(m_FoundComponents.At(Index));
			if(Component)
			{
				//Log message Library Loaded
				ComponentEntryPoint LibraryEntryPoint = (ComponentEntryPoint)m_Platform->LoadEntryPoint((void*)Component, "CreateComponent");
				if(LibraryEntryPoint)
				{
					GUID Type = GUID_IArgonUnknown;
					IComponent* pComponent = NULL;
					if(LibraryEntryPoint(false, NULL, &Type))
					{
						if(Type != GUID_IRenderSystem)
						{
							if(LibraryEntryPoint(false, (void**)&pComponent, &Type))
							{
								m_Components.Push_Back(pComponent);
							}
						}
					}
					else
					{
						m_Platform->UnLoadLibrary(Component);
					}
				}
				else
				{
					m_Platform->UnLoadLibrary(Component);
				}
			}
		}
	}

	void Root::ImportRenderSystems()
	{
		for(size_t Index = 0; Index < m_FoundComponents.Size(); ++Index)
		{
			void* Component = (HINSTANCE)m_Platform->LoadArgonLibrary(m_FoundComponents.At(Index).c_str());
			if(Component)
			{
				//Log message Library Loaded
				ComponentEntryPoint LibraryEntryPoint = (ComponentEntryPoint)m_Platform->LoadEntryPoint(Component, "CreateComponent");
				if(LibraryEntryPoint)
				{
					GUID Type = GUID_IArgonUnknown;
					if(LibraryEntryPoint(false, NULL, &Type))
					{
						if(Type == GUID_IRenderSystem)
						{
							IRenderSystem* RenderSystem = NULL;
							if(LibraryEntryPoint(true, (void**)&RenderSystem, &Type))
							{
								if(RenderSystem)
								{
									RenderSystem->Load();
									m_LoadedRenderSystems.Push_Back(RenderSystem);
								}
							}
						}
					}
					else
					{
						m_Platform->UnLoadLibrary(Component);
					}
				}
				else
				{
					m_Platform->UnLoadLibrary(Component);
				}
			}
		}
	}

	void Root::FindSupportedComponents()
	{
		m_Platform->FindAllFiles("ArgonEngine\\Components\\*.dll", &m_FoundComponents);
	}

	void Root::RenderListners(IFrameListner::RenderPass Pass)
	{
		for(Vector<IFrameListner*>::Iterator it = m_FrameListners.Begin(); it != m_FrameListners.End(); ++it)
		{
			if((*it)->SupportsPass(Pass))
			{
				(*it)->FrameDraw(Pass);
			}
		}
	}

} //Namespace