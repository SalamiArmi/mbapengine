#ifndef _ARGONMESH_HEADER_
#define _ARGONMESH_HEADER_

#include <Standard/ArgonVector.h>

#include <Interface/IBuffer.h>
#include <Interface/IRenderSystem.h>
#include <Standard/ArgonPhysicalMemory.h>

namespace Argon
{
	class Mesh
	{
	public:

		enum LockType
		{
			LOCKTYPE_ReadOnly,
			LOCKTYPE_WriteOnly,
		};

	public:
		Mesh();
		Mesh(ulong VertexCount, ulong FaceCount, IRenderSystem::VertexDeclaration Declaration);
		~Mesh();

		///LOAD(BOOL)
		///
		///Load the Mesh Mesh with new Vertex Buffers and Index Buffers.
		///
		///No Params:
		bool Load();

		///UNLOAD(BOOL)
		///
		///Unload the mesh's Vertex and Index Buffers and release all memory
		///
		///No Params:
		bool UnLoad();

		///BIND(BOOL)
		///
		///Bind the Vertex and Index buffer to the graphics card before drawing
		///
		///No Params:
		bool Bind();

		///DRAW(BOOL)
		///
		///Draw the Geometry to the backbuffer
		///
		///Param MeshID: The Id that will be drawn
		bool Draw(ulong MeshID);
		
		///UNBIND(BOOL)
		///
		///Unbind the Vertex and Index Buffer from the graphics card
		///
		///No Params:
		bool UnBind();

		///LOCKBUFFER(VOID)
		///
		///Lock the vertex buffer if the type isn't Readonly mesh becomes invalid
		///Next bind will update the mesh
		///
		///Param BufferType: The Buffer type to be locked
		///Param Type: Will determin if the buffers are updated next bind
		///Param Data: The Data that the VertexBuffer holds
		void LockBuffer(IBuffer::BufferType BufferType, LockType Type, void** Data);

		///UNLOCKBUFFER(VOID)
		///
		///Unlock a buffer and set if the process any Threading Attributes
		///
		///Param BufferType: The desired buffer to unlock
		void UnlockBuffer(IBuffer::BufferType BufferType);

		///GETVERTEXCOUNT(UNSIGNEDLONG)
		///
		///Get the total Vertex count for this mesh
		///
		///No Params:
		ulong GetVertexCount();

		///GETFACECOUNT(UNSIGNEDLONG)
		///
		///Get the total Face count for the mesh 
		///
		///No Params:
		ulong GetFaceCount();

		///SETSTARTVERTEX(VOID)
		///
		///Set the Start Vertex that will determin how much of this mesh will be rendered
		///
		///Param Vertex: The start Vertex count in which to offset when rendering
		void SetStartVertex(ulong Vertex);
		
		///SETSTARTINDEX(VOID)
		///
		///Set the start index in which to off set when rendering
		///
		///Param Index: The index in which to offset to when attempting to render
		void SetStartIndex(ulong Index);

		///GETSTARTVERTEX(UINT)
		///
		///Get the Start Vertex that is currently being used when offsetting when rendering
		///
		///No Params:
		ulong GetStartVertex();
	
		///GETSTARTINDEX(UINT)
		///
		///Get the Start Index that is currently being used when offsetting when rendering
		///
		///No Params:
		ulong GetStartIndex();

		///GETSTRIDE(UNSIGNED)
		///
		///Get the current number of bytes used in the vertex decleration
		///
		///No Params:
		ulong GetStride();
		
		///SETVERTEXDECLERATION(UINT)
		///
		///Set the Vertex Declaration for the Mesh
		///This will cause the Mesh to become invalid until next bind
		///
		///Param Declaration: The new Decleration for the Mesh Verties
		void SetVertexDecleration(IRenderSystem::VertexDeclaration Declaration);

		///INTERSECT(BOOL)
		///
		///Check if the ray cast collides with a Collision Sphere then check the mesh
		///
		///Param CollisionOrigin: The Origin of the Ray Cast
		///Param CollisionDirection: The Direction of the Ray Cast
		///Param Intersection: The point of intersection
		///Param MaterialID: The Material ID that intersected
		bool Intersect(const Vector3& CollisionOrigin, const Vector3& CollisionDirection, Vector3& Intersection, int& MaterialID);

	protected:

		///UPLOADTOVIDEOMEMORY(VOID)
		///
		///Upload the physical nemory to video memory
		///
		///No Params:
		void UploadToVideoMemory();

		///OPTIMIZEINPLACE(BOOL)
		///
		///Optimize the Index Buffer and create the Attribute Table
		///
		///No Params:
		template<typename IndexType> bool OptimizeInplace();

		///GENERATETANGETNS(BOOL)
		///
		///Generare the tangents of each face
		///
		///No Params:
		template<typename IndexType> bool GenerateTangents();

		///GETMATERIALCOUNT(ULONG)
		///
		///Get the Heighest Attribute ID
		///
		///Params AttributeBuffer: The Attribute Ptr Buffer to search
		///Params FaceCount: The Total amount of faces to search
		ulong GetMaterialCount(ulong* AttributeBuffer, ulong FaceCount);

		///GETDECLARATIONSIZE(UNSIGNED)
		///
		///Get the size of a Declaration
		///
		///Param Decl: The Declaration being measured
		unsigned GetDeclarationSize(IRenderSystem::VertexDeclaration& Decl);

		IRenderSystem::VertexDeclaration	m_VertexDeclaration;
		PhysicalMemory<char>*				m_VertexBuffer;
		PhysicalMemory<char>*				m_IndexBuffer;
		PhysicalMemory<ulong>*				m_AttributeBuffer;
		Vector<MeshID>						m_AttributeTable;				

		ulong								m_VertexCount;
		ulong								m_FaceCount;
		unsigned							m_Stride;

		IRenderSystem::VertexDeclaration	m_VideoVertexDeclaration;
		IBuffer*							m_VideoVertexBuffer;
		IBuffer*							m_VideoIndexBuffer;

		bool								m_Dirty;
		bool								m_DirtyAttributes;
		bool								m_IndicesAre32bit;
	};
#include "ArgonMesh.inl"
} //namespace

#endif //_ARGONMESH_HEADER_