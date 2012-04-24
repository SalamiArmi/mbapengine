#include <Standard/ArgonStandard.h>
#include <Standard/ArgonVector.h>
#include <Standard/ArgonVector2.h>
#include <Standard/ArgonVector3.h>

template<typename IndexType> struct AttributeInfo
{
	ulong MinVertex;
	ulong MaxVertex;
	ulong MaterialID;
	Vector<IndexType> Faces;
};

template<typename IndexType> bool Mesh::OptimizeInplace()
{
	ulong* SystemAttribs = NULL;
	IndexType* IndexBuffer = NULL;

	m_AttributeBuffer->LoadPhysicalData( (void**)&SystemAttribs );
	m_IndexBuffer->LoadPhysicalData( (void**)&IndexBuffer );

	Vector<AttributeInfo<IndexType>> MaterialID;
	MaterialID.Resize((size_t)GetMaterialCount(SystemAttribs, m_FaceCount));

	//Create Empty Slots
	for(size_t Index = 0; Index < MaterialID.Size(); ++Index)
	{
		MaterialID[Index].MaterialID = Index;
		MaterialID[Index].MinVertex = ULONG_MAX;
		MaterialID[Index].MaxVertex = -ULONG_MAX;
	}

	//Optimize the mesh
	ulong FaceCount = m_FaceCount;

	for(ulong Face = 0; Face < FaceCount; ++Face)
	{
		Vector<AttributeInfo<IndexType>>::Iterator it = MaterialID.Begin();

		ulong AttributeIndex = SystemAttribs[Face];

		IndexType i1 = IndexBuffer[(Face * 3) + 0];
		IndexType i2 = IndexBuffer[(Face * 3) + 1];
		IndexType i3 = IndexBuffer[(Face * 3) + 2];

		for(; it != MaterialID.End(); ++it)
		{
			if((*it).MaterialID == AttributeIndex)
			{
				(*it).Faces.Push_Back( i1 );
				if( i1 < (*it).MinVertex ) (*it).MinVertex = i1;
				if( i1 > (*it).MaxVertex ) (*it).MaxVertex = i1;

				(*it).Faces.Push_Back( i2 );
				if( i2 < (*it).MinVertex ) (*it).MinVertex = i2;
				if( i2 > (*it).MaxVertex ) (*it).MaxVertex = i2;

				(*it).Faces.Push_Back( i3 );
				if( i3 < (*it).MinVertex ) (*it).MinVertex = i3;
				if( i3 > (*it).MaxVertex ) (*it).MaxVertex = i3;
			}
		}
	}

	m_IndexBuffer->UnloadPhysicalData();

	//Copy into the Mesh Index Buffer
	IndexBuffer = NULL;
	m_IndexBuffer->LoadPhysicalData((void**)&IndexBuffer);

	//Create the Attribute Count
	m_AttributeTable.Resize(MaterialID.Size());

	ulong FaceStart = 0;
	IndexType Offset = 0;

	for( Vector<AttributeInfo<IndexType>>::Iterator it = MaterialID.Begin(); it != MaterialID.End(); ++it )
	{
		m_AttributeTable[(*it).MaterialID].MaterialID = (*it).MaterialID;

		if(it != MaterialID.Begin())
		{
			Offset += (*(it - 1)).Faces.Size();
			FaceStart += (*(it - 1)).Faces.Size() / 3;
		}

		m_AttributeTable[(*it).MaterialID].FaceStart = FaceStart;

		if((*it).Faces.Size() > 0)
		{
			memcpy(IndexBuffer + Offset, &(*it).Faces[0], (*it).Faces.Size() * sizeof(IndexType));
		}

		for(ulong Index = 0; Index < ((*it).Faces.Size() / 3 ); ++Index)
		{
			SystemAttribs[Index + (Offset / 3)] = (*it).MaterialID;
		}

		m_AttributeTable[(*it).MaterialID ].IndexCount = (*it).Faces.Size();

		/*if((*it).MaxVertex == ULONG_MAX || (*it).MinVertex == -ULONG_MAX)
		{
			m_AttributeTable[(*it).MaterialID ].VertexCount = 0;
			m_AttributeTable[(*it).MaterialID ].nVertexStart = 0;
		}
		else
		{
			m_AttributeTable[(*it).MaterialID].VertexCount = ((*it).MaxVertex - (*it).MinVertex ) + 1;
			m_AttributeTable[(*it).MaterialID].nVertexStart = (*it).MinVertex;
		}*/
	}

	m_IndexBuffer->UnloadPhysicalData();
	m_AttributeBuffer->UnloadPhysicalData();

	return true;
}

