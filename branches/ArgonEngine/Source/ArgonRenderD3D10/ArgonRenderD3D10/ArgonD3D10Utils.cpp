#include "ArgonD3D10Utils.h"
namespace Argon
{

	DXGI_FORMAT ArgonFormatToD3D10(Format SurfaceFormat)
	{
		DXGI_FORMAT ReturnFormat;

		switch(SurfaceFormat)
		{
		case Format::FORMAT_ARGB32:		ReturnFormat = DXGI_FORMAT_R32G32B32A32_TYPELESS;		break;
		case Format::FORMAT_ARGB16:		ReturnFormat = DXGI_FORMAT_R16G16B16A16_UNORM;			break;
		case Format::FORMAT_Depth32:	ReturnFormat = DXGI_FORMAT_R32_FLOAT;					break;
		case Format::FORMAT_RGB8:		ReturnFormat = DXGI_FORMAT_B8G8R8X8_UNORM;				break;
		case Format::FORMAT_FORCE:		ReturnFormat = DXGI_FORMAT_FORCE_UINT;					break;
		case Format::FORMAT_Depth24:	ReturnFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;			break;
		default:						ReturnFormat = DXGI_FORMAT_UNKNOWN;						break;
		}
		return ReturnFormat;
	}

} //Namespace