#include "ArgonD3D10IndexBuffer.h"

namespace Argon
{
	D3D10IndexBuffer::D3D10IndexBuffer(Usage UsageType)
		: m_IndexData(NULL),
		m_IndexCount(0),
		m_Usage(UsageType),
		m_VideoMemoryBuffer(NULL)
	{
	}

	D3D10IndexBuffer::D3D10IndexBuffer(Usage UsageType, ulong* Data, ulong Size)
		: m_IndexData(Data),
		m_IndexCount(Size),
		m_Usage(UsageType),
		m_VideoMemoryBuffer(NULL)
	{
	}

	D3D10IndexBuffer::~D3D10IndexBuffer()
	{
		if(m_IndexData)
		{
			delete[] m_IndexData;
			m_IndexCount = 0;
		}
	}

	bool D3D10IndexBuffer::Load()
	{
		++m_RefCount;
		if(m_IndexData)
		{
			return UploadToVideoMemory();
		}

		return false;
	}

	IBuffer::Usage D3D10IndexBuffer::GetUsageType()
	{
		return m_Usage;
	}

	IBuffer::BufferType D3D10IndexBuffer::GetBufferType()
	{
		return IBuffer::BUFFERTYPE_IndexBuffer;
	}

	bool D3D10IndexBuffer::Is32Bit()
	{
		return true;
	}

	bool D3D10IndexBuffer::LoadPhysicalData(void** Data)
	{
		if(m_IndexData && m_LoadPhysicalCount == 0)
		{
			(*Data) = (void*)m_IndexData;
			m_Dirty = true;
			return true;
		}

		return false;
	}

	bool D3D10IndexBuffer::UnloadPhysicalData()
	{
		if(m_IndexData && !m_Dirty && m_LoadPhysicalCount == 1)
		{
			m_Dirty = true;
			return true;
		}

		return false;
	}

	bool D3D10IndexBuffer::UploadToVideoMemory()
	{
		if(m_Dirty)
		{
			if(m_VideoMemoryBuffer)
			{
				m_VideoMemoryBuffer->Release();
			}

			D3D10_BUFFER_DESC Desc;
			Desc.ByteWidth = m_IndexCount * sizeof(float);

			if(m_Usage == IBuffer::USAGE_Default)
			{
				Desc.Usage = D3D10_USAGE_DEFAULT;
			}
			else if(m_Usage == IBuffer::USAGE_Dynamic)
			{
				Desc.Usage = D3D10_USAGE_DYNAMIC;
			}

			Desc.BindFlags = D3D10_BIND_INDEX_BUFFER;
			Desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
			Desc.MiscFlags = 0;

			D3D10_SUBRESOURCE_DATA Data;
			Data.pSysMem = m_IndexData;
			Data.SysMemPitch = 0;
			Data.SysMemSlicePitch = 0;

			HRESULT hr = D3D10RenderSystem::instance()->GetDevice()->GetDevice()->CreateBuffer(&Desc, &Data, &m_VideoMemoryBuffer);

			if(hr == S_OK)
				return true;
		}
		return false;
	}

	ID3D10Buffer* D3D10IndexBuffer::GetVideoBufferPtr() const
	{
		return m_VideoMemoryBuffer;
	}
}