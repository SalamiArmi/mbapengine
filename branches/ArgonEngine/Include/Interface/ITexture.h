#ifndef _ARGONITEXTURE_HEADER_
#define _ARGONITEXTURE_HEADER_

#include "IArgonUnknown.h"
#include <Interface/ISurface.h>

namespace Argon
{
	DeclareBasedInterface(ITexture, IArgonUnknown)

		///GETHEIGHT(UNSIGNEDINT)
		///
		///Get the Height of the Surface
		///
		///No Params:
		uint GetHeight() = 0;

		///GETWIDTH(UNSIGNEDINT)
		///
		///Get the Width of the Surface
		///
		///No Params
		uint GetWidth() = 0;

		///GETMIPLEVELCOUNT(UNSIGNEDINT)
		///
		///Get how many MipMaps this Texture Resource contains
		///
		///No Params:
		uint GetMipLevelCount() = 0;

		///GETMIPLEVEL(ISURFACE)
		///
		///Get a specific MipLevel
		///
		///Param MipIndex: The Index of the desired MipMap
		ISurface* GetMipLevel(uint MipIndex) = 0;

		///GETRENDERABLE(BOOL)
		///
		///Can the Texture be Rendered to Via the surface
		///
		///No Params:
		bool GetRenderable() = 0;
		
	EndInterface(ITexture)
} //Namespace

#endif //_ARGONITEXTURE_HEADER_
