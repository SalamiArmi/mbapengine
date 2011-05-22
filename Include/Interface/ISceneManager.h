#ifndef _ISCENEMANAGER_HEADER_
#define _ISCENEMANAGER_HEADER_

#include "IArgonUnknown.h"

namespace Argon
{
	class IRoot;

	DeclareBasedInterface(ISceneManager, IArgonUnknown)
		
		///GETCREATOR(ROOT)
		///
		///Get the Root whom Created this object
		///
		///No Params:
		IRoot*			GetCreator();

	EndInterface(ISceneManager)

} //Namespace

#endif //_ISCENEMANAGER_HEADER_