#include "ArgonRoot.h"
#include <Standard/ArgonLog.h>
#include "SceneManager.h"
#include <Standard/ArgonTimer.h>

#if defined WIN32
#	include <Platform\CreateArgonWindows.h>
#endif

namespace Argon
{
	Root::Root()
		: m_Platform(NULL),
		m_Timer(new Timer())
	{
		
	}

	Root::~Root()
	{
	}

	bool Root::Load()
	{
		CreatePlatform(&m_Platform);	//Load the Engine Platform

		FindSupportedComponents();		//Find all Supported Components
		ImportRenderSystems();			//Import and prepare the render systems

		m_Timer->Reset();				//Start the Timer
		return true;
	}

	bool Root::Unload()
	{
		if(!m_Platform->UnLoad())
		{
			//LOG ERROR
		}

		return true;
	}

	bool Root::RenderOneFrame()
	{
		//Get DeltaT
		float DeltaT = (float)m_Timer->GetMilliseconds();

		//Update the Listners
		for(Vector<IFrameListner*>::Iterator it = m_FrameListners.Begin(); it != m_FrameListners.End(); ++it)
		{
			(*it)->FrameUpdate(DeltaT);
		}

		//Render Listners

		//Render the Normal Pass
		RenderListners(IFrameListner::RENDERPASS_Normal);

		//Render Post Pass
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
		m_Components.Push_Back(Manager);
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

	void Root::SetCurrentSceneManager(const SceneManager* Manager)
	{
		m_ActiveSceneManager = Manager;
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
			void* Component = m_Platform->LoadLibrary(m_FoundComponents.At(Index));
			if(Component)
			{
				//Log message Library Loaded
				ComponentEntryPoint LibraryEntryPoint = (ComponentEntryPoint)m_Platform->LoadEntryPoint((void*)Component, "CreateComponent");
				if(LibraryEntryPoint)
				{
					GUID Type = GUID_IArgonUnknown;
					IComponent* pComponent = NULL;
					if(LibraryEntryPoint(true, (void**)&pComponent, &Type))
					{
						//Log Message
						ARGONERROR("Engine Log.ArgonLog", "Message Logging Test");

						m_Components.Push_Back(pComponent);
					}
					else
						m_Platform->UnLoadLibrary(Component);
				}
				else
					m_Platform->UnLoadLibrary(Component);
			}
		}
	}

	void Root::ImportRenderSystems()
	{
		for(size_t Index = 0; Index < m_FoundComponents.Size(); ++Index)
		{
			void* Component = (HINSTANCE)m_Platform->LoadLibrary(m_FoundComponents.At(Index).c_str());
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
							IRenderSystem* RenderSystem;
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
						m_Platform->UnLoadLibrary(Component);
				}
				else
					m_Platform->UnLoadLibrary(Component);
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
				(*it)->RenderFrame(Pass);
			}
		}
	}

} //Namespace