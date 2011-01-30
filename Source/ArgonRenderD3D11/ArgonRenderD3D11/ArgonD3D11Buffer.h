#ifndef _ARGOND3D11BUFFER_HEADER_
#define _ARGOND3D11BUFFER_HEADER_

#include <Interface/IBuffer.h>
#include <Interface/IArgonUnknownImp.h>

#include "ArgonD3D11Device.h"

namespace Argon
{

	class D3D11Buffer : public IArgonUnknownImp<IBuffer, GUID_IBuffer>
	{
	public:
		D3D11Buffer(uint BufferSize, IBuffer::Usage Usage, IBuffer::BufferType BufferType, uint Stride);

		///GETUSAGETYPE(USAGE)
		///
		///Get the usage type of this buffer
		///
		///
		///No Params:
		Usage	GetUsageType();

		///IS32BIT(BOOL)
		///
		///Get if the Buffer is a 32bit buffer this is used when rendering the buffer
		///
		///No Params:
		bool	Is32Bit();

		///LOADDATA(VOID*)
		///
		///Load the Data into a void* and return it
		///Once loaded it must be unloaded before the buffer can be loaded 
		///again else will throw a internal exception
		///
		///No Params:
		void*	LoadData();

		///UNLOADDATA(BOOL)
		///
		///Unload the data from previous LoadData
		///If the Data is not loaded and Unload Data is Called a exception will be thrown
		///
		///No Params:
		bool	UnloadData();

		///GETD3D11BUFFER(ID3D11BUFFER)
		///
		///Get the Internal Buffer this is only used in the Renderers project
		///Internal use only
		///
		///No Params:
		ID3D11Buffer* GetD3D11Buffer();

	protected:
		~D3D11Buffer();

		ID3D11Buffer* m_Buffer;		//The DirectX11 Buffer

		//Stored Flags for Accessing the Buffer Correctly
		Usage m_Usage;

		uint m_LoadDataCount;		//The load and unload Data count
	}; //Class

} //Namespace

#endif //_ARGOND3D11BUFFER_HEADER_