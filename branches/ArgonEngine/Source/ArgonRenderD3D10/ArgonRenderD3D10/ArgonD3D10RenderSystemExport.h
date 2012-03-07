#ifndef _ARGOND3D10RENDERSYSTEMEXPORT_HEADER_
#define _ARGOND3D10RENDERSYSTEMEXPORT_HEADER_

namespace Argon
{
	ArgonExport bool CreateComponent(bool Create, void** OutComponent, GUID* GuidType)
	{
		if(Create)
			*OutComponent = D3D10RenderSystem::instance();
		*GuidType = GUID_IRenderSystem;
		return true;
	}

} //namespace

#endif //_ARGOND3D10RENDERSYSTEMEXPORT_HEADER_