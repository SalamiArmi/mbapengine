#ifndef _IRENDERSYSTEM_HEADER_
#define _IRENDERSYSTEM_HEADER_

#include "IArgonUnknown.h"
#include "IDriver.h"
#include "ISurface.h"
#include "ITexture.h"
#include "IViewport.h"
#include "IFont.h"
#include "IBuffer.h"
#include "IShader.h"
#include "ISprite.h"

#include <Standard/ArgonMatrix4.h>

namespace Argon
{
	class Mesh;

	struct MeshID
	{
		ulong MaterialID;
		ulong VertexStart;
		ulong VertexCount;
		ulong FaceStart;
		ulong IndexCount;
	};

	DeclareBasedInterface(IRenderSystem, IArgonUnknown)

		enum MatrixType
		{
			MATRIXTYPE_World,
			MATRIXTYPE_View,
			MATRIXTYPE_Projection,
		};

		enum CreateType
		{
			CREATE_Viewport,
			CREATE_RenderTarget,
			CREATE_DepthStencil,
		};

		enum VertexDeclaration
		{
			VERTEXDECL_Unknown					= (1 << 1),
			VERTEXDECL_Position					= (1 << 2),			//Always a Vector3
			VERTEXDECL_Normal					= (1 << 3),			//Always a Vector3
			VERTEXDECL_TexCoord					= (1 << 4),			//Always a Vector2
			VERTEXDECL_TexCoord1				= (1 << 5),			//Always a Vector2
			VERTEXDECL_Tangent					= (1 << 6),			//Always a Vector3	
			VERTEXDECL_Binormal					= (1 << 7),			//Always a Vector3
			VERTEXDECL_TesselationFactor		= (1 << 8),			//Alwyas a Real
			VERTEXDECL_Color					= (1 << 9),			//Always a Vector4
		};

		enum Topology
		{
			TOPOLOGY_PointList,
			TOPOLOGY_LineList,
			TOPOLOGY_TriangleList,
			TOPOLOGY_TriangleStrip,
		};

		///LOAD(BOOL)
		///
		///Load and init all possible information
		///
		///No Params:
		bool Load() = 0;
	
		///GETDRIVERCOUNT(SIZE_T)
		///
		///Get all the supported drivers for this renderer and computer
		///
		///No Params:
		size_t GetDriverCount() = 0;

		///GETDRIVER(IDRIVER)
		///
		///Get a driver from the renderer
		///
		///Param Index: Which driver to retrieve
		IDriver* GetDriver(size_t Index);

		///CREATEDEVICE(BOOL)
		///
		///Create a new Device Specific to the paramater Flags
		///
		///
		///Param DriverIndex: The driver that will be used to create the Device
		///Param ModeIndex: The video description
		///Param Window: The window that will be rendered to
		bool CreateDevice(uint DriverIndex, uint ModeIndex, void* Window);

		//////////////////////////////////////////////////////////////////////////////////
		// Wrapper for RenderSystem type mainly used in engine or internally

		///BEGINFRAME(BOOL)
		///
		///Announce that the frame is about to start rendering
		/// return false if this fails must not end frame will produce error
		///
		///No Params:
		bool BeginFrame() = 0;

		///ENDFRAME(BOOL)
		///
		///End the last frame and present to the user
		///If fails will return false
		///
		///No Params:
		bool EndFrame() = 0;

		///SETMATRIX(VOID)
		///
		///Set a matrix to the renderer
		///Will mainly be used in the camera
		///
		///Param Matrix: The matrix that will be set
		///Param Type: The type of matrix that will be set
		void SetMatrix(Matrix4 Matrix, MatrixType Type) = 0;

		///SETRENDERTARGET(VOID)
		///
		///Set the rendersystems current rendertarget
		///
		///Param RenderTarget: The rendertaget that will be used
		void SetRenderTarget(ISurface* RenderTarget);

		///SETDEPTHSTENCIL(VOID)
		///
		///Set the depth stencil that will be used in the renderer
		///
		///Param DepthStencil: The surface that will be used
		void SetDepthStencil(ISurface* DepthStencil);

		///SETCLEARCOLOR(VOID)
		///
		///Set the Device Clear color when starting a new frame
		///
		///Param A: Aplha
		///Param R: Red
		///Param G: Green
		///Param B: Blue
		void SetClearColor(float A, float R, float G, float B);

		///CREATERENDERTARGET(ISURFACE)
		///
		///Create a new render target and return it
		///
		///Param Width: The width of the RenderTarget
		///Param Height: The height of the RenderTarget
		///Param Format: The format in which the pixels will be arranged in this object
		ISurface* CreateRenderTarget(uint Width, uint Height, Format Format);

