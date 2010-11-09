#include "WindowsPlatformInclude.h"
#include "ArgonWindows.h"

namespace Argon
{
	void CreatePlatform(IPlatform** Platform)
	{
		*Platform = new WindowsPlatform();
	}
}//Namespace