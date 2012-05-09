#include "ArgonD3D11RenderTarget.h"
#include <Interface/ISurface.h>
#include "ArgonD3D11RenderSystem.h"
#include "ArgonD3D11Utils.h"

#include "D3D11.h"
#include "D3DX11.h"
#include "DXGI.h"

namespace Argon
{
	D3D11RenderTarget::D3D11RenderTarget(uint Width, uint Height, Format Format)
		: m_Width(Width),
		m_Height(Height),
		m_Pool(ISurface::POOL_Managed),
		m_Format(Format)
	{

	}

	D3D11RenderTarget::D3D11RenderTarget(ID3D11RenderTargetView* DesiredTarget)
		: m_RenderTarget(DesiredTarget),
		m_Width(0),
		m_Height(0),
		m_Pool(ISurface::POOL_Managed),
		m_Format(FORMAT_Unknown)
	{
	}

	D3D11RenderTarget::~D3D11RenderTarget()
	{

	}

	bool D3D11RenderTarget::Load()
	{
		D3D11_RENDER_TARGET_VIEW_DESC Desc;
		Desc.Texture2D.MipSlice = 1;
		Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		Desc.Format = ArgonFormatToD3D11(m_Format);
	

		D3D11RenderSystem::instance()->GetDevice()->GetDevice()->CreateRenderTargetView(NULL, &Desc, &m_RenderTarget);
		return true;
	}

	bool D3D11RenderTarget::UnLoad()
	{
		if(m_RenderTarget->Release() == 0)
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

	MemoryPool D3D11RenderTarget::GetPoolType()
	{
		return m_Pool;
	}

	void D3D11RenderTarget::ReadMessage(IMessageBoard *MessageBoard, uint Message)
	{

	}

	ID3D11RenderTargetView* D3D11RenderTarget::GetTexture()
	{
		return m_RenderTarget;
	}

	void D3D11RenderTarget::Clear(uint Alpha, uint Red, uint Green, uint Blue)
	{
		float Color[] = { (float)Red, (float)Green, (float)Blue, (float)Alpha };
		D3D11RenderSystem::instance()->GetDevice()->GetDeviceContext()->ClearRenderTargetView(m_RenderTarget, Color);
	}

} //Namespace