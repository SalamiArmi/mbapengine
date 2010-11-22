#ifndef _ARGOND3D11UTILS_HEADER_
#define _ARGOND3D11UTILS_HEADER_

#include <Interface/ISurface.h>

#include "ArgonD3D11Device.h"

namespace Argon
{
	DXGI_FORMAT ArgonFormatToD3D11(ISurface::Format Format);

} //Namespace
#endif //_ARGOND3D11UTILS_HEADER_