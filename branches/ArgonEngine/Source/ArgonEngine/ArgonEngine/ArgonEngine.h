#ifndef _ARGONENGINE_HEADER_
#define _ARGONENGINE_HEADER_

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonSingleton.h>

#include "Root/ArgonRoot.h"

namespace Argon
{
	class ArgonEngine : public singleton<ArgonEngine>
	{
		friend singleton;
	public:
		ArgonEngine();
		~ArgonEngine();

		///LOAD(BOOL)
		///
		///Load and init the engine
		///
		///No Params:
		bool				Load();

		///UNLOAD(VOID)
		///
		///Release and Cleanup the Engine
		///
		///No Params:
		bool				Unload();

	protected:

	private:
		Root*	m_Root; //The Root is used to hide all Platforms and Render Systems		
	};
} //Namespace

#endif //_ARGONENGINE_HEADER_