#ifndef _ARGOND3D10RENDERSYSTEM_HEADER_
#define _ARGOND3D10RENDERSYSTEM_HEADER_

#include <Interface/IArgonUnknownImp.h>
#include <Interface/IRenderSystem.h>
#include <Interface/IComponent.h>
#include <Interface/IFont.h>

#include <Standard/ArgonSingleton.h>

#include "ArgonD3D10Device.h"

#include <assert.h>

namespace Argon
{
	//Predefines
	class D3D10RenderTarget;
	class D3D10DepthStencil;
	class Mesh;
	class D3D10Shader;

	class D3D10RenderSystem : ArgonImplements IArgonUnknownImp2<IRenderSystem, GUID_IRenderSystem, IComponent, GUID_IComponent>, public singleton<D3D10RenderSystem>
	{
		friend singleton;
	public:
		bool		UnLoad();
		bool		Load();

		////////////////////////////////////////////////////////
		// IComponent Implementation
		QString		GetName();

		////////////////////////////////////////////////////////
		// IRenderSystem Implementation
		size_t		GetDriverCount();
		IDriver*	GetDriver(size_t Index);
		bool		CreateDevice(uint DriverIndex, uint VideoModeIndex, void* Window);
		ISurface*	CreateRenderTarget(uint Width, uint Height, Format Format);
		ISurface*	CreateDepthStencil(uint Width, uint Height, Format Format);
		void		SetClearColor(float A, float R, float G, float B);

		//////////////////////////////////////////////////////////////////////////////////
		// Wrapper for RenderSystem type mainly used in engine or internally
		bool		BeginFrame();
		bool		EndFrame();
		bool		PresentFrame();
		void 		SetMatrix(Matrix4 Matrix, MatrixType Type);
		void 		SetRenderTarget(ISurface* RenderTarget);
		ITexture*	CreateTexture(uint Width, uint Height, Format Format, bool Renderable);
		ITexture*	CreateTexture(String Filename);
		void 		SetViewport(IViewport* Viewport);
		void 		SetVertexDeclaration(VertexDeclaration* VertexDecl, ulong Size);
		void		SetDepthStencil(ISurface* DepthStencil);
		IViewport*	CreateViewport(uint Width, uint Height, uint PositionX, uint PositionY);
		IViewport*	CreateViewport(Vector2T<uint> Size, Vector2T<uint> Position);
		IViewport*	GetViewport(uint Index);
		IFont*		CreateAFont();
		IFont*		GetFont(uint Index);
		
		IBuffer*	CreateBuffer(IBuffer::BufferType Type, IBuffer::Usage Usage, ulong DataSize);
		IBuffer*	CreateBuffer(IBuffer::BufferType Type, IBuffer::Usage Usage, char* Data, ulong DataSize);
		bool		SetBuffer(IBuffer::BufferType Type, IBuffer* Buffer);
		bool		SetTopology(Topology Type);
		void		DrawPrimitive( MeshID& ID );

		///GETDEVICE(D3D10DEVICE)
		///
		///Get the D3D10Device from the rendersystem
		///
		///No Params:
		D3D10Device*		GetDevice();
		
		///GETBACKBUFFER(D3D10RENDERTARGET)
		///
		/// Get the Device back buffer
		/// Internal use only
		/// 
		///No Params:
		D3D10RenderTarget*	GetBackBuffer();

	protected:
		virtual ~D3D10RenderSystem();
		D3D10RenderSystem();

		uint				m_Width;
		uint				m_Height;
		float				m_ClearColor[4];

		Vector<IViewport*>	m_Viewports;
		Vector<IFont*>		m_Fonts;

	private:
		D3D10Device*		m_Device;
		D3D10RenderTarget*	m_BackBuffer;
		D3D10RenderTarget*	m_RenderTarget;
		D3D10DepthStencil*	m_DepthStencil;

		D3D10Shader*		m_BoundShader;
		ID3D10InputLayout*	m_InputLayout;
	};

} //Namespace

#endif //_ARGOND3D10RENDERSYSTEM_HEADER_