#include "ArgonD3D11RenderSystem.h"
#include "ArgonD3D11RenderTarget.h"
#include "ArgonD3D11Buffer.h"
#include "ArgonD3D11DepthStencil.h"
#include "ArgonD3D11Font.h"
#include "ArgonD3D11RenderSystemExport.h"

#include "ArgonD3D11Driver.h"
#include "ArgonD3D11VideoMode.h"

#include "ArgonD3D11Viewport.h"

#include <Standard/ArgonMemory.h>

namespace Argon
{
	D3D11RenderSystem::D3D11RenderSystem() 
		: m_Device(NULL),
		m_BackBuffer(NULL),
		m_DepthStencil(NULL),
		m_Width(0),
		m_Height(0),
		m_D3D11Counter(NULL)
	{
		m_RefCount = 0;
	}

	D3D11RenderSystem::~D3D11RenderSystem()
	{	
	}

	bool D3D11RenderSystem::Load()
	{
		assert(m_RefCount == 0);
		++m_RefCount;

		m_Device = new D3D11Device();
		m_Device->Load();

		return false;
	}

	bool D3D11RenderSystem::UnLoad()
	{		
		if(m_RefCount > 1)
		{
			--m_RefCount;
		}
		else
		{
			assert(m_Device->Unload());
			assert(m_BackBuffer->UnLoad());
			assert(m_DepthStencil->UnLoad());

			if(m_D3D11Counter)
			{
				assert(m_D3D11Counter->Release() == 0);
			}

			IArgonUnknownImp2<IRenderSystem, GUID_IRenderSystem, IComponent, GUID_IComponent>::UnLoad();
			return true;
		}

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

		bool Success = m_Device->CreateDevice(DriverIndex, ModeIndex, Window);

		//Create the BackBuffer render target
		ID3D11Texture2D* BackBuffer = NULL;
		ID3D11RenderTargetView* RenderTarget = NULL;
		m_Device->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		m_Device->GetDevice()->CreateRenderTargetView(BackBuffer, NULL, &RenderTarget);

		//Create a Buffer without accually creating a backbuffer
		m_BackBuffer = new D3D11RenderTarget(RenderTarget);

		//Release the Referance of the device
		BackBuffer->Release();
		BackBuffer = NULL;

		//Create the Depth Stencil
		m_DepthStencil = new D3D11DepthStencil(m_Width, m_Height, ISurface::FORMAT_Depth24);
		m_DepthStencil->Load();

		return Success;
	}

	void D3D11RenderSystem::RenderMesh(Mesh* RenderMesh)
	{	
		m_Device->GetDeviceContext()->IASetVertexBuffers(0, 1, (ID3D11Buffer* const*)((D3D11Buffer*)RenderMesh->GetVertexBuffer())->GetD3D11Buffer(), 0 &RenderMesh->GetStride(), 0);
		
		DXGI_FORMAT IndexFormat;
		if(RenderMesh->GetVertexBuffer()->Is32Bit())
			IndexFormat = DXGI_FORMAT_R16_UINT;
		else
			IndexFormat = DXGI_FORMAT_R32_UINT;
		
		m_Device->GetDeviceContext()->IASetIndexBuffer((ID3D11Buffer*)((D3D11Buffer*)RenderMesh->GetIndexBuffer())->GetD3D11Buffer(), IndexFormat, 0);
		m_Device->GetDeviceContext()->Draw(RenderMesh->GetVertexCount(), RenderMesh->GetStartVertex());
	}

	ISurface* D3D11RenderSystem::CreateRenderTarget(uint Width, uint Height, Format Format)
	{
		return new D3D11RenderTarget(Width, Height, Format);
	}

	ISurface* D3D11RenderSystem::CreateDepthStencil(uint Width, uint Height, Format Format)
	{
		return new D3D11DepthStencil(Width, Height, Format);
	}

	bool D3D11RenderSystem::BeginFrame()
	{
		//Clear Buffers
		m_BackBuffer->Clear(255, 255, 0, 0);
		m_DepthStencil->Clear();

		D3D11_COUNTER_DESC CounterDesc;
		CounterDesc.Counter = D3D11_COUNTER_DEVICE_DEPENDENT_0;
		CounterDesc.MiscFlags = 0;
		m_Device->GetDevice()->CreateCounter(&CounterDesc, &m_D3D11Counter);

		//Begin the new frame
		m_Device->GetDeviceContext()->Begin(m_D3D11Counter);
		
		return true;
	}

	bool D3D11RenderSystem::EndFrame()
	{
		m_Device->GetDeviceContext()->End(m_D3D11Counter);
	
		m_Device->GetSwapChain()->Present(0, 0);

		m_D3D11Counter->Release();	
		m_D3D11Counter = NULL;

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
		//m_DepthStencil = static_cast<D3D11DepthStencil*>(DepthStencil);
		//m_Device->GetDeviceContext()->OMSetRenderTargets(0, m_BackBuffer->GetTexture(), m_DepthStencil->GetTexture());
	}

	void D3D11RenderSystem::SetViewport(IViewport* Viewport)
	{
		m_Device->GetDeviceContext()->RSSetViewports(0, &static_cast<D3D11Viewport*>(Viewport)->GetD3D11Viewport());
	}

	IViewport* D3D11RenderSystem::CreateViewport(uint Width, uint Height, uint PositionX, uint PositionY)
	{
		D3D11Viewport* Viewport = new D3D11Viewport(Vector2((float)Width, (float)Height), Vector2((float)PositionX, (float)PositionY));
		Viewport->Load();
		m_Viewports.Push_Back(Viewport);

		return Viewport;
	}

	IViewport* D3D11RenderSystem::CreateViewport(Vector2 Size, Vector2 Position)
	{
		D3D11Viewport* Viewport = new D3D11Viewport(Size, Position);
		Viewport->Load();
		m_Viewports.Push_Back(Viewport);

		return Viewport;
	}

	IViewport* D3D11RenderSystem::GetViewport(uint Index)
	{
		return m_Viewports.At(Index);
	}

	IFont* D3D11RenderSystem::CreateAFont()
	{
		D3D11Font* Font = new D3D11Font();
		if( !Font->Load() )
		{
			Font->UnLoad();
			return NULL;
		}

		m_Fonts.Push_Back( (IFont*)Font );
		return (IFont*)Font;
	}

	IFont* D3D11RenderSystem::GetFont(uint Index)
	{
		return m_Fonts.At(Index);
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

	D3D11RenderTarget* D3D11RenderSystem::GetBackBuffer()
	{
		return m_BackBuffer;
	}


} //Namespace