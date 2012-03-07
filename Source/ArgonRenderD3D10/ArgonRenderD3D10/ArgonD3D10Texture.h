#ifndef _ARGOND3D10TEXTURE_HEADER_
#define _ARGOND3D10TEXTURE_HEADER_


#include <Interface/ITexture.h>

namespace Argon
{
	class D3D10Texture : IArgonUnknownImp<ITexture, GIID_ITexture>
	{
	public:
		bool		UnLoad();
		bool		Load();

		///GETHEIGHT(UNSIGNEDINT)
		///
		///Get the Height of the Surface
		///
		///No Params:
		uint GetHeight();

		///GETWIDTH(UNSIGNEDINT)
		///
		///Get the Width of the Surface
		///
		///No Params
		uint GetWidth();

		///GETMIPLEVELCOUNT(UNSIGNEDINT)
		///
		///Get how many MipMaps this Texture Resource contains
		///
		///No Params:
		uint GetMipLevelCount();

		///GETMIPLEVEL(ISURFACE)
		///
		///Get a specific MipLevel
		///
		///Param MipIndex: The Index of the desired MipMap
		ISurface* GetMipLevel(uint MipIndex);

		///GETRENDERABLE(BOOL)
		///
		///Can the Texture be Rendered to Via the surface
		///
		///No Params:
		bool GetRenderable();

	private:
		bool	m_Renderable;
		uint	m_Width;
		uint	m_Height;
	};

} //Namespace

#endif //_ARGOND3D10TEXTURE_HEADER_