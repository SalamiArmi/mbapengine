#ifndef _IBUFFER_HEADER_
#define _IBUFFER_HEADER_

#include "IArgonUnknown.h"

namespace Argon
{
	DeclareBasedInterface(IBuffer, IArgonUnknown) 
		
		enum Usage
		{
			USAGE_Dynamic = 0,
			USAGE_Default,
		}; //Enum

		enum BufferType
		{
			BUFFERTYPE_VertexBuffer = 0,
			BUFFERTYPE_IndexBuffer = 1,
		}; //Enum

		///GETUSAGETYPE(VOID)
		///
		///Get the usage type of this buffer
		///
		///
		///No Params:
		virtual Usage	GetUsageType()	= 0;

		///IS32BIT(VOID)
		///
		///Get if the Buffer is a 32bit buffer this is used when rendering the buffer
		///
		///No Params:
		virtual bool	Is32Bit()		= 0;

		///LOADDATA(VOID)
		///
		///Load the Data into a void* and return it
		///Once loaded it must be unloaded before the buffer can be loaded 
		///again else will throw a internal exception
		///
		///No Params:
		virtual void*	LoadData()		= 0;

		///UNLOADDATA(VOID)
		///
		///Unload the data from previous LoadData
		///If the Data is not loaded and Unload Data is Called a exception will be thrown
		///
		///No Params:
		virtual bool	UnloadData()	= 0;

	EndInterface(IBuffer) //Interface
} //Namespace

#endif //_IBUFFER_HEADER_