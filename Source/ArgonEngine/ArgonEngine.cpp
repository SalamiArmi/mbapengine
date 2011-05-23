#include "ArgonEngine.h"
#include <string.h>
#include <sstream>
#include <algorithm>

#include <Standard/ArgonLog.h>
#include <Standard/ArgonException.h>
#include <Standard/ArgonMemory.h>

namespace Argon
{
	ArgonEngine::ArgonEngine()
		: m_Root(NULL)
	{
	}

	ArgonEngine::~ArgonEngine()
	{

	}

	bool ArgonEngine::Load()
	{
		//Create the Platform and the Root to render with
		CreatePlatform(&m_Platform);
		m_Platform->Load();

		ArgonCreateRoot(&m_Root, m_Platform);
		m_Root->Load();

		return true;
	}

	bool ArgonEngine::Unload()
	{
		m_Root->UnLoad();
		m_Platform->UnLoad();

		return true;
	}

	bool ArgonEngine::Create(void* Window, size_t RenderSystemIndex, size_t DriverIndex, size_t ModeIndex)
	{
		m_Root->Create(Window, RenderSystemIndex, DriverIndex, ModeIndex);

		if(Window)
		{
			m_Platform->CreateArgonWindow();
		}

		return true;
	}

	bool ArgonEngine::FrameUpdate()
	{
		try
		{
			//Get Time Delta
			float DeltaT = m_Timer->GetMilliseconds();

			//Update the Active SceneManager
			m_Root->FrameUpdate(DeltaT);
	
			//Update complete Render the Frame
			m_Root->DrawOneFrame();
		}
		catch(...)
		{
			return false;
		}

		return true;
	}

	IRoot* ArgonEngine::GetRoot() const 
	{
		return m_Root;
	}

	IPlatform* ArgonEngine::GetPlatform() const
	{
		return m_Platform;
	}

} //Namespace