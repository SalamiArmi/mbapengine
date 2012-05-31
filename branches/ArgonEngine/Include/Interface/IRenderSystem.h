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
		virtual bool Load() = 0;
	
		///GETDRIVERCOUNT(SIZE_T)
		///
		///Get all the supported drivers for this renderer and computer
		///
		///No Params:
		virtual size_t GetDriverCount() = 0;

		///GETDRIVER(IDRIVER)
		///
		///Get a driver from the renderer
		///
		///Param Index: Which driver to retrieve
		virtual IDriver* GetDriver(size_t Index);

		///CREATEDEVICE(BOOL)
		///
		///Create a new Device Specific to the paramater Flags
		///
		///
		///Param DriverIndex: The driver that will be used to create the Device
		///Param ModeIndex: The video description
		///Param Window: The window that will be rendered to
		virtual bool CreateDevice(uint DriverIndex, uint ModeIndex, void* Window);

		//////////////////////////////////////////////////////////////////////////////////
		// Wrapper for RenderSystem type mainly used in engine or internally

		///BEGINFRAME(BOOL)
		///
		///Announce that the frame is about to start rendering
		/// return false if this fails must not end frame will produce error
		///
		///No Params:
		virtual bool BeginFrame() = 0;

		///ENDFRAME(BOOL)
		///
		///End the last frame and present to the user
		///If fails will return false
		///
		///No Params:
		virtual bool EndFrame() = 0;

		///SETMATRIX(VOID)
		///
		///Set a matrix to the renderer
		///Will mainly be used in the camera
		///
		///Param Matrix: The matrix that will be set
		///Param Type: The type of matrix that will be set
		virtual void SetMatrix(Matrix4 Matrix, MatrixType Type) = 0;

		///SETRENDERTARGET(VOID)
		///
		///Set the rendersystems current rendertarget
		///
		///Param RenderTarget: The rendertaget that will be used
		virtual void SetRenderTarget(ISurface* RenderTarget) = 0;

		///SETDEPTHSTENCIL(VOID)
		///
		///Set the depth stencil that will be used in the renderer
		///
		///Param DepthStencil: The surface that will be used
		virtual void SetDepthStencil(ISurface* DepthStencil) = 0;

		///SETCLEARCOLOR(VOID)
		///
		///Set the Device Clear color when starting a new frame
		///
		///Param A: Aplha
		///Param R: Red
		///Param G: Green
		///Param B: Blue
		virtual void SetClearColor(float A, float R, float G, float B) = 0;

		///CREATERENDERTARGET(ISURFACE)
		///
		///Create a new render target and return it
		///
		///Param Width: The width of the RenderTarget
		///Param Height: The height of the RenderTarget
		///Param Format: The format in which the pixels will be arranged in this object
		virtual ISurface* CreateRenderTarget(uint Width, uint Height, Format Format) = 0;

		///CREATETEXTURE(ITEXTURE)
		///
		///Create a new Texture and return it
		///
		///Param Width: The width of the Texture
		///Param Height: The height of the Height
		///Param Format: The format in which the pixels will be arranged in this object
		///Param Renderable: Can this Texture be rendered to
		virtual ITexture* CreateTexture(uint Width, uint Height, Format Format, bool Renderable) = 0;

		///CREATETEXTURE(ITEXTURE)
		///
		/// Create a texture from file
		///
		///Param Filename: The file to attempt to open
		virtual ITexture* CreateTexture(String Filename) = 0;

		///CREATEDEPTHSTENCIL(ISURFACE)
		///
		///Create a new depth stencil buffer
		///
		///
		///Param Width: The width of the DepthStencil
		///Param Height: The height of the DepthStencil
		///Param Format: The format in which the pixels will be arranged in this object
		virtual ISurface* CreateDepthStencil(uint Width, uint Height, Format Format) = 0;

		///CREATEVIEWPORT(IVIEWPORT)
		///
		/// Create a new viewport
		///
		///Param Width: The desired with of the Viewport
		///Param Height: The desired height of the Viewport
		///Param PositionX: The top left corner of the viewport along the X axis
		///Param PositionY: The top left corner of the viewport along the Y axis
		virtual IViewport* CreateViewport(uint Width, uint Height, uint PositionX, uint PositionY) = 0;

		///CREATEVIEWPORT(IVIEWPORT)
		///
		/// Create a new viewport
		///
		///Param Size: The desired size of the Viewport
		///Param Position: The starting position starting from the top left corner
		virtual IViewport* CreateViewport(Vector2T<uint> Size, Vector2T<uint> Position) = 0;

		///CREATESHADER(ISHADER)
		///
		/// Create a shader from Memory
		///
		///Param ResourceName: The Resource name of the Shader on file
		///Param FileData: The compiled shader
		virtual IShader* CreateShader(String ResourceName, String FileData) = 0;

		///SETVIEWPORT(VOID)
		///
		///Set the viewport for the render system
		///
		///Param Viewport: the main viewport to render to
		virtual void SetViewport(IViewport* Viewport) = 0;

		///SETVERTEXDECLARATION(VOID)
		///
		///Set the vertex declaratio
		///
		///Params VertexDecl: The vertex Declarartion that will be set
		virtual void SetVertexDeclaration(VertexDeclaration* VertexDecl, ulong Size) = 0;

		///GETVIEWPORT(IVIEWPORT)
		///
		/// Get the desired viewport at the Index
		///
		///Param Index: Which Viewport to retrieve
		virtual IViewport* GetViewport(uint Index) = 0;

		///CREATEAFONT(IFONT)
		///
		/// Create a new Font
		///
		///No Params:
		virtual IFont* CreateAFont() = 0;

		///GETFONT(IFONT)
		///
		/// Get the Desired Font at the Index
		///
		///Param Index: Which Font to retrieve
		virtual IFont* GetFont(uint Index) = 0;

		///CREATEBUFFER(IBUFFER)
		///
		/// Create a new Buffer
		///
		///Param Type: The type of buffer to create
		virtual IBuffer* CreateBuffer(IBuffer::BufferType Type, IBuffer::Usage Usage, ulong DataSize) = 0;

		///CREATEBUFFER(IBUFFER)
		///
		/// Create a new Buffer
		///
		///Param Type: The type of buffer to create
		///Param Data: The Data the will be added to the Buffer
		///Param DataSize: The total size of the buffer in bytes
		virtual IBuffer* CreateBuffer(IBuffer::BufferType Type, IBuffer::Usage Usage, char* Data, ulong DataSize) = 0;

		///SETBUFFER(BOOL)
		///
		/// Create a new Buffer
		///
		///Param Type: The type of buffer to set
		///Param Buffer: The buffer that will be added to the render system
		virtual bool SetBuffer(IBuffer::BufferType Type, IBuffer* Buffer) = 0;

		///SETTOPOLOFY(BOOL)
		///
		/// Set the Buffer Topology
		///
		///Param Type: The type of Topology that will be used to create the final render
		virtual bool SetTopology(Topology Type) = 0;

		///CREATESPRITE(ISPRITE)
		///
		/// Create a sprite that will be used for drawing GUI elements and instances very quick
		///
		///Param MaxInstances: The max amount of instances this sprite can render at once
		virtual ISprite* CreateSprite(uint MaxInstances) = 0;

		///DRAWPRIMITIVE(VOID)
		///
		/// Draw the Mesh ID with the current set Vertex and Index Buffers.
		///
		///Param MeshID: The information about the ID to be Rendered
		virtual void DrawPrimitive(MeshID& ID) = 0;
		
	EndInterface(IRenderSystem) //Interface

} //Namespace

#endif //