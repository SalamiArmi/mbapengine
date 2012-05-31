#ifndef _IARGONUNKNOWN_HEADER_
#define _IARGONUNKNOWN_HEADER_

#include "ArgonInterface.h"
#include <Standard/ArgonStandard.h>

namespace Argon
{
	DeclareInterface(IArgonUnknown)
		
		///QUERYINTERFACE(BOOL)
		///
		///Query a interface and check if anouther interface is implemented
		///
		///Param GUID: The Global Unique Idinitfier for the interface
		///Param Out: The object that will be returned if successfull
		bool QueryInterface(GUID Guid, void** Out) = 0;

		///LOAD(BOOL)
		///
		///Load the Interface All interfaces must use this
		///
		///No Params:
		bool Load() = 0;

		///RELEASE(BOOL)
		///
		///Either Release a reference or release the object
		///
		///No Params:
		bool UnLoad() = 0;

		///GETREF(UNSIGNEDLONG)
		///
		///Get the current reference count of this object
		///
		///No Params:
		ulong GetRef() = 0;

		///ADDREF(VOID)
		///
		///Add a reference to this object
		///
		///No Params:
		ulong AddRef() = 0;

	EndInterface(IArgonUnknown) //Interface
} //Namespace

#endif //_IARGONUNKNOWN_HEADER_