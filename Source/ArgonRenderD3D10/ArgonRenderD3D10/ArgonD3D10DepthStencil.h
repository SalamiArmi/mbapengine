#ifndef _ARGOND3D10DEPTHSTENCIL_HEADER_
#define _ARGOND3D10DEPTHSTENCIL_HEADER_

#include <Interface/ISurface.h>
#include <Interface/IArgonUnknownImp.h>

#include "ArgonD3D10Device.h"

namespace Argon
{
	class D3D10DepthStencil : public IArgonUnknownImp<ISurface, GUID_ISurface>
	{
	public:
		D3D10DepthStencil(uint Width, uint Height, ISurface::Format Format);

		///LOAD(BOOL)
		///
		///Load all required information to create the depth stencil
		///
		///No Params:
		bool Load();

		///UNLOAD(BOOL)
		///
		///Unload all data/information that was used to create the depth stencil
		///
		///No Params:
		bool UnLoad();

		///GETHEIGHT(UNSIGNEDINT)
		///
		///Get the Height of the Surface
		///
		///No Params:
		uint GetHeight();

		///GETWIDTH(UNSIGNEDINT)
		///
		///Get the Width of the Surface
		///
		///No Params
		uint GetWidth();

		///GETPOOLTYPE(MEMORYPOOL)
		///
		///Get the type of pool this item was created on
		///
		///No Params:
		ISurface::MemoryPool GetPoolType();

		///(OD3D10DEPTHSTENCILVIEW)
		///
		///	Get the Depth Stencil
		///
		///No Params:
		ID3D10DepthStencilView* GetTexture() const;

		///CLEAR(VOID)
		///
		///	Clear the depth stencil with a depth of 1.0f
		///
		///No Params:
		void Clear();

	protected:
		~D3D10DepthStencil();

		//Dimensions
		uint m_Width;
		uint m_Height;

		//Format
		ISurface::Format m_Format;

		//D3D10 Members
		ID3D10Texture2D* m_Buffer;					//The Buffer for the Depth Stencil
		ID3D10DepthStencilView* m_DepthStencil;		//The acual depth stencil
	}; //D3D10DepthStencil
} //Namespace

#endif //_ARGOND3D10DEPTHSTENCIL_HEADER_