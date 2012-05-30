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
		m_IndicesAre32bit((FaceCount * 3) > ArgonMaxUShort),
		m_VertexBuffer(new PhysicalMemory<char>(VertexCount * sizeof(float))),
		m_IndexBuffer(new PhysicalMemory<char>((m_FaceCount * 3) * m_IndicesAre32bit ? sizeof(ushort) : sizeof(ulong))),
		m_AttributeBuffer(new PhysicalMemory<ulong>(m_FaceCount))
	{
	}

	Mesh::Mesh()
		: m_VertexDeclaration(IRenderSystem::VERTEXDECL_Unknown),
		m_VideoVertexDeclaration(IRenderSystem::VERTEXDECL_Unknown),
		m_VideoVertexBuffer(NULL),
		m_VideoIndexBuffer(NULL),
		m_VertexCount(0),
		m_FaceCount(0),
		m_Dirty(false),
		m_IndicesAre32bit(true),
		m_VertexBuffer(NULL),
		m_IndexBuffer(NULL),
		m_AttributeBuffer(NULL)
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
		if(m_Dirty || m_VertexDeclaration != m_VideoVertexDeclaration)
		{
			UploadToVideoMemory(); //Upload new Data to the Video Buffers
			m_Dirty = false;
		}

		bool Success = false;

		//Root::instance()->GetActiveRenderSystem()->SetVertexDecleration(
		Success &= Root::instance()->GetActiveRenderSystem()->SetBuffer(IBuffer::BUFFERTYPE_IndexBuffer, m_VideoIndexBuffer);
		Success &= Root::instance()->GetActiveRenderSystem()->SetBuffer(IBuffer::BUFFERTYPE_VertexBuffer, m_VideoVertexBuffer);

		return Success;
	}

	bool Mesh::Draw(IShader* Shader, ulong MeshID)
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
		else if(BufferType == IBuffer::BUFFERTYPE_Attributes)
		{
			Success = m_AttributeBuffer->LoadPhysicalData(Data);
			m_DirtyAttributes = (Type == Mesh::LOCKTYPE_WriteOnly);
		}

		if(Type == Mesh::LOCKTYPE_WriteOnly && Success)
		{
			m_Dirty = true; //Mesh should now be invalid
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
		else if(BufferType == IBuffer::BUFFERTYPE_Attributes)
		{
			m_AttributeBuffer->UnloadPhysicalData();
			if(m_DirtyAttributes)
			{
				m_IndicesAre32bit ? OptimizeInplace<ushort>() : OptimizeInplace<ulong>();
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

	bool Mesh::Intersect(const Vector3& CollisionOrigin, const Vector3& CollisionDirection, Vector3& Intersection, int& MaterialID)
	{
		//Vector3 MeshOrg(m_BoundingSphereCentre.x,m_BoundingSphereCentre.y,m_BoundingSphereCentre.z);
		//Vector3 RayOrg(rCollisionOrigin.x,rCollisionOrigin.y,rCollisionOrigin.z);
		//Vector3 RayDir(rCollisionDirection.x,rCollisionDirection.y,rCollisionDirection.z);
		//RayDir.Normalize();
		//Vector3 PointOnRay( RayOrg + RayDir * ((MeshOrg-RayOrg).Dot(RayDir)) );
		//float RayToCenterDistSquared = (PointOnRay-MeshOrg).MagnitudeSquared();
		//if( RayToCenterDistSquared > m_BoundingSphereRadius*m_BoundingSphereRadius ) {
		//	// ray and sphere do not intersect
		//	return false;
		//} else {
		//	bool bIntersect = false;

		//	unsigned char* pIndices = NULL;
		//	m_pIndexBuffer->Lock( (void**)&pIndices, IBuffer::LOCKTYPE_ReadOnly );
		//	unsigned char* pVertices = NULL;
		//	m_pVertexBuffer->Lock( (void**)&pVertices, IBuffer::LOCKTYPE_ReadOnly );
		//	for(ulong i=0; i<m_nFaceCount; ++i) {
		//		ulong iV0 = (m_bIndicesAre32bit) ?  *((ulong*)pIndices + i*3 + 0) : *((ushort*)pIndices + i*3 + 0);
		//		assert(iV0<m_nVertexCount);
		//		ulong iV1 = (m_bIndicesAre32bit) ?  *((ulong*)pIndices + i*3 + 1) : *((ushort*)pIndices + i*3 + 1);
		//		assert(iV1<m_nVertexCount);
		//		ulong iV2 = (m_bIndicesAre32bit) ?  *((ulong*)pIndices + i*3 + 2) : *((ushort*)pIndices + i*3 + 2);
		//		assert(iV2<m_nVertexCount);
		//		const Vector3& rV0 = *((const Vector3*)( pVertices + m_nSystemMemoryStride*iV0 ));
		//		const Vector3& rV1 = *((const Vector3*)( pVertices + m_nSystemMemoryStride*iV1 ));
		//		const Vector3& rV2 = *((const Vector3*)( pVertices + m_nSystemMemoryStride*iV2 ));

		//		Vector3 TriNorm( (rV1-rV0).Cross( rV2-rV0 ) );
		//		float Denominator = RayDir.Dot(TriNorm);
		//		if( !bIgnoreTriangleNormals && Denominator>=0.0f ) {
		//			continue;
		//		}
		//		Vector3 W( RayOrg - rV0 );
		//		float Numerator = -TriNorm.Dot( W );
		//		if( !bIgnoreTriangleNormals && Numerator>=0.0 ) {
		//			// Denominator is always negative, thus S will be negative. We dont want that.
		//			continue;
		//		}
		//		float S = Numerator / Denominator;
		//		if( S >= 0.0f ) { // avoid NaN
		//			Vector3 IntersectionPoint = RayOrg + RayDir*S;
		//			Vector3 Test0( (rV1-rV0).Cross(IntersectionPoint-rV0) );
		//			if( Test0.Dot(TriNorm)<0.0f ) {
		//				continue;
		//			}
		//			Vector3 Test1( (rV2-rV1).Cross(IntersectionPoint-rV1) );
		//			if( Test1.Dot(TriNorm)<0.0f ) {
		//				continue;
		//			}
		//			Vector3 Test2( (rV0-rV2).Cross(IntersectionPoint-rV2) );
		//			if( Test2.Dot(TriNorm)<0.0f ) {
		//				continue;
		//			}

		//			// Ok, this triangle does intersect with our ray.
		//			bool bUpdate = false;
		//			if(!bIntersect) {
		//				// first intersecting triangle found
		//				bUpdate = true;
		//			} else {
		//				// is the new point closer to the camera ?
		//				bUpdate = ((rCollisionOrigin-IntersectionPoint).MagnitudeSquared()) < ((rCollisionOrigin-rIntersection).MagnitudeSquared());
		//			}
		//			if(bUpdate) {
		//				rIntersection = IntersectionPoint;
		//				if(m_pAttributeBuffer) {
		//					int* pMaterialIDs = NULL;
		//					m_pAttributeBuffer->Lock( (void**)&pMaterialIDs, IBuffer::LOCKTYPE_ReadOnly );
		//					rMaterialID = pMaterialIDs[i];
		//					m_pAttributeBuffer->UnLock();
		//				} else {
		//					rMaterialID = 0;
		//				}
		//			}
		//			bIntersect = true;
		//		}
		//	}
		//	m_pVertexBuffer->UnLock();
		//	m_pIndexBuffer->UnLock();

		//	return bIntersect;
		//}

		return false;
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

	unsigned Mesh::GetDeclarationSize(IRenderSystem::VertexDeclaration& Decl)
	{
		unsigned Size = 0;

		if(Decl & IRenderSystem::VERTEXDECL_Position)
		{
			Size += 3;
		}

		if(Decl & IRenderSystem::VERTEXDECL_Normal)
		{
			Size += 3;
		}

		if(Decl & IRenderSystem::VERTEXDECL_TexCoord)
		{
			Size += 2;
		}

		if(Decl & IRenderSystem::VERTEXDECL_TexCoord1)
		{
			Size += 2;
		}

		if(Decl & IRenderSystem::VERTEXDECL_Binormal)
		{
			Size += 3;
		}

		if(Decl & IRenderSystem::VERTEXDECL_Tangent)
		{
			Size += 3;
		}

		if(Decl & IRenderSystem::VERTEXDECL_TesselationFactor)
		{
			Size += 1;
		}
		if(Decl & IRenderSystem::VERTEXDECL_Color)
		{
			Size += 4;
		}

		return Size * sizeof(float);
	}

	void Mesh::PreDrawCallback(IShader* BoundShader)
	{
	}

	bool Mesh::PostDrawCallback(IShader* BoundShader)
	{
		return false;
	}

} //namespace