#include "ArgonD3D10VertexBuffer.h"
#include "ArgonD3D10RenderSystem.h"

namespace Argon
{
	D3D10VertexBuffer::D3D10VertexBuffer(Usage UsageType)
		: m_VertexData(NULL),
		m_VertexCount(0),
		m_Usage(UsageType),
		m_VideoMemoryBuffer(NULL),
		m_Dirty(true),
		m_LoadPhysicalCount(0)
	{
	}

	
	D3D10VertexBuffer::D3D10VertexBuffer(Usage UsageType, float* Data, ulong Size)
		: m_VertexData(Data),
		m_VertexCount(Size),
		m_Usage(UsageType),
		m_Dirty(true)
	{
		
	}

	D3D10VertexBuffer::~D3D10VertexBuffer()
	{
		if(m_VertexData)
		{
			delete[] m_VertexData;
			m_VertexCount = 0;
		}
	}

	bool D3D10VertexBuffer::Load()
	{	
		++m_RefCount;
		if(m_VertexData)
		{
			return UploadToVideoMemory();
		}

		return false;
	}

	IBuffer::Usage D3D10VertexBuffer::GetUsageType()
	{
		return m_Usage;
	}

	IBuffer::BufferType D3D10VertexBuffer::GetBufferType()
	{
		return IBuffer::BUFFERTYPE_VertexBuffer;
	}

	bool D3D10VertexBuffer::Is32Bit()
	{
		return false;
	}

	bool D3D10VertexBuffer::LoadPhysicalData(void** Data)
	{
		if(m_VertexData && m_LoadPhysicalCount == 0)
		{
			(*Data) = (void*)m_VertexData;
			m_Dirty = true;
			return true;
		}

		return false;
	}

	bool D3D10VertexBuffer::UnloadPhysicalData()
	{
		if(m_VertexData && !m_Dirty && m_LoadPhysicalCount == 1)
		{
			m_Dirty = true;
			return true;
		}

		return false;
	}

	bool D3D10VertexBuffer::UploadToVideoMemory()
	{
		if(m_Dirty)
		{
			if(m_VideoMemoryBuffer)
			{
				m_VideoMemoryBuffer->Release();
			}

			D3D10_BUFFER_DESC Desc;
			Desc.ByteWidth = m_VertexCount * sizeof(float);

			if(m_Usage == IBuffer::USAGE_Default)
			{
				Desc.Usage = D3D10_USAGE_DEFAULT;
			}
			else if(m_Usage == IBuffer::USAGE_Dynamic)
			{
				Desc.Usage = D3D10_USAGE_DYNAMIC;
			}

			Desc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
			Desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
			Desc.MiscFlags = 0;

			D3D10_SUBRESOURCE_DATA Data;
			Data.pSysMem = m_VertexData;
			Data.SysMemPitch = 0;
			Data.SysMemSlicePitch = 0;

			HRESULT hr = D3D10RenderSystem::instance()->GetDevice()->GetDevice()->CreateBuffer(&Desc, &Data, &m_VideoMemoryBuffer);

			if(hr == S_OK)
				return true;
		}
		return false;
	}

	ID3D10Buffer* D3D10VertexBuffer::GetVideoBuffer()
	{
		return m_VideoMemoryBuffer;
	}

	ID3D10Buffer* const * D3D10VertexBuffer::GetVideoBufferPtr()
	{
		return &m_VideoMemoryBuffer;
	}

} //Namespace
