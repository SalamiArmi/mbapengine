#ifndef _IMESH_HEADER_
#define _IMESH_HEADER_

#include "IBuffer.h"

namespace Argon
{
	DeclareBasedInterface(IMesh, IArgonUnknown)

		enum VertexDeclaration
		{
			VERTEXDECL_Position = 0,		//Always a Vector3
			VERTEXDECL_Normal,				//Always a Vector3
			VERTEXDECL_TexCoord,			//Always a Vector2
			VERTEXDECL_TexCoord1,			//Always a Vector2
			VERTEXDECL_Tangent,				//Always a Vector3	
			VERTEXDECL_Binormal,			//Always a Vector3
			VERTEXDECL_TesselationFactor,	//Alwyas a Real
			VERTEXDECL_Color,				//Always a Vector4
		};

		///GETVERTEXBUFFER(IBUFFER)
		///
		///Get the Vertex buffer used to render this mesh
		///Also used to gain access to the buffers contenst
		///
		///No Params:
		IBuffer*		GetVertexBuffer()									 = 0;

		///SETVERTEXBUFFER(VOID)
		///
		///Set the vertex buffer of the mesh
		///
		///Param VertexBuffer: the new vertex buffer
		void			SetVertexBuffer(IBuffer* VertexBuffer)				= 0;

		///(IBUFFER)
		///
		///Get the Index buffer of the mesh
		///The index buffer contains the links or indices between verts
		///
		///No Params:
		IBuffer*		GetIndexBuffer()									= 0;

		///SETINDEXBUFFER(VOID)
		///
		///Set the index buffer that will be used to render this mesh
		///
		///Param IndexBuffer: The index buffer that will be used to render this mesh
		void			SetIndexBuffer(IBuffer* IndexBuffer)				= 0;

		///GETVERTEXCOUNT(UNSIGNEDLONG)
		///
		///Get the total Vertex count for this mesh
		///
		///No Params:
		ulong			GetVertexCount()									= 0;

		///GETINDEXCOUNT(UNSIGNEDLONG)
		///
		///Get the total index count for the mesh 
		///To get the Face count devide by 3
		///
		///No Params:
		ulong			GetIndexCount()										= 0;

		///SETSTARTVERTEX(VOID)
		///
		///Set the Start Vertex that will determin how much of this mesh will be rendered
		///
		///Param Vertex: The start Vertex count in which to offset when rendering
		void			SetStartVertex(uint Vertex)							= 0;
		
		///SETSTARTINDEX(VOID)
		///
		///Set the start index in which to off set when rendering
		///
		///Param Index: The index in which to offset to when attempting to render
		void			SetStartIndex(uint Index)							= 0;

		///GETSTARTVERTEX(UINT)
		///
		///Get the Start Vertex that is currently being used when offsetting when rendering
		///
		///No Params:
		uint			GetStartVertex()									= 0;
	
		///GETSTARTINDEX(UINT)
		///
		///Get the Start Index that is currently being used when offsetting when rendering
		///
		///No Params:
		uint			GetStartIndex()										= 0;

		///GETSTRIDE(UINT)
		///
		///Get the current number of bytes used in the vertex decleration
		///
		///No Params:
		uint			GetStride()											= 0;

		///GETSUBMESH(VECTOR<IMESH>)
		///
		///Get a sub mesh of this object
		///
		///No Params:
		//Vector<IMesh*> GetSubMesh();

	EndInterface(IMesh) //Interface
} //Namespace

#endif //_IMESH_HEADER_