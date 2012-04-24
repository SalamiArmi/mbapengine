#include "ArgonD3D10DepthStencil.h"
#include "ArgonD3D10RenderSystem.h"
#include "ArgonD3D10Utils.h"

namespace Argon
{
	D3D10DepthStencil::D3D10DepthStencil(uint Width, uint Height, Format Format)
		: m_Height(Height),
		m_Width(Width),
		m_Format(Format),
		m_Buffer(NULL),
		m_DepthStencil(NULL)
	{
	}

	D3D10DepthStencil::~D3D10DepthStencil()
	{
	}

	bool D3D10DepthStencil::Load()
	{
		D3D10_TEXTURE2D_DESC Desc;

		//Dimension
		Desc.Width = m_Width;
		Desc.Height = m_Height;

		//Format
		Desc.Format = ArgonFormatToD3D10(m_Format);

		//Extra Settings Hard Coded
		Desc.MipLevels = 1;
		Desc.ArraySize = 1;

		//Use same as swap chain
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		
		//Usage must be default as it is a type of render target
		Desc.Usage = D3D10_USAGE_DEFAULT;

		//Flags
		Desc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
		Desc.CPUAccessFlags = 0;
		Desc.MiscFlags = 0;

		D3D10RenderSystem::instance()->GetDevice()->GetDevice()->CreateTexture2D(&Desc, 0, &m_Buffer);
		D3D10RenderSystem::instance()->GetDevice()->GetDevice()->CreateDepthStencilView(m_Buffer, 0, &m_DepthStencil);

		return true;
	}

	bool D3D10DepthStencil::UnLoad()
	{
		return true;
	}

	uint D3D10DepthStencil::GetHeight()
	{
		return m_Height;
	}

	uint D3D10DepthStencil::GetWidth()
	{
		return m_Width;
	}

	MemoryPool D3D10DepthStencil::GetPoolType()
	{
		return POOL_Default;
	}

	ID3D10DepthStencilView* D3D10DepthStencil::GetTexture() const
	{
		return m_DepthStencil;
	}

	void D3D10DepthStencil::Clear()
	{
#if _DEBUG
		D3D10Device* Device = D3D10RenderSystem::instance()->GetDevice();
		Device->GetDevice()->ClearDepthStencilView(m_DepthStencil, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
#else
		D3D10RenderSystem::instance()->GetDevice()->GetDevice()->ClearDepthStencilView(m_DepthStencil, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
#endif
		
	}

} //Namespace