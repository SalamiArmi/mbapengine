#include "System.h"
#include "Viewport.h"
#include "RenderTarget.h"

namespace OOS
{
	RenderTarget::RenderTarget(Viewport *Viewport)
	{
		D3D10_RENDER_TARGET_VIEW_DESC desc;
		ZeroMemory( &desc, sizeof ( desc ) );
		desc.Buffer.NumElements = 1;
		desc.Buffer.ElementWidth = 50;
		desc.Buffer.FirstElement = 0;
		desc.Buffer.ElementOffset = 0;
		desc.Texture2D.MipSlice = 0;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;

		if (FAILED(System::getSingleton().getRenderingSystem()->getDx10Device()->CreateRenderTargetView(System::getSingleton().getRenderingSystem()->getBackBuffer(), NULL, &m_DirectxObject)))
		{
			return;
		}
	}

	void RenderTarget::clear()
	{
		//Clear the current back buffer
		float color[4] = {  0,0,1,1.0f };
		System::getSingleton().getRenderingSystem()->getDx10Device()->ClearRenderTargetView( m_DirectxObject, color );
	}

	RenderTarget::~RenderTarget()
	{

	}

	unsigned int RenderTarget::getHeight(void) const
	{
		return m_Height;
	}

	unsigned int RenderTarget::getWidth(void) const
	{
		return m_Width;
	}

	unsigned int RenderTarget::getNumViewports() const
	{
		return m_Viewports.Count();
	}

	Viewport* RenderTarget::getViewport(unsigned int ViewportIndex) const
	{
		return m_Viewports.at(ViewportIndex);
	}
}