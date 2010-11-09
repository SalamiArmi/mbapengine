#ifndef _ARGOND3D11UTILS_HEADER_
#define _ARGOND3D11UTILS_HEADER_

#include <Interface/ISurface.h>

DXGI_FORMAT ArgonFormatToD3D11(ISurface::Format Format)
{
	DXGI_FORMAT ReturnFormat;

	switch(Format)
	{
		case ISurface::FORMAT_ARGB32:	ReturnFormat = DXGI_FORMAT_R32G32B32A32_TYPELESS;		break;
		case ISurface::FORMAT_ARGB16:	ReturnFormat = DXGI_FORMAT_R16G16B16A16_UNORM;			break;
		case ISurface::FORMAT_Depth32:	ReturnFormat = DXGI_FORMAT_R32_FLOAT;					break;
		case ISurface::FORMAT_RGB8:		ReturnFormat = DXGI_FORMAT_B8G8R8X8_UNORM;				break;
		case ISurface::FORMAT_ARGB16:	ReturnFormat = DXGI_FORMAT_R16G16B16A16_UNORM;			break;
		case ISurface::FORMAT_Depth32:	ReturnFormat = DXGI_FORMAT_R32_FLOAT;					break;
		case ISurface::FORMAT_RGB8:		ReturnFormat = DXGI_FORMAT_B8G8R8X8_UNORM;				break;
		case ISurface::FORMAT_FORCE:	ReturnFormat = DXGI_FORMAT_FORCE_UINT;					break;
		default:						ReturnFormat = DXGI_FORMAT_UNKNOWN;						break;
	}
	return ReturnFormat;
}

#endif //_ARGOND3D11UTILS_HEADER_