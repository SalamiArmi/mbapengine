#include "Viewport.h"
#include "RenderTarget.h"

namespace OOS
{
	Viewport::Viewport(Camera* Camera, int Width, int Height, Vector2 Position)
	{
		//Zero memory the viewport
		ZeroMemory(&m_DirectxObject, sizeof(m_DirectxObject));

		//Set the width and height
		m_Width = m_DirectxObject.Width = Width;
		m_Height = m_DirectxObject.Height = Height;

		//Set the position
		m_Position = Position;
		m_DirectxObject.TopLeftX = (INT) Position.x;
		m_DirectxObject.TopLeftY = (INT) Position.y;	

		m_ViewportCamera = Camera;

		//Create a Render Target
		m_RenderTarget = new RenderTarget(this);

		//Create the stencli buffer
		D3D10_TEXTURE2D_DESC DescDepth;
		ZeroMemory ( &DescDepth, sizeof ( DescDepth ) );
		DescDepth.Width = m_Width;
		DescDepth.Height =  m_Height;
		DescDepth.MipLevels = 1;
		DescDepth.ArraySize = 1;
		DescDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		DescDepth.SampleDesc.Count = 1;
		DescDepth.SampleDesc.Quality = 0;
		DescDepth.Usage = D3D10_USAGE_DEFAULT;
		DescDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
		DescDepth.CPUAccessFlags = 0;
		DescDepth.MiscFlags = 0;

		if ( FAILED ( System::getSingleton().getRenderingSystem()->getDx10Device()->CreateTexture2D( &DescDepth, NULL, &m_DepthStencilBuffer ) ) ) return;

		D3D10_DEPTH_STENCIL_DESC StencilDesc;
		ZeroMemory ( &StencilDesc, sizeof( StencilDesc ) );
		StencilDesc.DepthEnable = true;
		StencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
		StencilDesc.DepthFunc = D3D10_COMPARISON_LESS;

		//Stencil test values
		StencilDesc.StencilEnable = true;
		StencilDesc.StencilReadMask = (UINT8)0xFFFFFFFF;
		StencilDesc.StencilWriteMask = (UINT8)0xFFFFFFFF;

		//Stencil op if picel is front
		StencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
		StencilDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
		StencilDesc.FrontFace.StencilPassOp  = D3D10_STENCIL_OP_KEEP;
		StencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

		//Stencil op if picel is back
		StencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
		StencilDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
		StencilDesc.BackFace.StencilPassOp  = D3D10_STENCIL_OP_KEEP;
		StencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

		if ( FAILED ( System::getSingleton().getRenderingSystem()->getDx10Device()->CreateDepthStencilState( &StencilDesc, &m_DepthStencilState ) ) )  return;
		System::getSingleton().getRenderingSystem()->getDx10Device()->OMSetDepthStencilState( m_DepthStencilState, 1 );

		//Create the stencil view
		D3D10_DEPTH_STENCIL_VIEW_DESC StencilViewDesc;
		ZeroMemory( &StencilViewDesc, sizeof ( StencilViewDesc ) );
		StencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		StencilViewDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
		StencilViewDesc.Texture2D.MipSlice = 0;

		if ( FAILED ( System::getSingleton().getRenderingSystem()->getDx10Device()->CreateDepthStencilView( m_DepthStencilBuffer, &StencilViewDesc, &m_DepthStencilView ) ) ) return;

		System::getSingleton().getRenderingSystem()->getDx10Device()->OMSetRenderTargets( 1, m_RenderTarget->getDirectxObjectRef(), m_DepthStencilView );
	}

	Viewport::~Viewport()
	{

	}

	bool Viewport::update()
	{
		m_RenderTarget->clear();
		return true;
	}
}