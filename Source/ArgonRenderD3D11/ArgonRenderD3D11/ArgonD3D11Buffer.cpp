#include "ArgonD3D11Buffer.h"
#include "ArgonD3D11RenderSystem.h"

namespace Argon
{

	//To create a buffer using filled out memory simply fill out 
	//the sub resource data instead of using NULL 	
	D3D11Buffer::D3D11Buffer(uint BufferSize, IBuffer::Usage Usage, IBuffer::BufferType BufferType, uint Stride) 
		: m_Usage(Usage)
	{
		D3D11_BUFFER_DESC BufferDesc;
		BufferDesc.ByteWidth = BufferSize;

		//Set the Buffer usage Flags
		if(Usage == IBuffer::USAGE_Default)
			BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		else if(Usage == IBuffer::USAGE_Dynamic)
			BufferDesc.Usage = D3D11_USAGE_DYNAMIC;

		//Set the type of buffer eg Vertex or Index Buffers
		if(BufferType == BUFFERTYPE_IndexBuffer)
			BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		else if(BufferType == BUFFERTYPE_VertexBuffer)
			BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//Always have Write as the CPU Flag
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		//Set the Stride of the Buffer
		BufferDesc.StructureByteStride = Stride;
		
		D3D11RenderSystem::instance()->GetDevice()->GetDevice()->CreateBuffer(&BufferDesc, NULL, &m_Buffer);
	}

	D3D11Buffer::~D3D11Buffer()
	{
	}

	IBuffer::Usage D3D11Buffer::GetUsageType()
	{
		return m_Usage;
	}

	bool D3D11Buffer::Is32Bit()
	{
		return true; //TODO
	}

	void* D3D11Buffer::LoadData()
	{
		return NULL;
	}

	bool D3D11Buffer::UnloadData()
	{
		return false;
	}

	ID3D11Buffer* D3D11Buffer::GetD3D11Buffer()
	{
		return m_Buffer;
	}

} //Namespace