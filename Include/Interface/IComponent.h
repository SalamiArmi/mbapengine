#ifndef _ICOMPONENT_HEADER_
#define _ICOMPONENT_HEADER_

#include "IArgonUnknown.h"
#include <Standard/ArgonQString.h>

namespace Argon
{
	DeclareBasedInterface(IComponent, IArgonUnknown)

		///GETNAME(QSTRING)
		///
		///Get the name of the component
		///
		///No Params:
		QString		GetName();
	
	EndInterface(IComponent) //Interface

}//Namespace

#endif //_ICOMPONENT_HEADER_