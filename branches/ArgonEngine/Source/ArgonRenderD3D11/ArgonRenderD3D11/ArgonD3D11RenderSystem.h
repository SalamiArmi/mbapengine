#ifndef _ARGOND3D11RENDERSYSTEM_HEADER_
#define _ARGOND3D11RENDERSYSTEM_HEADER_

#include "ArgonD3D11Device.h"

#include <Interface/IArgonUnknownImp.h>
#include <Interface/IRenderSystem.h>
#include <Interface/IComponent.h>

#include <Standard/ArgonSingleton.h>

namespace Argon
{
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

		//////////////////////////////////////////////////////////////////////////////////
		// Wrapper for RenderSystem type mainly used in engine or internally
		bool		BeginFrame();
		bool		EndFrame();
		bool		PresentFrame();
		void 		SetMatrix(Matrix4 Matrix, MatrixType Type);
		void 		SetRenderTarget(ISurface* RenderTarget);
		void 		SetViewport(IViewport* Viewport);
		void 		SetVertexDeclaration(IMesh::VertexDeclaration VertexDecl);

		///GETDEVICE(D3D11DEVICE)
		///
		///Get the D3D11Device from the rendersystem
		///
		///No Params:
		D3D11Device* GetDevice();

	protected:
		virtual ~D3D11RenderSystem();
		D3D11RenderSystem();

	private:
		D3D11Device* m_Device;
	};

} //Namespace

#endif //_ARGOND3D11RENDERSYSTEM_HEADER_