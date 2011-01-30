#include "ArgonD3D11RenderSystem.h"
#include "ArgonD3D11RenderTarget.h"
#include "ArgonD3D11Buffer.h"
#include "ArgonD3D11DepthStencil.h"

#include "ArgonD3D11RenderSystemExport.h"

#include "ArgonD3D11Driver.h"
#include "ArgonD3D11VideoMode.h"

#include <Standard/ArgonMemory.h>

namespace Argon
{
	D3D11RenderSystem::D3D11RenderSystem() 
		: m_Device(NULL),
		m_BackBuffer(NULL),
		m_DepthStencil(NULL),
		m_Width(0),
		m_Height(0)
	{
	}

	D3D11RenderSystem::~D3D11RenderSystem()
	{	
	}

	bool D3D11RenderSystem::Load()
	{
		m_Device = new D3D11Device();
		m_Device->Load();

		//m_Device->CreateDevice(0,0,NULL);

		////Create the BackBuffer render target
		//ID3D11Texture2D* BackBuffer = NULL;
		//ID3D11RenderTargetView* RenderTarget;
		//m_Device->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		//m_Device->GetDevice()->CreateRenderTargetView(BackBuffer, NULL, &RenderTarget);

		//m_BackBuffer = new ("D3D11RenderTarget") D3D11RenderTarget(RenderTarget);

		//BackBuffer->Release();

		////Create the Depth Stencil
		//m_DepthStencil = new ("D3D11DepthStencil") D3D11DepthStencil(m_Width, m_Height, ISurface::FORMAT_Depth24);
		//m_DepthStencil->Load();

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
		//First store the width and height of the render targets to be created
		D3D11Driver* Driver = (D3D11Driver* )m_Device->GetDriver(DriverIndex);

		if(Driver)
		{
			D3D11VideoMode* VideoMode = (D3D11VideoMode* )Driver->GetVideoMode(ModeIndex);
			m_Width = VideoMode->GetWidth();
			m_Height = VideoMode->GetHeight();
		}

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
		return new ("D3D11RenderTarget") D3D11RenderTarget(Width, Height, Format);
	}

	ISurface* D3D11RenderSystem::CreateDepthStencil(uint Width, uint Height, ISurface::Format Format)
	{
		return new ("D3D11DepthStencil") D3D11DepthStencil(Width, Height, Format);
	}

	bool D3D11RenderSystem::BeginFrame()
	{
		//Clear Buffers
		ID3D11RenderTargetView* RenderTarget = m_BackBuffer->GetTexture();
		float Color[] = { 0, 0, 0, 0 };
		m_Device->GetDeviceContext()->ClearRenderTargetView(RenderTarget, Color);


		ID3D11DepthStencilView* DepthStencil = m_DepthStencil->GetTexture();
		m_Device->GetDeviceContext()->ClearDepthStencilView(DepthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		//Begin the new frame
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
	
	void D3D11RenderSystem::SetClearColor(float A, float R, float G, float B)
	{
		m_ClearColor[0] = A;
		m_ClearColor[1] = R;
		m_ClearColor[2] = G;
		m_ClearColor[3] = B;
	}

	D3D11Device* D3D11RenderSystem::GetDevice()
	{
		return m_Device;
	}

} //Namespace