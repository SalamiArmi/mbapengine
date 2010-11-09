#include "ArgonD3D11RenderTarget.h"
#include <Interface/ISurface.h>
#include "ArgonD3D11RenderSystem.h"

namespace Argon
{
	D3D11RenderTarget::D3D11RenderTarget(uint Width, uint Height, ISurface::Format Format)
	{

	}

	D3D11RenderTarget::~D3D11RenderTarget()
	{

	}

	bool D3D11RenderTarget::Load()
	{
		ID3D10Texture2D* BackBuffer;
		D3D11RenderSystem::instance()->GetDevice()->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		D3D11RenderSystem::instance()->GetDevice()->GetDevice()->CreateRenderTargetView(BackBuffer, 0, &m_RenderTexture);
		
		//Release the backbuffer, we no longer have a reference
		BackBuffer->Release();

		return true;
	}

	bool D3D11RenderTarget::UnLoad()
	{
		if(m_RenderTexture->Release() == 0)
		{
			return true;
		}

		//Log Internal Error

		return false;
	}

	uint D3D11RenderTarget::GetHeight()
	{
		return m_Height;
	}

	uint D3D11RenderTarget::GetWidth()
	{
		return m_Width;
	}

	ISurface::MemoryPool D3D11RenderTarget::GetPoolType()
	{
		return m_Pool;
	}

	void D3D11RenderTarget::ReadMessage(IMessageBoard *MessageBoard, uint Message)
	{

	}

	ID3D10Texture2D* D3D11RenderTarget::GetTexture()
	{
		return m_RenderTexture;
	}

} //Namespace