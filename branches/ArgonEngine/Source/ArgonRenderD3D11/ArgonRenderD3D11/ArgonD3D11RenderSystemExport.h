#ifndef _ARGOND3D11RENDERSYSTEMEXPORT_HEADER_
#define _ARGOND3D11RENDERSYSTEMEXPORT_HEADER_

#include "ArgonD3D11RenderSystem.h"

namespace Argon
{
	ArgonExport bool CreateComponent(bool Create, void** OutComponent, GUID* GuidType)
	{
		if(Create)
			*OutComponent = D3D11RenderSystem::instance();
		*GuidType = GUID_IRenderSystem;
		return true;
	}
} //Namespace

#endif //_ARGOND3D11RENDERSYSTEMEXPORT_HEADER_