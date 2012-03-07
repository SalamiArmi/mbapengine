#ifndef _ARGOND3D10DEVICE_HEADER_
#define _ARGOND3D10DEVICE_HEADER_

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonVector.h>
#include <Interface/IDriver.h>

#include <Interface/IMessageBoard.h>

#include "D3D10.h"
#include "D3DX10.h"

namespace Argon
{
	class D3D10Device
	{
	public:
		D3D10Device();
		~D3D10Device();
		
		bool Load();
		bool Unload();

		///GETDEVICE(ID3D10DEVICE)
		///
		///Get the DirectX11 Device
		///
		///No Params:
		ID3D10Device*			GetDevice();

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

		///DUMPMESSAGES(VOID)
		///
		///Dump all messages from the device message queue
		///
		///No Params:
		void					DumpMessages();

	protected:

		///GETSUPPORTEDDRIVERS(VOID)
		///
		///Get all the supported drivers for this device
		///
		///No Params:
		bool			GetSupportedDrivers();

	private:
		ID3D10Device*			m_Device;
		IDXGISwapChain*			m_SwapChain;
		IDXGIFactory*			m_Factory;
		ID3D10InfoQueue*		m_MessageQueue;

		Vector<IDriver*>		m_Drivers;
	};
} //Namespace

#endif //_ARGONDEVICED3D10_HEADER_