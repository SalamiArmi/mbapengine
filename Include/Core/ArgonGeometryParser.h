#ifndef _ARGONGEOMETRYPARSER_HEADER_
#define _ARGONGEOMETRYPARSER_HEADER_

#include "ArgonParser.h"

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonString.h>
#include <Standard/ArgonVector.h>
#include <Standard/ArgonVector3.h>

namespace Argon
{
	class GeometryParser : public Parser
	{
	public:
		~GeometryParser();

		///GETFACECOUNT(ULONG)
		///
		///Get the face count of the parsed geometry file
		///
		///No Params
		ulong GetFaceCount();

		///GETFACEMATERIAL(UINT)
		///
		///Get the 
		///
		///Param Face: Which face will the Material be for
		uint GetFaceMaterial(ulong Face);

		///GETFACEINDEX(ULONG)
		///
		///Get a face Index
		///
		///Param Face: Which face to use
		///Param VertexIndex: An index starting at 0 and max Indicies per face
		ulong GetFaceIndex(ulong Face, ushort VertexIndex);

		///GETFACEATTRIBUTE(ULONG)
		///
		///Get the Material ID used for a specific face
		///
		///Param Face: The face that will be used when retrieving the data
		ulong GetFaceAttribute(ulong Face);

		///GETVERTEXCOUNT(ULONG)
		///
		///Get the Vertex count of the parsed geometry file
		///
		///No Params
		ulong GetVextexCount();

		///GETMATERIALCOUNT(ULONG)
		///
		///Get the Material count of the parsed geometry file
		///
		///No Params
		uint GetMaterialCount();

		///GETMATERIALNAME(ULONG)
		///
		///Get the Material name as a resource name
		///
		///Param MaterialIndex: The Index of the material name
		String GetMaterialName(uint MaterialIndex);

		///GETMATERIALIDNAME(ULONG)
		///
		///Get the Material name not the resource
		///
		///Param MaterialIndex: The Index of the material name
		String GetMaterialIDName(uint MaterialIndex);

	protected:
		Vector<Vector3>				m_Vertices;
		Vector<ulong>				m_Indices;
		Vector<ulong>				m_Attributes;
		Vector<uint>				m_FaceMaterial;
		Vector<Vector3>				m_TexCoord;
		Vector<Vector3>				m_Normals;
		Vector<String>				m_MaterialNames;
	}; //Class
} //Namespace

#endif //_ARGONGEOMETRYPARSER_HEADER_