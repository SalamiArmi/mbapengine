#include "ArgonGeometryParser.h"

namespace Argon
{
	GeometryParser::~GeometryParser()
	{
	}

	ulong GeometryParser::GetFaceCount()
	{
		return ((ulong)(m_Indices.Size() / 3));
	}

	uint GeometryParser::GetFaceMaterial(ulong Face)
	{
		return ((uint)(m_FaceMaterial[Face]));
	}

	ulong GeometryParser::GetFaceIndex(ulong Face, ushort VertexIndex)
	{
		return ((ulong)(m_Indices[(Face * 3) + VertexIndex]));
	}

	ulong GeometryParser::GetFaceAttribute(ulong Face)
	{
		return m_Attributes[Face];
	}

	Vector3 GeometryParser::GetVextexPosition(ulong VertexIndex)
	{
		return m_Vertices[VertexIndex];
	}

	Vector3 GeometryParser::GetVextexNormal(ulong VertexIndex)
	{
		return m_Normals[VertexIndex];
	}

	Vector3 GeometryParser::GetVextexTexCoord(ulong VertexIndex)
	{
		return m_TexCoord[VertexIndex];
	}

	ulong GeometryParser::GetVextexCount()
	{
		return m_Vertices.Size();
	}

	uint GeometryParser::GetMaterialCount()
	{
		return m_MaterialNames.Size();
	}

	String GeometryParser::GetMaterialName(uint MaterialIndex)
	{
		return m_MaterialNames[MaterialIndex];
	}

	String GeometryParser::GetMaterialIDName(uint MaterialIndex)
	{
		return m_MaterialNames[MaterialIndex];
	}

} //Namespace