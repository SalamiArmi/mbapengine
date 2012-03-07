#ifndef _IBUFFER_HEADER_
#define _IBUFFER_HEADER_

#include "IArgonUnknown.h"

namespace Argon
{
	DeclareBasedInterface(IBuffer, IArgonUnknown) 
		
		enum Usage
		{
			USAGE_Dynamic = 0,	//Create a Buffer that can have memory Allocated to it
			USAGE_Default,		//Create a Buffer that will have a set size and will upload to video memory
		}; //Enum

		enum BufferType
		{
			BUFFERTYPE_VertexBuffer = 0,	//Video Memory Support
			BUFFERTYPE_IndexBuffer = 1,		//Video Memory Support
			BUFFERTYPE_PhysicalMemory = 2,	//Physical Memory, only RAM (Random Access Memory)
			BUFFERTYPE_Attributes = 3,		
		}; //Enum

		///GETBUFFERTYPE(VOID)
		///
		///Get the usage type of this buffer
		///
		///
		///No Params:
		virtual BufferType GetBufferType() = 0;

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

		///LoadPhysicalData(VOID)
		///
		///Load the Data into a void* and return it
		///Once loaded it must be unloaded before the buffer can be loaded 
		///again else will throw a internal exception
		///
		///No Params:
		virtual bool	LoadPhysicalData(void** Data)	= 0;

		///UnloadPhysicalData(VOID)
		///
		///Unload the data from previous LoadData
		///If the Data is not loaded and Unload Data is Called a exception will be thrown
		///
		///No Params:
		virtual bool	UnloadPhysicalData()	= 0;

		//
		//UploadToVideoMemory(BOOL)
		//
		//Upload the Physical memory to video memory
		//
		virtual bool	UploadToVideoMemory()	= 0;

	EndInterface(IBuffer) //Interface
} //Namespace

#endif //_IBUFFER_HEADER_