#ifndef _IRENDERSYSTEM_HEADER_
#define _IRENDERSYSTEM_HEADER_

#include "IArgonUnknown.h"
#include "IMesh.h"
#include "IDriver.h"
#include "ISurface.h"
#include <Standard/ArgonMatrix4.h>

namespace Argon
{
	class IViewport;

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
		size_t		GetDriverCount() = 0;

		///GETDRIVER(IDRIVER)
		///
		///Get a driver from the renderer
		///
		///Param Index: Which driver to retrieve
		IDriver*	GetDriver(size_t Index);

		///CREATEDEVICE(BOOL)
		///
		///Create a new Device Specific to the paramater Flags
		///
		///
		///Param DriverIndex: The driver that will be used to create the Device
		///Param ModeIndex: The video description
		///Param Window: The window that will be rendered to
		bool		CreateDevice(uint DriverIndex, uint ModeIndex, void* Window);

		///RENDERMESH(VOID)
		///
		///Render a mesh to the screen
		///
		///Param Mesh: The Mesh that will be renderd
		void		RenderMesh(IMesh* Mesh);

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

		///CREATERENDERTARGET(ISURFACE)
		///
		///Create a new render target and return it
		///
		///Param Width: The width of the RenderTarget
		///Param Height: The height of the RenderTarget
		///Param Format: The format in which the pixels will be arranged in this object
		ISurface* CreateRenderTarget(uint Width, uint Height, ISurface::Format Format);

		///CREATEDEPTHSTENCIL(ISURFACE)
		///
		///Create a new depth stencil buffer
		///
		///
		///Param Width: The width of the DepthStencil
		///Param Height: The height of the DepthStencil
		///Param Format: The format in which the pixels will be arranged in this object
		ISurface* CreateDepthStencil(uint Width, uint Height, ISurface::Format Format);

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
		void SetVertexDeclaration(IMesh::VertexDeclaration VertexDecl);
		
	EndInterface(IRenderSystem) //Interface

} //Namespace

#endif //