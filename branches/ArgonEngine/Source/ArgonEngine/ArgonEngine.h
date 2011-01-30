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

		///GETROOT(ROOT)
		///
		///Get the root if the engine it contains all the engine components and render systems
		///
		///No Params:
		Root*				GetRoot() const;

	protected:

	private:
		Root*	m_Root; //The Root is used to hide all Platforms and Render Systems		
	};
} //Namespace

#endif //_ARGONENGINE_HEADER_