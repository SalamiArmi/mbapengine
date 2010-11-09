#ifndef _IDRIVER_HEADER_
#define _IDRIVER_HEADER_

#include "IArgonUnknown.h"
#include "IVideoMode.h"

#include <Standard/ArgonString.h>

namespace Argon
{
	DeclareBasedInterface(IDriver, IArgonUnknown) 

		///GETNAME(STRING)
		///
		///Get the drivers name
		///
		///No Params:
		String			GetName()						= 0;
		
		///GETDESCRIPTION(STRING)
		///
		///Get the description of the driver
		///
		///No Params:
		String			GetDescription()				= 0;

		///GETVIDEOMODE(IVIDEOMODE)
		///
		///Get a supported Video mode
		///
		///Param Index: Which video mode to retrieve
		IVideoMode*		GetVideoMode(uint Index)		= 0;

		///GETVIDEOMODECOUNT(UNSIGNEDINT)
		///
		///Get the total amount of videomodes for this driver
		///
		///No Params:
		uint			GetVideoModeCount()				= 0;

	EndInterface(IDriver) //Interface
}//Namespace

#endif //_IDRIVER_HEADER_