		///CREATETEXTURE(ITEXTURE)
		///
		///Create a new Texture and return it
		///
		///Param Width: The width of the Texture
		///Param Height: The height of the Height
		///Param Format: The format in which the pixels will be arranged in this object
		///Param Renderable: Can this Texture be rendered to
		ITexture* CreateTexture(uint Width, uint Height, Format Format, bool Renderable);

		///CREATETEXTURE(ITEXTURE)
		///
		/// Create a texture from file
		///
		///Param Filename: The file to attempt to open
		ITexture* CreateTexture(String Filename);

		///CREATEDEPTHSTENCIL(ISURFACE)
		///
		///Create a new depth stencil buffer
		///
		///
		///Param Width: The width of the DepthStencil
		///Param Height: The height of the DepthStencil
		///Param Format: The format in which the pixels will be arranged in this object
		ISurface* CreateDepthStencil(uint Width, uint Height, Format Format);

		///CREATEVIEWPORT(IVIEWPORT)
		///
		/// Create a new viewport
		///
		///Param Width: The desired with of the Viewport
		///Param Height: The desired height of the Viewport
		///Param PositionX: The top left corner of the viewport along the X axis
		///Param PositionY: The top left corner of the viewport along the Y axis
		IViewport* CreateViewport(uint Width, uint Height, uint PositionX, uint PositionY);

		///CREATEVIEWPORT(IVIEWPORT)
		///
		/// Create a new viewport
		///
		///Param Size: The desired size of the Viewport
		///Param Position: The starting position starting from the top left corner
		IViewport* CreateViewport(Vector2T<uint> Size, Vector2T<uint> Position);

		///CREATESHADER(ISHADER)
		///
		/// Create a shader from Memory
		///
		///Param ResourceName: The Resource name of the Shader on file
		///Param FileData: The compiled shader
		IShader* CreateShader(String ResourceName, String FileData);

		///SETVIEWPORT(VOID)
		///
		///Set the viewport for the render system
		///
		///Param Viewport: the main viewport to render to
		void SetViewport(IViewport* Viewport);

		///SETVERTEXDECLARATION(VOID)
		///
		///Set the vertex declaratio
		///
		///Params VertexDecl: The vertex Declarartion that will be set
		void SetVertexDeclaration(VertexDeclaration* VertexDecl, ulong Size);

		///GETVIEWPORT(IVIEWPORT)
		///
		/// Get the desired viewport at the Index
		///
		///Param Index: Which Viewport to retrieve
		IViewport* GetViewport(uint Index);

		///CREATEAFONT(IFONT)
		///
		/// Create a new Font
		///
		///No Params:
		IFont* CreateAFont();

		///GETFONT(IFONT)
		///
		/// Get the Desired Font at the Index
		///
		///Param Index: Which Font to retrieve
		IFont* GetFont(uint Index);

		///CREATEBUFFER(IBUFFER)
		///
		/// Create a new Buffer
		///
		///Param Type: The type of buffer to create
		IBuffer* CreateBuffer(IBuffer::BufferType Type, IBuffer::Usage Usage, ulong DataSize);

		///CREATEBUFFER(IBUFFER)
		///
		/// Create a new Buffer
		///
		///Param Type: The type of buffer to create
		///Param Data: The Data the will be added to the Buffer
		///Param DataSize: The total size of the buffer in bytes
		IBuffer* CreateBuffer(IBuffer::BufferType Type, IBuffer::Usage Usage, char* Data, ulong DataSize);

		///SETBUFFER(BOOL)
		///
		/// Create a new Buffer
		///
		///Param Type: The type of buffer to set
		///Param Buffer: The buffer that will be added to the render system
		bool SetBuffer(IBuffer::BufferType Type, IBuffer* Buffer);

		///SETTOPOLOFY(BOOL)
		///
		/// Set the Buffer Topology
		///
		///Param Type: The type of Topology that will be used to create the final render
		bool SetTopology(Topology Type);

		///DRAWPRIMITIVE(VOID)
		///
		/// Draw the Mesh ID with the current set Vertex and Index Buffers.
		///
		///Param MeshID: The information about the ID to be Rendered
		void DrawPrimitive(MeshID& ID);

		///CREATESPRITE(ISPRITE)
		///
		/// Create a sprite that will be used for drawing GUI elements and instances very quick
		///
		///Param MaxInstances: The max amount of instances this sprite can render at once
		ISprite* CreateSprite(uint MaxInstances);
		
	EndInterface(IRenderSystem) //Interface

} //Namespace

#endif //