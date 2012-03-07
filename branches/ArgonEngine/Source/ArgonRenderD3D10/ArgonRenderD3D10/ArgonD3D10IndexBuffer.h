#ifndef _ARGOND3D10INDEXBUFFER_HEADER_
#define _ARGOND3D10INDEXBUFFER_HEADER_

#include "ArgonD3D10RenderSystem.h"
#include <Standard/ArgonStandard.h>

namespace Argon
{
	class D3D10IndexBuffer : public IArgonUnknownImp<IBuffer, GUID_IBuffer>
	{
	public:
		D3D10IndexBuffer(Usage UsageType);
		D3D10IndexBuffer(Usage UsageType, ulong* Data, ulong Size);
		~D3D10IndexBuffer();

		///LOAD(BOOL)
		///
		///Load the Interface All interfaces must use this
		///
		///No Params:
		bool Load();

		///GETUSAGETYPE(USAGE)
		///
		///Get the usage type of this buffer
		///
		///No Params:
		IBuffer::Usage GetUsageType();

		///GETBUFFERTYPE(BUFFERTYPE)
		///
		///Get the usage type of this buffer
		///
		///No Params:
		IBuffer::BufferType GetBufferType();

		///IS32BIT(BOOL)
		///
		///Get if the Buffer is a 32bit buffer this is used when rendering the buffer
		///
		///No Params:
		bool Is32Bit();

		///LoadPhysicalData(VOID)
		///
		///Load the Data into a void* and return it
		///Once loaded it must be unloaded before the buffer can be loaded 
		///again else will throw a internal exception
		///
		///No Params:
		bool LoadPhysicalData(void** Data);

		///UnloadPhysicalData(VOID)
		///
		///Unload the data from previous LoadData
		///If the Data is not loaded and Unload Data is Called a exception will be thrown
		///
		///No Params:
		bool UnloadPhysicalData();

		//
		//UploadToVideoMemory(BOOL)
		//
		//Upload the Physical memory to video memory
		//
		bool UploadToVideoMemory();

	private:
		bool			m_Dirty;
		ushort			m_LoadPhysicalCount;

		ulong*			m_IndexData;
		ulong			m_IndexCount;
		Usage			m_Usage;

		ID3D10Buffer*	m_VideoMemoryBuffer;
	};//Class
} //Namespace

#endif //_ARGOND3D10VERTEXBUFFER_HEADER_