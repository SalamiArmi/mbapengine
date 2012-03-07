#include "ArgonD3D10Viewport.h"

namespace Argon
{
	D3D10Viewport::D3D10Viewport(Vector2T<uint> Dimensions, Vector2T<uint> Position)
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

	D3D10Viewport::~D3D10Viewport()
	{
	}

	bool D3D10Viewport::Load()
	{	
		assert(m_RefCount == 0);
		++m_RefCount;
		return true;
	}

	bool D3D10Viewport::UnLoad()
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

	bool D3D10Viewport::Begin()
	{
		D3D10RenderSystem::instance()->GetDevice()->GetDevice()->RSSetViewports(0, &m_Viewport);
		return true;
	}

	bool D3D10Viewport::End()
	{
		return true;
	}

	Vector2T<uint> D3D10Viewport::GetPosition()
	{
		return m_Position;
	}

	Vector2T<uint> D3D10Viewport::GetDimensions()
	{
		return m_Dimensions;
	}

	void D3D10Viewport::SetEnabled(bool Enabled)
	{
		m_Enabled = Enabled;
	}

	bool D3D10Viewport::GetEnabled()
	{
		return m_Enabled;
	}

	void D3D10Viewport::SetCamera(Camera* Cam)
	{
		m_Camera = Cam;
	}

	Camera* D3D10Viewport::GetCamera()
	{
		return m_Camera;
	}

	void D3D10Viewport::SetClearColor(size_t Alpha, size_t Red, size_t Green, size_t Blue)
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

	size_t* D3D10Viewport::GetClearColor()
	{
		return m_ClearColor;
	}

	D3D10_VIEWPORT& D3D10Viewport::GetD3D10Viewport()
	{
		return m_Viewport;
	}

} //Namespace