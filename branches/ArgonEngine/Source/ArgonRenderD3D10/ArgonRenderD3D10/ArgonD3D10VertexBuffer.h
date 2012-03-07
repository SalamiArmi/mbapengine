#ifndef _ARGOND3D10VERTEXBUFFER_HEADER_
#define _ARGOND3D10VERTEXBUFFER_HEADER_

#include "ArgonD3D10RenderSystem.h"
#include <Standard/ArgonStandard.h>

namespace Argon
{
	class D3D10VertexBuffer : public IArgonUnknownImp<IBuffer, GUID_IBuffer>
	{
	public:
		D3D10VertexBuffer(Usage UsageType);
		D3D10VertexBuffer(Usage UsageType, float* Data, ulong Size);
		~D3D10VertexBuffer();

		///LOAD(BOOL)
		///
		///Load the Interface All interfaces must use this
		///
		///No Params:
		bool	Load();

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

		///UploadToVideoMemory(BOOL)
		///
		///Upload the Physical memory to video memory
		///
		///No Params:
		bool UploadToVideoMemory();
		
		///UploadToVideoMemory(BOOL)
		///
		///Upload the Physical memory to video memory
		///
		///No Params:
		ID3D10Buffer* GetVideoBuffer();

		ID3D10Buffer* const * GetVideoBufferPtr();

	private:
		bool			m_Dirty;
		ushort			m_LoadPhysicalCount;

		float*			m_VertexData;
		ulong			m_VertexCount;
		Usage			m_Usage;

		ID3D10Buffer*	m_VideoMemoryBuffer;
	};//Class
} //Namespace

#endif //_ARGOND3D10VERTEXBUFFER_HEADER_