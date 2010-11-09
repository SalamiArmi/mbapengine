#ifndef _ISURFACE_HEADER_
#define _ISURFACE_HEADER_

#include "IArgonUnknown.h"

namespace Argon
{
	DeclareBasedInterface(ISurface, IArgonUnknown)

		enum MemoryPool
		{
			POOL_Managed,
			POOL_Default,
		};

		enum Format
		{
			FORMAT_Unknown = 0,			// DirectX, DXGI_FORMAT_UNKNOWN					OpenGL:
			FORMAT_ARGB32,				// DirectX, DXGI_FORMAT_R32G32B32A32_TYPELESS	OpenGL:
			FORMAT_ARGB16,				// DirectX, DXGI_FORMAT_R16G16B16A16_UNORM		OpenGL:
			FORMAT_Depth32,				// DirectX, DXGI_FORMAT_R32_FLOAT				OpenGL:
			FORMAT_RGB8,				// DirectX, DXGI_FORMAT_B8G8R8X8_UNORM			OpenGL:
			FORMAT_ARGB8,				// DirectX, DXGI_FORMAT_R8G8B8A8_UNORM			OpenGL:
			FORMAT_FORCE = 0xffffffff	// DirectX, DXGI_FORMAT_FORCE_UINT				OpenGL:
		};

		///GETHEIGHT(UNSIGNEDINT)
		///
		///Get the Height of the Surface
		///
		///No Params:
		uint GetHeight() = 0;

		///GETWIDTH(UNSIGNEDINT)
		///
		///Get the Width of the Surface
		///
		///No Params
		uint GetWidth() = 0;

		///GETPOOLTYPE(MEMORYPOOL)
		///
		///Get the type of pool this item was created on
		///
		///No Params:
		MemoryPool GetPoolType() = 0;

	EndInterface(ISurface)
} //Namespace

#endif //_ISURFACE_HEADER_