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
		D3D11RenderTarget(uint Width, uint Height, Format Format);
		D3D11RenderTarget(ID3D11RenderTargetView* DesiredTarget);
		
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
		MemoryPool GetPoolType();

		///READMESSAGE(VOID)
		///
		///Read a posted message from the message board
		///
		///Param MessageBoard: The message board that send the message for the reader
		void ReadMessage(IMessageBoard* MessageBoard, uint Message);

		///GETTEXTURE(D3D11RENDERTARGETVIEW)
		///
		///Internal Use
		///Get the DirectX Texture RenderTarget
		///
		///No Params:
		ID3D11RenderTargetView* GetTexture();

		///GETTEXTURE(D3D11RENDERTARGETVIEW)
		///
		///Internal Use
		///Clear the render target
		///
		///Param Alpha: The Alpha value of the color that will begin at the start of the frame
		///Param Alpha: The Red value of the color that will begin at the start of the frame
		///Param Alpha: The Green value of the color that will begin at the start of the frame
		///Param Alpha: The Blue value of the color that will begin at the start of the frame
		void Clear(uint Alpha, uint Red, uint Green, uint Blue);

	protected:
		~D3D11RenderTarget();
		ID3D11RenderTargetView*			m_RenderTarget;

		uint							m_Height;
		uint							m_Width;
		MemoryPool			m_Pool;
		Format				m_Format;
	};

} //Namespace

#endif //_ARGOND3D11RENDERTARGET_HEADER_