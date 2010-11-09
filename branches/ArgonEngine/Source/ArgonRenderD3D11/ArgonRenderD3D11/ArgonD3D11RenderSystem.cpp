#include "ArgonD3D11RenderSystem.h"
#include "ArgonD3D11RenderTarget.h"
#include "ArgonD3D11Buffer.h"
#include "ArgonD3D11DepthStencil.h"

#include "ArgonD3D11RenderSystemExport.h"

namespace Argon
{
	D3D11RenderSystem::D3D11RenderSystem() 
		: m_Device(NULL)
	{
	}

	D3D11RenderSystem::~D3D11RenderSystem()
	{	
	}

	bool D3D11RenderSystem::Load()
	{
		m_Device = new D3D11Device();
		m_Device->Load();

		return false;
	}

	bool D3D11RenderSystem::UnLoad()
	{		
		return false;
	}

	QString D3D11RenderSystem::GetName()
	{
		return "D3D11 RenderSystem";
	}

	size_t D3D11RenderSystem::GetDriverCount()
	{
		return m_Device->GetDriverCount();
	}

	IDriver* D3D11RenderSystem::GetDriver(size_t Index)
	{
		return m_Device->GetDriver(Index);
	}

	bool D3D11RenderSystem::CreateDevice(size_t DriverIndex, uint ModeIndex, void* Window)
	{
		return m_Device->CreateDevice(DriverIndex, ModeIndex, Window);
	}

	void D3D11RenderSystem::RenderMesh(IMesh* Mesh)
	{	
		m_Device->GetDeviceContext()->IASetVertexBuffers(0, 1, (ID3D11Buffer* const*)((D3D11Buffer*)Mesh->GetVertexBuffer())->GetD3D11Buffer(), 0 /*&Mesh->GetStride()*/, 0);
		
		DXGI_FORMAT IndexFormat;
		if(Mesh->GetVertexBuffer()->Is32Bit())
			IndexFormat = DXGI_FORMAT_R16_UINT;
		else
			IndexFormat = DXGI_FORMAT_R32_UINT;
		
		m_Device->GetDeviceContext()->IASetIndexBuffer((ID3D11Buffer*)((D3D11Buffer*)Mesh->GetIndexBuffer())->GetD3D11Buffer(), IndexFormat, 0);
		m_Device->GetDeviceContext()->Draw(Mesh->GetVertexCount(), Mesh->GetStartVertex());
	}

	ISurface* D3D11RenderSystem::CreateRenderTarget(uint Width, uint Height, ISurface::Format Format)
	{
		return new D3D11RenderTarget(Width, Height, Format);
	}

	ISurface* D3D11RenderSystem::CreateDepthStencil(uint Width, uint Height, ISurface::Format Format)
	{
		return new D3D11DepthStencil(Width, Height, Format);
	}

	bool D3D11RenderSystem::BeginFrame()
	{
		m_Device->GetDeviceContext()->Begin(NULL); 
		return true;
	}

	bool D3D11RenderSystem::EndFrame()
	{
		m_Device->GetDeviceContext()->End(NULL);
		return true;
	}

	void D3D11RenderSystem::SetMatrix(Matrix4 Matrix, MatrixType Type)
	{
		if(Type & MATRIXTYPE_Projection)
		{
			
		}
	}

	void D3D11RenderSystem::SetRenderTarget(ISurface* RenderTarget)
	{
	}

	void D3D11RenderSystem::SetDepthStencil(ISurface* DepthStencil)
	{
	}

	void D3D11RenderSystem::SetViewport(IViewport* Viewport)
	{
	}

	void D3D11RenderSystem::SetVertexDeclaration(IMesh::VertexDeclaration VertexDecl)
	{
	}

	D3D11Device* D3D11RenderSystem::GetDevice()
	{
		return m_Device;
	}

} //Namespace