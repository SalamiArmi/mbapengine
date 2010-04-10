#include "RenderingSystem.h"
#include "RenderTarget.h"
#include "DxUtils.h"

namespace OOS
{
	RenderingSystem::RenderingSystem(Window* Window) : m_Running(true), m_Window(Window)
	{
		HRESULT hr = 0;

		DXGI_SWAP_CHAIN_DESC SwapChainDesc;
		ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));

		SwapChainDesc.BufferCount = 1;

		//Set the width and Height of the back buffer
		SwapChainDesc.BufferDesc.Width = m_Window->getWidth();
		SwapChainDesc.BufferDesc.Height = m_Window->getHeight();

		//Set the surface to be 32 bit
		SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		//Set the refresh rate to be 60 frames per second
		SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		//Set the output Window
		SwapChainDesc.OutputWindow = m_Window->getWindowHandle();

		//No multisampling at the moment
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.SampleDesc.Quality = 0;

		//Windowed mode
		SwapChainDesc.Windowed = TRUE;

		hr = D3D10CreateDeviceAndSwapChain(NULL, //Use the default Adapter
			D3D10_DRIVER_TYPE_HARDWARE, 
			NULL, //Not using DLL for rendering
			D3D10_CREATE_DEVICE_DEBUG, //Allow debug output
			D3D10_SDK_VERSION, //use the current SDK
			&SwapChainDesc,
			&m_SwapChain,
			&m_Device);
	}

	RenderingSystem::~RenderingSystem()
	{
	}

	bool RenderingSystem::InitInstance()
	{
		if ( FAILED ( m_SwapChain->GetBuffer ( 0, __uuidof( ID3D10Texture2D ), ( LPVOID* )&m_BackBuffer ) ) )
		{
			return false;
		}

		//Create a QaueryInteface
		if ( FAILED( m_Device->QueryInterface(__uuidof(ID3D10InfoQueue), (LPVOID*)&m_MessageQueue ) ) )
		{
			return false;	
		}

		m_MessageQueue->SetMuteDebugOutput(false); //Do muting
		m_MessageQueue->SetMessageCountLimit(-1); //Unlimited messages

		return true;
	}

	bool RenderingSystem::RenderOneFrame()
	{
		HRESULT hr = S_OK;

		assert( m_Device );

		m_Device->ClearState();

		//Present the Back buffer to the screen
		if ( FAILED ( m_SwapChain->Present( 0, 0 ) ) )
		{
			return false;
		}		
		
		return true;
	}

	void RenderingSystem::Cleanup()
	{
		SafeRelease( m_MessageQueue );
		SafeRelease( m_SwapChain );
		SafeRelease( m_Device );
	}

	ID3D10Device* RenderingSystem::getDx10Device()
	{
		return m_Device;
	}

	ID3D10Texture2D* OOS::RenderingSystem::getBackBuffer()
	{
		return m_BackBuffer;
	}
}