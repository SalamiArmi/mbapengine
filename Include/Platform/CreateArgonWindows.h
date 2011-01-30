#ifndef _CREATEARGONWINDOWS_HEADER_
#define _CREATEARGONWINDOWS_HEADER_

#include "ArgonWindows.h"
#include <Interface\IPlatform.h>

ArgonExport void CreatePlatform(Argon::IPlatform** Platform)
{
	*Platform = new Argon::WindowsPlatform();
}

#endif //_CREATEARGONWINDOWS_HEADER_