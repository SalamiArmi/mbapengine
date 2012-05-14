#include "ArgonGeometryResource.h"

namespace Argon
{
	GeometryResource::GeometryResource(String Name)
		: Mesh(),
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
			return true;
		}

		return false;
	}

} //Namespace