#ifndef _ARGOND3D10UTILS_HEADER_
#define _ARGOND3D10UTILS_HEADER_

#include <Interface/ISurface.h>

#include "ArgonD3D10Device.h"

namespace Argon
{
	DXGI_FORMAT ArgonFormatToD3D10(ISurface::Format Format);

} //Namespace
#endif //_ARGOND3D10UTILS_HEADER_