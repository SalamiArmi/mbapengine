#include "ArgonD3D11DepthStencil.h"
#include "ArgonD3D11RenderSystem.h"
#include "ArgonD3D11Utils.h"

namespace Argon
{
	D3D11DepthStencil::D3D11DepthStencil(uint Width, uint Height, ISurface::Format Format)
		: m_Height(Height),
		m_Width(Width),
		m_Format(Format)
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

		//D3D11RenderSystem::GetDevice()->

		return false;
	}

} //Namespace