#include "ArgonEngine.h"
#include <string.h>
#include <sstream>
#include <algorithm>
#include <Standard/ArgonLog.h>

#if _WIN32
#include "Windows.h"
#include "WindowsPlatformInclude.h"
#endif

namespace Argon
{
	ArgonEngine::ArgonEngine()
		: m_EngineLog(new Log("Argon.Log")),
		m_Platform(NULL)
	{
	}

	ArgonEngine::~ArgonEngine()
	{

	}

	bool ArgonEngine::Load()
	{
		m_EngineLog->Load();
		CreatePlatform(&m_Platform);	//Load the Engine Platform

		FindSupportedComponents();		//Find all Supported Components
		ImportRenderSystems();			//Import and prepare the render systems

		return true;
	}

	bool ArgonEngine::Unload()
	{
		return true;
	}

	void ArgonEngine::FindSupportedComponents()
	{
		 m_Platform->FindAllFiles("ArgonEngine\\Components\\*.dll", &m_FoundComponents);
	}

	typedef bool (*ComponentEntryPoint)(bool Create, void** OutComponent, GUID* GuidType);

	void ArgonEngine::ImportComponents()
	{
		for(size_t Index = 0; Index < m_FoundComponents.Size(); ++Index)
		{
			HINSTANCE Component = (HINSTANCE)m_Platform->LoadLibrary(m_FoundComponents.At(Index));
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
						m_Platform->UnLoadLibrary((void*)Component);
				}
				else
					m_Platform->UnLoadLibrary((void*)Component);
			}
		}
	}

	void ArgonEngine::ImportRenderSystems()
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

	size_t ArgonEngine::GetRenderSystemCount()
	{
		return m_LoadedRenderSystems.Size();
	}

	IRenderSystem* ArgonEngine::GetRenderSystem(size_t Index) const
	{
		return m_LoadedRenderSystems.At(Index);
	}

} //Namespace