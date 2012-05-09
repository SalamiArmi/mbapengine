#include "ArgonD3D11DepthStencil.h"
#include "ArgonD3D11RenderSystem.h"
#include "ArgonD3D11Utils.h"

namespace Argon
{
	D3D11DepthStencil::D3D11DepthStencil(uint Width, uint Height, Format Format)
		: m_Height(Height),
		m_Width(Width),
		m_Format(Format),
		m_Buffer(NULL),
		m_DepthStencil(NULL)
	{
	}

	D3D11DepthStencil::~D3D11DepthStencil()
	{
	}

	bool D3D11DepthStencil::Load()
	{
		D3D11_TEXTURE2D_DESC Desc;

		//Dimension
		Desc.Width = m_Width;
		Desc.Height = m_Height;

		//Format
		Desc.Format = ArgonFormatToD3D11(m_Format);

		//Extra Settings Hard Coded
		Desc.MipLevels = 1;
		Desc.ArraySize = 1;

		//Use same as swap chain
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		
		//Usage must be default as it is a type of render target
		Desc.Usage = D3D11_USAGE_DEFAULT;

		//Flags
		Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		Desc.CPUAccessFlags = 0;
		Desc.MiscFlags = 0;

		D3D11RenderSystem::instance()->GetDevice()->GetDevice()->CreateTexture2D(&Desc, 0, &m_Buffer);
		D3D11RenderSystem::instance()->GetDevice()->GetDevice()->CreateDepthStencilView(m_Buffer, 0, &m_DepthStencil);

		return true;
	}

	bool D3D11DepthStencil::UnLoad()
	{
		return true;
	}

	uint D3D11DepthStencil::GetHeight()
	{
		return m_Height;
	}

	uint D3D11DepthStencil::GetWidth()
	{
		return m_Width;
	}

	MemoryPool D3D11DepthStencil::GetPoolType()
	{
		return ISurface::POOL_Default;
	}

	ID3D11DepthStencilView* D3D11DepthStencil::GetTexture()
	{
		return m_DepthStencil;
	}

	void D3D11DepthStencil::Clear()
	{
#if _DEBUG
		D3D11Device* Device = D3D11RenderSystem::instance()->GetDevice();
		Device->GetDeviceContext()->ClearDepthStencilView(m_DepthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
#else
		D3D11RenderSystem::instance()->GetDevice()->GetDeviceContext()->ClearDepthStencilView(DepthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
#endif
		
	}

} //Namespace