#include "ArgonD3D10RenderTarget.h"
#include <Interface/ISurface.h>
#include "ArgonD3D10RenderSystem.h"
#include "ArgonD3D10Utils.h"

#include "D3D10.h"
#include "D3DX10.h"
#include "DXGI.h"

namespace Argon
{
	D3D10RenderTarget::D3D10RenderTarget(uint Width, uint Height, Format TargetFormat)
		: m_Width(Width),
		m_Height(Height),
		m_Pool(MemoryPool::POOL_Default),
		m_Format(TargetFormat)
	{

	}

	D3D10RenderTarget::D3D10RenderTarget(ID3D10RenderTargetView* DesiredTarget)
		: m_RenderTarget(DesiredTarget),
		m_Width(0),
		m_Height(0),
		m_Pool(MemoryPool::POOL_Default),
		m_Format(FORMAT_Unknown)
	{
	}

	D3D10RenderTarget::~D3D10RenderTarget()
	{

	}

	bool D3D10RenderTarget::Load()
	{
		D3D10_RENDER_TARGET_VIEW_DESC Desc;
		Desc.Texture2D.MipSlice = 1;
		Desc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
		Desc.Format = ArgonFormatToD3D10(m_Format);
	

		D3D10RenderSystem::instance()->GetDevice()->GetDevice()->CreateRenderTargetView(NULL, &Desc, &m_RenderTarget);
		return true;
	}

	bool D3D10RenderTarget::UnLoad()
	{
		if(m_RenderTarget->Release() == 0)
		{
			return true;
		}

		//Log Internal Error

		return false;
	}

	uint D3D10RenderTarget::GetHeight()
	{
		return m_Height;
	}

	uint D3D10RenderTarget::GetWidth()
	{
		return m_Width;
	}

	MemoryPool D3D10RenderTarget::GetPoolType()
	{
		return m_Pool;
	}

	void D3D10RenderTarget::ReadMessage(IMessageBoard *MessageBoard, uint Message)
	{
		MessageBoard;
		Message;
	}

	ID3D10RenderTargetView* D3D10RenderTarget::GetTexture() const
	{
		return m_RenderTarget;
	}

	void D3D10RenderTarget::Clear(float Alpha, float Red, float Green, float Blue)
	{
		float Color[] = { Red, Green, Blue, Alpha };
		D3D10RenderSystem::instance()->GetDevice()->GetDevice()->ClearRenderTargetView(m_RenderTarget, Color);
	}

} //Namespace