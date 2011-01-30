#include "ArgonD3D11Device.h"
#include "ArgonD3D11Driver.h"
#include "ArgonD3D11VideoMode.h"

#include <Standard/ArgonMemory.h>

#include <assert.h>

namespace Argon
{

	D3D11Device::D3D11Device()
		: m_Device(NULL)
	{
	}

	D3D11Device::~D3D11Device()
	{
	}

	bool D3D11Device::Load()
	{
		assert(m_Device == NULL);

		HRESULT hr = S_OK;

		hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&m_Factory); //Create the factory
		if(FAILED(hr))
		{
			//Log internal Error
		}

		if(GetSupportedDrivers())
		{
			//Log message complete
		}
		else
		{
			//log message failed
		}

		return false;
	}

	bool D3D11Device::Unload()
	{
		m_Factory->Release(); //Release the Factory

		return false;
	}

	ID3D11Device* D3D11Device::GetDevice()
	{
		assert(m_Device);
		return m_Device;
	}

	ID3D11DeviceContext* D3D11Device::GetDeviceContext()
	{
		assert(m_DeviceContext);
		return m_DeviceContext;
	}

	IDXGISwapChain* D3D11Device::GetSwapChain()
	{
		assert(m_SwapChain);
		return m_SwapChain;
	}
	
	bool D3D11Device::GetSupportedDrivers()
	{
		//Log message Getting Supported Drivers
		for(uint Index = 0; ; ++Index)
		{
			IDXGIAdapter1* Adapter;
			HRESULT hr = m_Factory->EnumAdapters1(Index, &Adapter);
			if(hr == DXGI_ERROR_NOT_FOUND)
			{
				hr = S_OK;
				break;
			}
			if(FAILED(hr))
			{
				delete Adapter;
				return false;
			}

			//Success create new driver
			D3D11Driver* Driver = new ("D3D11Driver") D3D11Driver(this, Index, Adapter);
			m_Drivers.Push_Back(Driver);
		}
		return true;
	}

	uint D3D11Device::GetDriverCount()
	{
		return m_Drivers.Size();
	}

	IDriver* D3D11Device::GetDriver(uint Index)
	{
		return m_Drivers.At(Index);
	}

	bool D3D11Device::CreateDevice(uint DriverIndex, uint VideoModeIndex, void* Window)
	{
		D3D11Driver* Driver = (D3D11Driver* )GetDriver(DriverIndex);

		if(Driver)
		{
			D3D11VideoMode* VideoMode = (D3D11VideoMode* )Driver->GetVideoMode(VideoModeIndex);

			if(VideoMode)
			{

				//		D3D11_CREATE_DRVICE_FLAG Flags;
				//		
				//		if(!MultiThreadedRendering)
				//			Flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
				//
				//#		if _DEBUG
				//			Flags |= D3D11_CREATE_DEVICE_DEBUG;
				//#		endif

				DXGI_SWAP_CHAIN_DESC ChainDesc;

				//Buffer Dexcription
				ChainDesc.BufferDesc.Width = VideoMode->GetWidth();
				ChainDesc.BufferDesc.Height = VideoMode->GetHeight();
				
				ChainDesc.BufferDesc.RefreshRate.Numerator = VideoMode->GetRefereshRate().x / 1000;
				ChainDesc.BufferDesc.RefreshRate.Denominator = VideoMode->GetRefereshRate().y / 1000;
				
				ChainDesc.BufferDesc.Format = VideoMode->GetMode().Format;
				
				ChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; 
				ChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
				
				//Sample Description
				ChainDesc.SampleDesc.Count = 1;
				ChainDesc.SampleDesc.Quality = 0;

				//Output Window
				if(Window)
				{
					ChainDesc.OutputWindow = (HWND)Window; 
					ChainDesc.Windowed = true;
				}
				else
				{
					ChainDesc.OutputWindow = NULL;
					ChainDesc.Windowed = false;
				}

				//Swap Effect
				ChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

				//Buffer Count
				ChainDesc.BufferCount = 1;
				ChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

				//Flags
				uint DeviceFlags = 0;
//
//#if _DEBUG
//				DeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif
//
//				//Single Threaded
//				DeviceFlags |= D3D11_CREATE_DEVICE_SINGLETHREADED;

				ChainDesc.Flags = D3D11_CREATE_DEVICE_DEBUG;

				D3D_FEATURE_LEVEL FeatureLevel[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };

				/*
					TODO MAKE A SINGLE DEVICE WHICH CAN TAKE MULTIPLE SWAPCHAINS
				*/

				HRESULT hr = S_OK;
				if(FAILED(hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, FeatureLevel, 2, D3D11_SDK_VERSION, &ChainDesc, &m_SwapChain, &m_Device, NULL, &m_DeviceContext)))
				{
					//Log Internal error
					return false;
				}
				else
				{
					//Set the Width and Height of the render system
					return true;
				}
			}
			else
			{
				//Log internal Error
				return false;
			}
		}
		else
		{
			//Log Internal Error
			return false;
		}
		return true;
	}

} //Namespace