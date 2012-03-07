#include "ArgonD3D10Device.h"
#include "ArgonD3D10Driver.h"
#include "ArgonD3D10VideoMode.h"

#include <Standard/ArgonMemory.h>

#include <assert.h>

namespace Argon
{
#define MAX_DEBUG_MESSAGE 1024

	D3D10Device::D3D10Device()
		: m_Device(NULL)
	{
	}

	D3D10Device::~D3D10Device()
	{
		m_Drivers.Clear();

#if _DEBUG
		assert(m_SwapChain->Release() == 0);
		assert(m_Factory->Release() == 0);
		assert(m_Device->Release() == 0);
#else
		m_SwapChain->Release();
		m_Factory->Release();
		m_Device->Release();
#endif
	}

	bool D3D10Device::Load()
	{
		assert(m_Device == NULL);

		HRESULT hr = S_OK;

		hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_Factory); //Create the factory
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

	bool D3D10Device::Unload()
	{
		m_Factory->Release(); //Release the Factory

		return false;
	}

	ID3D10Device* D3D10Device::GetDevice()
	{
		assert(m_Device);
		return m_Device;
	}

	IDXGISwapChain* D3D10Device::GetSwapChain()
	{
		assert(m_SwapChain);
		return m_SwapChain;
	}
	
	bool D3D10Device::GetSupportedDrivers()
	{
		//Log message Getting Supported Drivers
		for(uint Index = 0; ; ++Index)
		{
			IDXGIAdapter* Adapter;
			HRESULT hr = m_Factory->EnumAdapters(Index, &Adapter);
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
			D3D10Driver* Driver = new D3D10Driver(this, Index, Adapter);
			m_Drivers.Push_Back(Driver);
		}
		return true;
	}

	uint D3D10Device::GetDriverCount()
	{
		return m_Drivers.Size();
	}

	IDriver* D3D10Device::GetDriver(uint Index)
	{
		return m_Drivers.At(Index);
	}

	bool D3D10Device::CreateDevice(uint DriverIndex, uint VideoModeIndex, void* Window)
	{
		D3D10Driver* Driver = (D3D10Driver* )GetDriver(DriverIndex);

		if(Driver)
		{
			D3D10VideoMode* VideoMode = (D3D10VideoMode* )Driver->GetVideoMode(VideoModeIndex);

			if(VideoMode)
			{
				DXGI_SWAP_CHAIN_DESC ChainDesc;
				memset(&ChainDesc, 0x0, sizeof(DXGI_SWAP_CHAIN_DESC));

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

#if _DEBUG
				DeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

				//Single Threaded
				DeviceFlags |= D3D10_CREATE_DEVICE_SINGLETHREADED;

				/*
					TODO MAKE A SINGLE DEVICE WHICH CAN TAKE MULTIPLE SWAPCHAINS
				*/

				HRESULT hr = S_OK;
				if(FAILED(hr = D3D10CreateDeviceAndSwapChain(Driver->GetAdapter(), D3D10_DRIVER_TYPE_HARDWARE, NULL, DeviceFlags, D3D10_SDK_VERSION, &ChainDesc, &m_SwapChain, &m_Device)))
				{
					//Log Internal error
					return false;
				}
				else
				{
					//Set the Width and Height of the render system
					m_Device->QueryInterface(__uuidof(ID3D10InfoQueue), (void**)&m_MessageQueue);

#if _DEBUG
					m_MessageQueue->SetMessageCountLimit((UINT64)-1);
					m_MessageQueue->SetMuteDebugOutput(false);
#else
					m_MessageQueue->SetMessageCountLimit(-1);
					m_MessageQueue->SetMuteDebugOutput(true);
#endif

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
	}

	void D3D10Device::DumpMessages()
	{
		//assert(m_MessageQueue);

		//HRESULT hr = S_OK;

		//while(1)
		//{
		//	//Get the Size of the message
		//	SIZE_T Length = 0;
		//	m_MessageQueue->GetMessage(0, NULL, &Length);
		//	if(Length == 0) break;

		//	D3D10_MESSAGE Message;
		//	hr = m_MessageQueue->GetMessage(0, &Message, &Length);

		//	if(hr == S_OK)
		//	{
		//		char* Output = new char[Message.DescriptionByteLength + 32];
		//		sprintf(Output, "Category(%i) Severity(%i) ID(%i), %s \n", Message.Category, Message.Severity, Message.ID, Message.pDescription);
		//		OutputDebugStringA(Output);
		//	}
		//}
	}

} //Namespace