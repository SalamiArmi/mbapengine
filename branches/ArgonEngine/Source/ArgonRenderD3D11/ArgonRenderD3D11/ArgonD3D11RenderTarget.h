#ifndef _ARGOND3D11RENDERTARGET_HEADER_
#define _ARGOND3D11RENDERTARGET_HEADER_

#include "ArgonD3D11Device.h"
#include <Standard/ArgonStandard.h>
#include <Interface/ISurface.h>

#include <Interface/IMessageBoardReader.h>
#include <Interface/IArgonUnknownImp.h>

namespace Argon
{
	class D3D11RenderTarget : public IArgonUnknownImp2<ISurface, GUID_ISurface, IMessageBoardReader, GUID_IMessageBoardReader>
	{
	public:
		D3D11RenderTarget(uint Width, uint Height, ISurface::Format Format);
		
		///LOAD(BOOL)
		///
		///Load the rendertarget this is where the render target is created
		///
		///No Params:
		bool Load();

		///UNLOAD(BOOL)
		///
		///Unload the render target and all of its contenst
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

		///READMESSAGE(VOID)
		///
		///Read a posted message from the message board
		///
		///Param MessageBoard: The message board that send the message for the reader
		void ReadMessage(IMessageBoard* MessageBoard, uint Message);

		///(VOID)
		///
		///Internal Use
		///Get the DirectX Texture RenderTarget
		///
		///No Params:
		ID3D11RenderTargetView* GetTexture();

	protected:
		~D3D11RenderTarget();
		ID3D11RenderTargetView*			m_RenderTarget;

		uint							m_Height;
		uint							m_Width;
		ISurface::MemoryPool			m_Pool;
	};

} //Namespace

#endif //_ARGOND3D11RENDERTARGET_HEADER_