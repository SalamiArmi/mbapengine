#include "ArgonD3D11Driver.h"
#include "ArgonD3D11VideoMode.h"
#include "assert.h"

#pragma warning(disable : 4996)

namespace Argon
{
	D3D11Driver::D3D11Driver(D3D11Device* Device, uint AdapterIndex, IDXGIAdapter1* Adapter)
		: m_Device(Device),
		m_AdapterIndex(AdapterIndex),
		m_Adapter(Adapter)
	{
		GetModeList();
	}

	D3D11Driver::~D3D11Driver()
	{
	}

	bool D3D11Driver::Load()
	{
		assert(m_RefCount > 0);
		++m_RefCount;

		return true;
	}

	String D3D11Driver::GetName()
	{
		DXGI_ADAPTER_DESC1 AdapterDesc;
		m_Adapter->GetDesc1(&AdapterDesc); //Get the adapter description

		size_t Size = wcslen(AdapterDesc.Description);
		char* Str = new char[Size+1];
		wcstombs(Str, AdapterDesc.Description, Size);  //Make a strng
		Str[Size] ='\0';
		String Description = Str;
		delete Str;

		return String(Description); //Return the String

	}

	String D3D11Driver::GetDescription()
	{
		return GetName();
	}

	IVideoMode* D3D11Driver::GetVideoMode(uint Index)
	{
		return m_VideoModes.At(Index);
	}

	uint D3D11Driver::GetVideoModeCount()
	{
		return m_VideoModes.Size();
	}

	void D3D11Driver::GetModeList()
	{
		HRESULT hr = S_OK;
		IDXGIOutput* Output;
		for(uint Index = 0; ; ++Index)
		{	
			m_Adapter->EnumOutputs(Index, &Output);
			if(hr == DXGI_ERROR_NOT_FOUND || Output == NULL)
				return;
			else if(FAILED(hr))
				return; //SHOULD NOT HAPPEN
			else //Worked
			{
				uint ModeCount = 512; //Max Modes
				DXGI_MODE_DESC* Desc = new DXGI_MODE_DESC[ ModeCount ];
			
				/*
					Note:
					Could have more Formats then just DXGI_FORMAT_R8G8B8A8_UNORM
				*/
				
				hr = Output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &ModeCount, Desc ); //Fill the Modes Desc list with supported modes and get the Number of supported modes
				DXGI_OUTPUT_DESC OutputDesc;
				Output->GetDesc(&OutputDesc);
				for(uint ModeIndex = 0; ModeIndex < ModeCount; ++ModeIndex)
				{
					D3D11VideoMode* VideoMode = new D3D11VideoMode(OutputDesc, Desc[ModeIndex]); //can be used for multi-moniter support
					m_VideoModes.Push_Back(VideoMode);
				}
			}
		}
	}

	IDXGIAdapter1*	D3D11Driver::GetAdapter()
	{
		return m_Adapter;
	}

} //Namespace