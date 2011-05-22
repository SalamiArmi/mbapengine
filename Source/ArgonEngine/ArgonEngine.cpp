#include "ArgonEngine.h"
#include <string.h>
#include <sstream>
#include <algorithm>
#include <Standard/ArgonLog.h>

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

	IRoot* ArgonEngine::GetRoot() const 
	{
		return m_Root;
	}

	IPlatform* ArgonEngine::GetPlatform() const
	{
		return m_Platform;
	}

} //Namespace