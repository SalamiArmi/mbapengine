#include "ArgonEngine.h"

namespace Argon
{
	///PRELOADENGINE(BOOL)
	///
	///	Preload the Engine by creating a new engine and also loading all rendering systems but not
	// /Storing or creating until statics are chosen
	///
	///No Params:
	ArgonExport bool PreLoadEngine(void* Window)
	{
		ArgonEngine::instance()->Load(); //Preload all the Components

		if(Window)
		{
			ArgonEngine::instance()->GetPlatform()->CreateArgonWindow();
		}

		return true;
	}

	ArgonExport void FrameUpdate()
	{
		ArgonEngine::instance()->FrameUpdate();
	}

} //Namespace