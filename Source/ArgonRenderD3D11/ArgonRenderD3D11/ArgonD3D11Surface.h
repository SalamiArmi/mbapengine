#ifndef _ARGOND3D11SURFACE_HEADER_
#define _ARGOND3D11SURFACE_HEADER_

namespace Argon
{
	class D3D11Surface
	{
	public:

	protected:
		 D3D11_TEXTURE2D_DESC	m_Desc;
		 ID3D11Texture2D*		m_Surface;
	}; //Class
} //Namespace

#endif //_ARGOND3D11SURFACE_HEADER_