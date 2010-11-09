#ifndef _ARGOND3D11VIDEOMODE_HEADER_
#define _ARGOND3D11VIDEOMODE_HEADER_

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonString.h>

#include <Interface/IArgonUnknownImp.h>
#include <Interface/IVideoMode.h>

#include "ArgonD3D11Device.h"

namespace Argon
{

	class D3D11VideoMode : ArgonImplements IArgonUnknownImp<IVideoMode, GUID_IVideoMode>
	{
	public:
		D3D11VideoMode(DXGI_OUTPUT_DESC OutputDesc, DXGI_MODE_DESC ModeDesc);

		///////////////////////////////////////////
		// IVideoMode Implementation
		String			GetDescription();
		uint			GetColorDepth();
		uint			GetWidth();
		uint			GetHeight();
		Vector2T<uint>	GetRefereshRate();

		//////////////////////////////////////////
		// Internal Use
		DXGI_MODE_DESC	GetMode();

	protected:
		virtual ~D3D11VideoMode();

	private:
		DXGI_OUTPUT_DESC	m_OutputDesc;
		DXGI_MODE_DESC		m_ModeDesc;
	};

} //Namespace

#endif //_ARGOND3D11VIDEOMODE_HEADER_