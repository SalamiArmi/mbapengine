#include "ArgonD3D11VideoMode.h"
#include <stdio.h>

#pragma warning(disable : 4996)

namespace Argon
{

	D3D11VideoMode::D3D11VideoMode(DXGI_OUTPUT_DESC OutputDesc, DXGI_MODE_DESC ModeDesc)
		: m_OutputDesc(OutputDesc),
		m_ModeDesc(ModeDesc)
	{
	}

	D3D11VideoMode::~D3D11VideoMode()
	{
	}

	String D3D11VideoMode::GetDescription()
	{
		char* Temp = new char[128];
		uint ColorDepth = 16;
		if(m_ModeDesc.Format == DXGI_FORMAT_R8G8B8A8_UNORM || m_ModeDesc.Format == DXGI_FORMAT_R32G32B32A32_TYPELESS ||
			m_ModeDesc.Format == DXGI_FORMAT_R32G32B32A32_FLOAT || m_ModeDesc.Format == DXGI_FORMAT_R32G32B32A32_UINT ||
			m_ModeDesc.Format == DXGI_FORMAT_R32G32B32A32_SINT || m_ModeDesc.Format == DXGI_FORMAT_R32G32B32_TYPELESS ||
			m_ModeDesc.Format == DXGI_FORMAT_R32G32B32_FLOAT || m_ModeDesc.Format == DXGI_FORMAT_R32G32B32_UINT || m_ModeDesc.Format == DXGI_FORMAT_R32G32B32_SINT)
			ColorDepth = 32; //Format is 32bit

		sprintf(Temp, "%d x %d @ %d-bit colour", m_ModeDesc.Width, m_ModeDesc.Height, ColorDepth);
		return String(Temp);
	}

	uint D3D11VideoMode::GetColorDepth()
	{
		uint ColorDepth = 16;
		if(m_ModeDesc.Format == DXGI_FORMAT_R32G32B32A32_TYPELESS || m_ModeDesc.Format == DXGI_FORMAT_R32G32B32A32_FLOAT ||
			m_ModeDesc.Format == DXGI_FORMAT_R32G32B32A32_UINT || m_ModeDesc.Format == DXGI_FORMAT_R32G32B32A32_SINT ||
			m_ModeDesc.Format == DXGI_FORMAT_R32G32B32_TYPELESS || m_ModeDesc.Format == DXGI_FORMAT_R32G32B32_FLOAT ||
			m_ModeDesc.Format == DXGI_FORMAT_R32G32B32_UINT || m_ModeDesc.Format == DXGI_FORMAT_R32G32B32_SINT)
			ColorDepth = 32; //Format is 32bit

		return ColorDepth;
	}

	uint D3D11VideoMode::GetWidth()
	{
		return m_ModeDesc.Width;
	}

	uint D3D11VideoMode::GetHeight()
	{
		return m_ModeDesc.Height;
	}

	Vector2T<uint> D3D11VideoMode::GetRefereshRate()
	{
		return Vector2T<uint>(m_ModeDesc.RefreshRate.Numerator, m_ModeDesc.RefreshRate.Denominator);
	}

	DXGI_MODE_DESC	D3D11VideoMode::GetMode()
	{
		return m_ModeDesc;
	}

} //Namespace