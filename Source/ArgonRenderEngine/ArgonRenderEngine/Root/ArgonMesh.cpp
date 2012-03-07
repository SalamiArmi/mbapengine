#include <Interface/IBuffer.h>
#include "ArgonRoot.h"
#include "ArgonMesh.h"

namespace Argon
{
	Mesh::Mesh(ulong VertexCount, ulong FaceCount, IRenderSystem::VertexDeclaration Declaration)
		: m_VertexDeclaration(Declaration),
		m_VideoVertexDeclaration(IRenderSystem::VERTEXDECL_Unknown),
		m_VideoVertexBuffer(NULL),
		m_VideoIndexBuffer(NULL),
		m_VertexCount(VertexCount),
		m_FaceCount(FaceCount),
		m_Dirty(true),
		m_IndicesAre32bit((FaceCount * 3) > ArgonMaxUShort)
		m_VertexBuffer(new PhysicalMemory<char>(VertexCount * sizeof(float))),
		m_IndexBuffer(new PhysicalMemory<char>((m_FaceCount * 3) * m_IndicesAre32bit ? sizeof(ushort) : sizeof(ulong))),
		m_AttributeBuffer(new PhysicalMemory<ulong>(m_FaceCount))
	{
	}

	Mesh::~Mesh()
	{

	}

	bool Mesh::Load()
	{
		return false;
	}

	bool Mesh::Bind()
	{
		if( m_Invalid || m_VertexDeclaration != m_VideoVertexDeclaration )
		{
			UploadToVideoMemory(); //Upload new Data to the Video Buffers
			m_Invalid = false;
		}

		bool Success = false;

		if(

		Root::instance()->GetActiveRenderSystem()->SetVertexDecleration(
		Success &= Root::instance()->GetActiveRenderSystem()->SetBuffer(IBuffer::BUFFERTYPE_IndexBuffer, m_VideoIndexBuffer);
		Success &= Root::instance()->GetActiveRenderSystem()->SetBuffer(IBuffer::BUFFERTYPE_VertexBuffer, m_VideoVertexBuffer);

		return Success;
	}

	bool Mesh::Draw(ulong MeshID)
	{	
		Root::instance()->GetActiveRenderSystem()->DrawPrimitive(m_AttributeTable[MeshID]);
		return true;
	}

	bool Mesh::UnBind()
	{
		return false;
	}

	void Mesh::LockBuffer(IBuffer::BufferType BufferType, Mesh::LockType Type, void** Data)
	{
		bool Success = false;
		if(BufferType == IBuffer::BUFFERTYPE_IndexBuffer)
		{
			Success = m_IndexBuffer->LoadPhysicalData(Data); //Lock the Index Buffer
		}
		else if(BufferType == IBuffer::BUFFERTYPE_VertexBuffer)
		{
			Success = m_VertexBuffer->LoadPhysicalData(Data);//Lock the Vertex Buffer
		}
		else if(BufferType == BUFFERTYPE_Attributes)
		{
			Success = m_AttributeBuffer->LoadPhysicalData(Data);
			m_DirtyAttributes = (Type == Mesh::LOCKTYPE_WriteOnly);
		}

		if(Type == Mesh::LOCKTYPE_WriteOnly && Success)
		{
			m_Invalid = true; //Mesh should now be invalid
		}
	}

	void Mesh::UnlockBuffer(IBuffer::BufferType BufferType)
	{
		if(BufferType == IBuffer::BUFFERTYPE_IndexBuffer)
		{
			m_IndexBuffer->UnloadPhysicalData();
		}
		else if(BufferType == IBuffer::BUFFERTYPE_VertexBuffer)
		{
			m_VertexBuffer->UnloadPhysicalData();
		}
		else if(BufferType == BUFFERTYPE_Attributes)
		{
			m_AttributeBuffer->UnloadPhysicalData();
			if(m_DirtyAttributes)
			{
				m_IndicesAre32bit ? OptimizeInplace<ushort> : OptimizeInplace<ulong>();
				m_DirtyAttributes = false;
			}
		}
	}

	ulong Mesh::GetVertexCount()
	{
		return m_VertexCount;
	}

	ulong Mesh::GetFaceCount()
	{
		return m_FaceCount;
	}

	void Mesh::SetStartVertex(ulong Vertex)
	{
	}

	void Mesh::SetStartIndex(ulong Index)
	{
	}

	ulong Mesh::GetStartVertex()
	{
		return 0;
	}

	ulong Mesh::GetStartIndex()
	{
		return 0;
	}

	ulong Mesh::GetStride()
	{
		return 0;
	}

	void Mesh::UploadToVideoMemory()
	{
		if(m_VertexCount == 0 || m_FaceCount == 0)
		{
			return;
		}

		if(m_VertexDeclaration != m_VideoVertexDeclaration)
		{
			//Destroy old Video Buffers
			if(m_VideoVertexBuffer)
				m_VideoVertexBuffer->UnLoad();
			if(m_VideoIndexBuffer)
				m_VideoIndexBuffer->UnLoad();
			
			Root::instance()->GetActiveRenderSystem()->CreateBuffer(IBuffer::BUFFERTYPE_PhysicalMemory, IBuffer::USAGE_Default, (m_FaceCount * 3) * m_IndicesAre32bit ? sizeof(ushort) : sizeof(ulong));
			Root::instance()->GetActiveRenderSystem()->CreateBuffer(IBuffer::BUFFERTYPE_PhysicalMemory, IBuffer::USAGE_Default, m_VertexCount * sizeof(float));
		}
	}

} //namespace