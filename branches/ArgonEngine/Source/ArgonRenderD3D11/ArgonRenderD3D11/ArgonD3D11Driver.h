#ifndef _ARGOND3D11DRIVER_HEADER_
#define _ARGOND3D11DRIVER_HEADER_

#include "ArgonD3D11Device.h"

#include <Interface/IArgonUnknownImp.h>
#include <Interface/IDriver.h>

namespace Argon
{
	class D3D11Driver : ArgonImplements IArgonUnknownImp<IDriver, GUID_IDriver>
	{
	public:
		D3D11Driver(D3D11Device* Device, uint AdapterIndex, IDXGIAdapter1* Adapter);

		///GETNAME(STRING)
		///
		///Get the drivers name
		///
		///No Params:
		String			GetName();

		///GETDESCRIPTION(STRING)
		///
		///Get the description of the driver
		///
		///No Params:
		String			GetDescription();

		///GETVIDEOMODE(IVIDEOMODE)
		///
		///Get a supported Video mode
		///
		///Param Index: Which video mode to retrieve
		IVideoMode*		GetVideoMode(uint Index);

		///GETVIDEOMODECOUNT(UNSIGNEDINT)
		///
		///Get the total amount of videomodes for this driver
		///
		///No Params:
		uint			GetVideoModeCount();

		////////////////////////////////////////////////////////////////////
		// Internal Functions

		///GETADAPTER(IDXGIADAPTER1)
		///
		///Get the Adapter specific to this Driver
		///
		///No Params:
		IDXGIAdapter1*	GetAdapter();

	protected:
		virtual ~D3D11Driver();

		///GETMODELIST(VOID)
		///
		///Get the supported modes for this driver
		///
		///No Params:
		virtual void GetModeList();

	private:
		D3D11Device*		m_Device;
		uint				m_AdapterIndex;
		IDXGIAdapter1*		m_Adapter;
		Vector<IVideoMode*> m_VideoModes;
	}; //Class
} //Namespace

#endif //_ARGOND3D11DRIVER_HEADER_