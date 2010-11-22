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
		m_Root = new ("Root") Root();
		m_Root->Load();
		return true;
	}

	bool ArgonEngine::Unload()
	{
		return true;
	}

} //Namespace