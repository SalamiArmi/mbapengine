#include "ArgonGeometryResource.h"

namespace Argon
{
	GeometryResource::GeometryResource(String Name)
		: Mesh(),
		Entity(Name, Entity::TYPE_Geometry),
		m_Name(Name)
	{	
		//TODO Threading
		//For now  find a Parser and se it for processing the mesh no threading atm
	}

	GeometryResource::~GeometryResource()
	{

	}

	void GeometryResource::SetMaterial(size_t MaterialID, Material* Mat)
	{
		ArgonAssert(MaterialID < m_Materials.Size());
		
		//Remove the old material
		m_Materials[MaterialID]->RemoveMesh(this, MaterialID);
		m_Materials[MaterialID] = NULL;

		//Set new Material
		m_Materials[MaterialID] = Mat;
		m_Materials[MaterialID]->AddMesh(this, MaterialID);
	}

	Material* GeometryResource::GetMaterial(size_t MaterialID)
	{
		return NULL;
	}

	bool GeometryResource::RemoveMaterial(String Name)
	{
		for(size_t Index = 0; Index < m_Materials.Size(); ++Index)
		{
			if(m_Materials[Index]->GetName() == Name)
			{
				m_Materials[Index]->RemoveMesh(this, Index);
				m_Materials[Index] = NULL;
				return true;
			}
		}

		return false;
	}

	bool GeometryResource::RemoveMaterial(Material* Mat)
	{
		for(size_t Index = 0; Index < m_Materials.Size(); ++Index)
		{
			if(m_Materials[Index] == Mat)
			{
				m_Materials[Index]->RemoveMesh(this, Index);
				m_Materials[Index] = NULL;
				return true;
			}
		}

		return false;
	}

	bool GeometryResource::Construct(GeometryParser* Parser)
	{
		if(Parser)
		{
			if(m_VertexBuffer)
			{
				delete m_VertexBuffer;
				m_VertexBuffer = NULL;
			}

			if(m_IndexBuffer)
			{
				delete m_IndexBuffer;
				m_IndexBuffer = NULL;
			}

			if(m_AttributeBuffer)
			{
				delete m_AttributeBuffer;
				m_AttributeBuffer = NULL;
			}

			if(m_VideoVertexBuffer)
			{
				ArgonAssert(m_VideoVertexBuffer->UnLoad());
				m_VideoVertexBuffer = NULL;
			}

			if(m_VideoIndexBuffer)
			{
				ArgonAssert(m_VideoIndexBuffer->UnLoad());
				m_VideoIndexBuffer = NULL;
			}
	
			m_Dirty = true;
			m_VertexCount = Parser->GetVextexCount();
			m_FaceCount = Parser->GetFaceCount();
			m_IndicesAre32bit = ((m_FaceCount * 3) > ArgonMaxUShort);
			m_VertexDeclaration = (IRenderSystem::VertexDeclaration)(IRenderSystem::VERTEXDECL_Position | IRenderSystem::VERTEXDECL_Normal | IRenderSystem::VERTEXDECL_TexCoord);
			m_VideoVertexDeclaration = IRenderSystem::VERTEXDECL_Unknown;
			m_Stride = GetDeclarationSize(m_VertexDeclaration);

			m_VertexBuffer = new PhysicalMemory<char>(m_VertexCount * m_Stride);
			m_IndexBuffer = new PhysicalMemory<char>((m_FaceCount * 3) * m_IndicesAre32bit ? sizeof(ushort) : sizeof(ulong));
			m_AttributeBuffer = new PhysicalMemory<ulong>(m_FaceCount);

			//Fill Vertex Buffer
			float* VertexData = NULL;
			m_VertexBuffer->LoadPhysicalData((void**)&VertexData);

			for(ulong Index = 0; Index < m_VertexCount; ++Index)
			{
				Vector3 Position = Parser->GetVextexPosition(Index);
				Vector3 Normal = Parser->GetVextexNormal(Index);
				Vector3 TextureCoord = Parser->GetVextexTexCoord(Index);

				//Position	
				VertexData[0] = Position.x;
				VertexData[1] = Position.y;
				VertexData[2] = Position.z;

				//Normal	
				VertexData[3] = Normal.x;
				VertexData[4] = Normal.y;
				VertexData[5] = Normal.z;

				//TexCoord	
				VertexData[6] = TextureCoord.x;
				VertexData[7] = TextureCoord.y;
				VertexData[8] = TextureCoord.z;

				*((char**)&VertexData) += m_Stride; //Increase by stride size
			}

			m_VertexBuffer->UnloadPhysicalData();

			//Fill Index Buffer
			char* IndexData = NULL;
			m_IndexBuffer->LoadPhysicalData((void**)IndexData);

			if(m_IndicesAre32bit)
				ParseIndexData<ulong>(Parser, IndexData);
			else
				ParseIndexData<ushort>(Parser, IndexData);

			m_IndexBuffer->UnloadPhysicalData();

			//Fill Attribute Buffer
			ulong* AttributeData = NULL;
			m_AttributeBuffer->LoadPhysicalData((void**)AttributeData);

			for(ulong Index = 0; Index < m_FaceCount; ++Index)
			{
				AttributeData[Index] = Parser->GetFaceMaterial(Index);
			}

			m_AttributeBuffer->UnloadPhysicalData();

			return true;
		}

		return false;
	}

	bool GeometryResource::Draw(IShader* Shader, ulong MeshID)
	{
		return Mesh::Draw(Shader, MeshID);
	}

} //Namespace