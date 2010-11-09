#ifndef _IVIDEOMODE_HEADER_
#define _IVIDEOMODE_HEADER_

#include "IArgonUnknown.h"
#include <Standard/ArgonString.h>
#include <Standard/ArgonVector2.h>

namespace Argon
{
	DeclareBasedInterface(IVideoMode, IArgonUnknown)

		///GETDESCRIPTION(STRING)
		///
		///Get the Description of the Video mode
		///Uses c style strings
		///
		///No Params:
		String GetDescription();

		///GETCOLORDEPTH(UNSIGNEDINT)
		///
		///Get the supported color depth for this video mode
		///
		///No Params:
		uint GetColorDepth();

		///GETWIDTH(UNSIGNEDINT)
		///
		///Get the supported width of the resolution
		///
		///No Params:
		uint GetWidth();

		///GETHEIGHT(UNSIGNEDINT)
		///
		///Get the supported height of the resolution
		///
		///No Params:
		uint GetHeight();

		///GETREFRESHRATE(VECTOR2T<uint>)
		///
		///Get the refresh rate as a fraction
		///X = Numerator Y = Denumerator
		///
		///No Params:
		Vector2T<uint> GetRefereshRate();

	EndInterface(IVideoMode) //Interface
} //Namespace

#endif //_IBUFFER_HEADER_