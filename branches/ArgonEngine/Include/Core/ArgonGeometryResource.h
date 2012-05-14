#ifndef _ARGONGEOMETRYRESOURCE_HEADER_
#define _ARGONGEOMETRYRESOURCE_HEADER_

#include <Standard/ArgonVector.h>
#include "ArgonGeometryParser.h"
#include "ArgonMesh.h"
#include "ArgonMaterial.h"

namespace Argon
{
	class GeometryResource : public Mesh
	{
	public:
		GeometryResource(String Name);
		~GeometryResource();

		///SETMATERIAL(VOID)
		///
		///Attempt to set a $Material$ for this Geometry
		///
		///Param MaterialID:
		///Param Mat:
		void SetMaterial(size_t MaterialID, Material* Mat);

		///GETMATERIAL(MATERIAL)
		///
		///Attempt to get a $Material$ from this Geometry
		///
		///Param MaterialID: 
		Material* GetMaterial(size_t MaterialID);

		///REMOVEMATERIAL(BOOL)
		///
		///Attempt to remove a $Material$ from this Geometry
		///
		///Param Name:
		bool RemoveMaterial(String Name);

		///REMOVEMATERIAL(BOOL)
		///
		///Attempt to remove a $Material$ from this Geometry
		///
		///Param Mat: The $Material$ Ptr to remove
		bool RemoveMaterial(Material* Mat);

	private:

		template<typename T>
		void ParseIndexData(GeometryParser* Parser, char* Data);

		///CONSTRUCT(BOOL)
		///
		///Construct the mesh from a Parser
		///
		///Param Parser: The Parser that will be used to gain the information from
		bool Construct(GeometryParser* Parser);

		Vector<Material*> m_Materials;
		String m_Name;
	};

#include "ArgonGeometryResource.inl"

} //Namespace

#endif //_ARGONGEOMETRYRESOURCE_HEADER_