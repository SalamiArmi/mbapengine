#ifndef _ARGONDEVICED3D11_HEADER_
#define _ARGONDEVICED3D11_HEADER_

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonVector.h>
#include <Interface/IDriver.h>

#include <Interface/IMessageBoard.h>

#include "D3D11.h"
#include "D3DX11.h"
#include "DXGI.h"

namespace Argon
{
	class D3D11Device
	{
	public:
		D3D11Device();
		~D3D11Device();
		
		bool Load();
		bool Unload();

		///GETDEVICE(ID3D11DEVICE)
		///
		///Get the DirectX11 Device
		///
		///No Params:
		ID3D11Device*			GetDevice();

		///GETDEVICECONTEXT(VOID)
		///
		///Get the device context, the device context does most of the rendering for directX11
		///
		///No Params:
		ID3D11DeviceContext*	GetDeviceContext();

		///GETSWAPCHAIN(IDXGISWAPCHAIN)
		///
		///Get the Swap chain used for this device
		///
		///No Params:
		IDXGISwapChain*			GetSwapChain();

		///GETDRIVERCOUNT(UNSIGNEDINT)
		///
		///Get the total amount of drivers this device can handle
		///
		///No Params:
		uint					GetDriverCount();
		
		///GETDRIVER(IDRIVER)
		///
		///Get a supported driver
		///
		///
		///Param Index: The Driver to retrieve
		IDriver*				GetDriver(uint Index);

		///CREATEDEVICE(BOOL)
		///
		///Create a new Device Specific to the paramater Flags
		///
		///Param DriverIndex: The driver that will be used to create the Device
		///Param VideoModeIndex: Get the Video Mode Index, from the video driver
		///Param Window: The window that will be used to render to
		bool					CreateDevice(uint DriverIndex, uint VideoModeIndex, void* Window);

	protected:

		///GETSUPPORTEDDRIVERS(VOID)
		///
		///Get all the supported drivers for this device
		///
		///No Params:
		bool			GetSupportedDrivers();

	private:
		ID3D11Device*			m_Device;
		IDXGISwapChain*			m_SwapChain;
		IDXGIFactory1*			m_Factory;

		Vector<IDriver*>		m_Drivers;

		ID3D11DeviceContext*	m_DeviceContext;
	};
} //Namespace

#endif //_ARGONDEVICED3D11_HEADER_