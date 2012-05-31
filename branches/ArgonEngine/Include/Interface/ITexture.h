#ifndef _ARGONITEXTURE_HEADER_
#define _ARGONITEXTURE_HEADER_

#include "IArgonUnknown.h"
#include <Interface/ISurface.h>

namespace Argon
{
	DeclareBasedInterface(ITexture, ISurface)

		///GETMIPLEVELCOUNT(UNSIGNEDINT)
		///
		///Get how many MipMaps this Texture Resource contains
		///
		///No Params:
		virtual uint GetMipLevelCount() = 0;

		///GETMIPLEVEL(ISURFACE)
		///
		///Get a specific MipLevel
		///
		///Param MipIndex: The Index of the desired MipMap
		virtual ISurface* GetMipLevel(uint MipIndex) = 0;

		///GETRENDERABLE(BOOL)
		///
		///Can the Texture be Rendered to Via the surface
		///
		///No Params:
		virtual bool GetRenderable() = 0;
		
	EndInterface(ITexture)
} //Namespace

#endif //_ARGONITEXTURE_HEADER_