template<typename IndexType> bool Mesh::GenerateTangents()
{
	if(m_VertexDeclaration & VERTEXDECL_Tangent)
	{
		ulong VertexCount = m_VertexCount;
		ulong FaceCount = m_FaceCount;

		void* VertexBuffer = NULL;
		m_VertexBuffer->LoadPhysicalData(&VertexBuffer);

		IndexType* IndexBuffer = NULL;
		m_IndexBuffer->LoadPhysicalData((void**)&IndexBuffer);

		ulong nStride = m_nSystemMemoryStride;

		Vector3* Tangents = new Vector3[VertexCount];
		memset( Tangents, 0, sizeof( float ) * 3 * VertexCount);

		Vector3* BiNormals = new Vector3[VertexCount];
		memset(BiNormals, 0, sizeof(float) * 3 * VertexCount);

		//Offsets
		ulong TexCoordElementOffset = 0;
		ulong NormalElementOffset = GetSystemVertexElementOffset(VERTEXELEMENT_Normal);

		Vector3* Tangent1 = new Vector3[VertexCount];

		for ( ulong nIndex = 0; nIndex < FaceCount; ++nIndex )
		{
			IndexType i1 = IndexBuffer[ 0 ];
			IndexType i2 = IndexBuffer[ 1 ];
			IndexType i3 = IndexBuffer[ 2 ];

			assert( i1 < VertexCount && "Index Count is out of the Vertex Count" );
			assert( i2 < VertexCount && "Index Count is out of the Vertex Count" );
			assert( i3 < VertexCount && "Index Count is out of the Vertex Count" );

			const Vector3 v1 = *reinterpret_cast<Vector3*>( reinterpret_cast<char*>( VertexBuffer ) + nStride * i1 );
			const Vector3 v2 = *reinterpret_cast<Vector3*>( reinterpret_cast<char*>( VertexBuffer ) + nStride * i2 );
			const Vector3 v3 = *reinterpret_cast<Vector3*>( reinterpret_cast<char*>( VertexBuffer ) + nStride * i3 );

			const Vector2 w1 = *reinterpret_cast<Vector2*>( reinterpret_cast<char*>( VertexBuffer ) + ( nStride * i1 + TexCoordElementOffset ) );
			const Vector2 w2 = *reinterpret_cast<Vector2*>( reinterpret_cast<char*>( VertexBuffer ) + ( nStride * i2 + TexCoordElementOffset ) );
			const Vector2 w3 = *reinterpret_cast<Vector2*>( reinterpret_cast<char*>( VertexBuffer ) + ( nStride * i3 + TexCoordElementOffset ) );

			float x1 = v2.x - v1.x;
			float x2 = v3.x - v1.x;
			float y1 = v2.y - v1.y;
			float y2 = v3.y - v1.y;
			float z1 = v2.z - v1.z;
			float z2 = v3.z - v1.z;

			float s1 = w2.x - w1.x;
			float s2 = w3.x - w1.x;
			float t1 = w2.y - w1.y;
			float t2 = w3.y - w1.y;


			float r = 0.0f;
			float r1 = (s1 * t2 - s2 * t1);
			if( r1 != 0.0f )
			{
				r = 1.0F / r1;
			}
			else
			{
				r = 0.0f;
			}

			Vector3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);

			Tangent1[i1] += sdir;
			Tangent1[i2] += sdir;
			Tangent1[i3] += sdir;

			IndexBuffer += 3;
		}

		for ( ulong nVertexIndex = 0; nVertexIndex < VertexCount; ++nVertexIndex )
		{
			const Vector3 n = *reinterpret_cast<Vector3*>( reinterpret_cast<char*>( VertexBuffer ) + ( m_nSystemMemoryStride * nVertexIndex + NormalElementOffset ) );
			const Vector3 t = Tangent1[nVertexIndex];

			// Gram-Schmidt orthogonalize
			Vector3 vTangent = (n * n.Dot(t)-t).Normalize();

			Tangents[nVertexIndex ] = vTangent;
			Vector3 vBiNormal = (t.Cross( n )).Normalize();
			BiNormals[ nVertexIndex ] = vBiNormal;
		}

		delete[] Tangent1;

		/*
		Copy the Tangent and Binormal Data into the Mesh
		*/
		float* pDeviceBuffer = NULL;
		m_VideoVertexBuffer->LoadPhysicalData( (void**)&pDeviceBuffer );

		//Get the Complete Mesh Data
		ulong nCompleteStride = m_nDeviceStride;

		for( ulong nIndex = 0; nIndex < VertexCount; ++nIndex )
		{
			Vector3* pTangent =  reinterpret_cast<Vector3*>( reinterpret_cast<char*>( pDeviceBuffer ) + nCompleteStride * nIndex + GetElementOffset( s_VertexDeclaration, D3DDECLUSAGE_TANGENT ) );

			if( pTangent )
			{
				memcpy( pTangent, Tangents[ nIndex ], sizeof( Vector3 ) );
			}

			Vector3* pBiNormal =  reinterpret_cast<Vector3*>( reinterpret_cast<char*>( pDeviceBuffer ) + nCompleteStride * nIndex + GetElementOffset( s_VertexDeclaration, D3DDECLUSAGE_BINORMAL ) );

			if( pBiNormal )
			{
				memcpy( pBiNormal, BiNormals[ nIndex ], sizeof( Vector3 ) );
			}
		}

		m_VideoVertexBuffer->UnloadPhysicalData();

		m_VertexBuffer->UnloadPhysicalData();
		m_IndexBuffer->UnloadPhysicalData();

		delete[] Tangents;
		delete[] BiNormals;

		return true;
	}
	return false;
}

ulong Mesh::GetMaterialCount(ulong* AttributeBuffer, ulong FaceCount)
{
	ulong HeighestMaterialID = 0;
	for(ulong Index = 0; Index < m_FaceCount; ++Index)
	{
		if(AttributeBuffer[Index] > HeighestMaterialID)
		{
			HeighestMaterialID = AttributeBuffer[Index];
		}
	}
	return HeighestMaterialID + 1; //Add one due to the Starting from 0 Eg. if found 12, 0 - 12 = 13;
}