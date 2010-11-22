#ifndef _ARGOND3D11DEPTHSTENCIL_HEADER_
#define _ARGOND3D11DEPTHSTENCIL_HEADER_

#include <Interface/ISurface.h>
#include <Interface/IArgonUnknownImp.h>

#include "ArgonD3D11Device.h"

namespace Argon
{

	class D3D11DepthStencil : public IArgonUnknownImp<ISurface, GUID_ISurface>
	{
	public:
		D3D11DepthStencil(uint Width, uint Height, ISurface::Format Format);

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

		///(OD3D11DEPTHSTENCILVIEW)
		///
		///	Get the Depth Stencil
		///
		///No Params:
		ID3D11DepthStencilView* GetTexture();

	protected:
		~D3D11DepthStencil();

		//Dimensions
		uint m_Width;
		uint m_Height;

		//Format
		ISurface::Format m_Format;

		//D3D11 Members
		ID3D11Texture2D* m_Buffer;					//The Buffer for the Depth Stencil
		ID3D11DepthStencilView* m_DepthStencil;		//The acual depth stencil
	};

} //Namespace

#endif //_ARGOND3D11DEPTHSTENCIL_HEADER_