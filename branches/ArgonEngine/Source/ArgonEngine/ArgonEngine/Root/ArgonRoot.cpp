#include "ArgonRoot.h"
#include <Standard/ArgonLog.h>

#if _WIN32
#	include "Windows.h"
#	include "WindowsPlatformInclude.h"
#endif

namespace Argon
{
	Root::Root()
		: m_Log(new ("ArgonLog.Log") Log("Argon.Log")),
		m_Platform(NULL)
	{
	}

	Root::~Root()
	{
	}

	bool Root::Load()
	{
		m_Log->Load();
		CreatePlatform(&m_Platform);	//Load the Engine Platform

		FindSupportedComponents();		//Find all Supported Components
		ImportRenderSystems();			//Import and prepare the render systems

		return true;
	}

	bool Root::Unload()
	{
		if(!m_Platform->UnLoad())
		{
			m_Log->LogMessage( "Failed to Unload Platform before Unloading the Root" );
		}
		delete m_Log;

		return true;
	}

	void Root::FindSupportedComponents()
	{
		m_Platform->FindAllFiles("ArgonEngine\\Components\\*.dll", &m_FoundComponents);
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

	size_t Root::GetRenderSystemCount()
	{
		return m_LoadedRenderSystems.Size();
	}

	IRenderSystem* Root::GetRenderSystem(size_t Index) const
	{
		return m_LoadedRenderSystems.At(Index);
	}


} //Namespace