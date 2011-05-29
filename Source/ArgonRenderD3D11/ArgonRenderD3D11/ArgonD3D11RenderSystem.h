#ifndef _ARGOND3D11RENDERSYSTEM_HEADER_
#define _ARGOND3D11RENDERSYSTEM_HEADER_

#include "ArgonD3D11Device.h"

#include <Interface/IArgonUnknownImp.h>
#include <Interface/IRenderSystem.h>
#include <Interface/IComponent.h>

#include <Standard/ArgonSingleton.h>

#include <assert.h>

namespace Argon
{
	//Predefines
	class D3D11RenderTarget;
	class D3D11DepthStencil;
		
	class D3D11RenderSystem : ArgonImplements IArgonUnknownImp2<IRenderSystem, GUID_IRenderSystem, IComponent, GUID_IComponent>, public singleton<D3D11RenderSystem>
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
		void		RenderMesh(IMesh* Mesh);
		ISurface*	CreateRenderTarget(uint Width, uint Height, ISurface::Format Format);
		ISurface*	CreateDepthStencil(uint Width, uint Height, ISurface::Format Format);
		void		SetClearColor(float A, float R, float G, float B);

		//////////////////////////////////////////////////////////////////////////////////
		// Wrapper for RenderSystem type mainly used in engine or internally
		bool		BeginFrame();
		bool		EndFrame();
		bool		PresentFrame();
		void 		SetMatrix(Matrix4 Matrix, MatrixType Type);
		void 		SetRenderTarget(ISurface* RenderTarget);
		void 		SetViewport(IViewport* Viewport);
		void 		SetVertexDeclaration(IMesh::VertexDeclaration VertexDecl);
		void		SetDepthStencil(ISurface* DepthStencil);


		///GETDEVICE(D3D11DEVICE)
		///
		///Get the D3D11Device from the rendersystem
		///
		///No Params:
		D3D11Device* GetDevice();

	protected:
		virtual ~D3D11RenderSystem();
		D3D11RenderSystem();

		uint				m_Width;
		uint				m_Height;
		float				m_ClearColor[4];

	private:
		D3D11Device*		m_Device;
		D3D11RenderTarget*	m_BackBuffer;
		D3D11DepthStencil*	m_DepthStencil;

		ID3D11Counter*		m_D3D11Counter;
	};

} //Namespace

#endif //_ARGOND3D11RENDERSYSTEM_HEADER_