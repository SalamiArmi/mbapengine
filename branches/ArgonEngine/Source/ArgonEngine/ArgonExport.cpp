#include "ArgonEngine.h"

namespace Argon
{
	///PRELOADENGINE(BOOL)
	///
	///	Preload the Engine by creating a new engine and also loading all rendering systems but not
	// /Storing or creating until statics are chosen
	///
	///No Params:
	ArgonExport bool PreLoadEngine()
	{
		ArgonEngine::instance()->Load(); //Preload all the Components
		return true;
	}

	ArgonExport bool CreateEngine(void* Window, size_t RenderSystemIndex, size_t DriverIndex, size_t ModeIndex)
	{
		ArgonEngine::instance()->Create(Window, RenderSystemIndex, DriverIndex, ModeIndex);

		return true;
	}

	ArgonExport void FrameUpdate()
	{
		ArgonEngine::instance()->FrameUpdate();
	}

} //Namespace