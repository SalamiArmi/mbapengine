#include "ArgonD3D11Viewport.h"

namespace Argon
{
	D3D11Viewport::D3D11Viewport(Vector2 Dimensions, Vector2 Position)
		: m_Enabled(true),
		m_Dimensions(Dimensions),
		m_Position(Position),
		m_ClearColor(NULL),
		m_Camera(NULL)
	{
		m_RefCount = 0;

		//Create the Viewport
		//Position
		m_Viewport.TopLeftX = Position.x;
		m_Viewport.TopLeftY = Position.y;

		//Dimensions
		m_Viewport.Width = Dimensions.x;
		m_Viewport.Height = Dimensions.y;

		//Default Values
		m_Viewport.MinDepth = 0.0f;
		m_Viewport.MaxDepth = 1.0f;
	}

	D3D11Viewport::~D3D11Viewport()
	{
	}

	bool D3D11Viewport::Load()
	{	
		assert(m_RefCount == 0);
		++m_RefCount;
		return true;
	}

	bool D3D11Viewport::UnLoad()
	{
		if(m_RefCount > 1)
		{
			--m_RefCount;
		}
		else
		{
			IArgonUnknownImp<IViewport, GUID_IViewport>::UnLoad();
		}

		return false;
	}

	bool D3D11Viewport::Begin()
	{
		D3D11RenderSystem::instance()->GetDevice()->GetDeviceContext()->RSSetViewports(0, &m_Viewport);
		return true;
	}

	bool D3D11Viewport::End()
	{
		return true;
	}

	Vector2 D3D11Viewport::GetPosition()
	{
		return m_Position;
	}

	Vector2 D3D11Viewport::GetDimensions()
	{
		return m_Dimensions;
	}

	void D3D11Viewport::SetEnabled(bool Enabled)
	{
		m_Enabled = Enabled;
	}

	bool D3D11Viewport::GetEnabled()
	{
		return m_Enabled;
	}

	void D3D11Viewport::SetCamera(Camera* Cam)
	{
		m_Camera = Cam;
	}

	Camera* D3D11Viewport::GetCamera()
	{
		return m_Camera;
	}

	void D3D11Viewport::SetClearColor(size_t Alpha, size_t Red, size_t Green, size_t Blue)
	{
		if(m_ClearColor)
		{
			delete[] m_ClearColor;
		}

		m_ClearColor = new size_t[4];
		m_ClearColor[0] = Alpha;
		m_ClearColor[1] = Red;
		m_ClearColor[2] = Green;
		m_ClearColor[3] = Blue;
	}

	size_t* D3D11Viewport::GetClearColor()
	{
		return m_ClearColor;
	}

	D3D11_VIEWPORT D3D11Viewport::GetD3D11Viewport()
	{
		return m_Viewport;
	}

} //Namespace