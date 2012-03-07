#include <Interface/IComponent.h>

#include "ArgonEngine.h"

namespace Argon
{
#include "ArgonInitializationExport.inl"

	///DESTROYENGINE(BOOL)
	///
	///Destroy the engine and all loaded render systems
	///
	///No Params:
	ArgonExport bool DestoryEngine()
	{
		ArgonEngine::instance()->Unload();
		ArgonEngine::destroyInstance();

		return true;
	}

	///FRAMEUPDATE(VOID)
	///
	/// Update the engine and call render
	///
	///No Params:
	ArgonExport void FrameUpdate()
	{
		ArgonEngine::instance()->FrameUpdate();
	}

} //Namespace