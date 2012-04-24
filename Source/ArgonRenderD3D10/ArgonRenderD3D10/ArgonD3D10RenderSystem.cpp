#include "ArgonD3D10RenderSystem.h"
#include "ArgonD3D10RenderTarget.h"
#include "ArgonD3D10DepthStencil.h"
#include "ArgonD3D10Font.h"
#include "ArgonD3D10RenderSystemExport.h"
#include "ArgonD3D10VertexBuffer.h"
#include "ArgonD3D10IndexBuffer.h"
#include "ArgonD3D10Driver.h"
#include "ArgonD3D10VideoMode.h"
#include "ArgonD3D10Viewport.h"
#include "ArgonD3D10Shader.h"
#include "ArgonD3D10Texture.h"

#include <Standard/ArgonMemory.h>

namespace Argon
{
	D3D10RenderSystem::D3D10RenderSystem() 
		: m_Device(NULL),
		m_BackBuffer(NULL),
		m_DepthStencil(NULL),
		m_Width(0),
		m_Height(0)
	{
		m_RefCount = 0;
	}

	D3D10RenderSystem::~D3D10RenderSystem()
	{	
	}

	bool D3D10RenderSystem::Load()
	{
		assert(m_RefCount == 0);
		++m_RefCount;

		m_Device = new D3D10Device();
		m_Device->Load();

		return false;
	}

	bool D3D10RenderSystem::UnLoad()
	{		
		if(m_RefCount > 1)
		{
			--m_RefCount;
		}
		else
		{
#if _DEBUG
			assert(m_Device->Unload());
			assert(m_BackBuffer->UnLoad());
			assert(m_DepthStencil->UnLoad());
#else
			m_Device->Unload();
			m_BackBuffer->UnLoad();
			m_DepthStencil->UnLoad();
#endif
			
			IArgonUnknownImp2<IRenderSystem, GUID_IRenderSystem, IComponent, GUID_IComponent>::UnLoad();
			return true;
		}

		return false;
	}

	QString D3D10RenderSystem::GetName()
	{
		return "D3D10 RenderSystem";
	}

	size_t D3D10RenderSystem::GetDriverCount()
	{
		return m_Device->GetDriverCount();
	}

	IDriver* D3D10RenderSystem::GetDriver(size_t Index)
	{
		return m_Device->GetDriver(Index);
	}

	bool D3D10RenderSystem::CreateDevice(size_t DriverIndex, uint ModeIndex, void* Window)
	{
		//First store the width and height of the render targets to be created
		D3D10Driver* Driver = (D3D10Driver* )m_Device->GetDriver(DriverIndex);

		if(Driver)
		{
			D3D10VideoMode* VideoMode = (D3D10VideoMode* )Driver->GetVideoMode(ModeIndex);
			m_Width = VideoMode->GetWidth();
			m_Height = VideoMode->GetHeight();
		}

		bool Success = m_Device->CreateDevice(DriverIndex, ModeIndex, Window);

		//Create the BackBuffer render target
		ID3D10Texture2D* BackBuffer = NULL;
		ID3D10RenderTargetView* RenderTarget = NULL;
		m_Device->GetSwapChain()->GetBuffer(0, __uuidof(ID3D10Texture2D), (void**)&BackBuffer);
		m_Device->GetDevice()->CreateRenderTargetView(BackBuffer, NULL, &RenderTarget);

		//Create a Buffer without accually creating a backbuffer
		m_BackBuffer = new D3D10RenderTarget(RenderTarget);

		//Release the Referance of the device
		BackBuffer->Release();
		BackBuffer = NULL;

		//Create the Depth Stencil
		m_DepthStencil = new D3D10DepthStencil(m_Width, m_Height, FORMAT_Depth24);
		m_DepthStencil->Load();

		return Success;
	}

	ISurface* D3D10RenderSystem::CreateRenderTarget(uint Width, uint Height, Format TargetFormat)
	{
		return new D3D10RenderTarget(Width, Height, TargetFormat);
	}

	ITexture* D3D10RenderSystem::CreateTexture(uint Width, uint Height, Format TextureFormat, bool Renderable)
	{
		return NULL;//new D3D10Texture(Width, Height, TextureFormat, Renderable);
	}

	ITexture* D3D10RenderSystem::CreateTexture(String Filename)
	{
		return NULL; //TODO
	}

	ISurface* D3D10RenderSystem::CreateDepthStencil(uint Width, uint Height, Format DepthStencilFormat)
	{
		return new D3D10DepthStencil(Width, Height, DepthStencilFormat);
	}

	bool D3D10RenderSystem::BeginFrame()
	{
		//Clear Buffers
		m_BackBuffer->Clear(255, 255, 0, 0);
		m_DepthStencil->Clear();
		
		return true;
	}

	bool D3D10RenderSystem::EndFrame()
	{
		if(m_Device->GetSwapChain()->Present(0, 0) == S_OK)
		{
			m_Device->DumpMessages();
			return true;
		}
		
		return true;
	}

	void D3D10RenderSystem::SetMatrix(Matrix4 Matrix, MatrixType Type)
	{
		Matrix;
		if(Type & MATRIXTYPE_Projection)
		{
			
		}
	}

	void D3D10RenderSystem::SetRenderTarget(ISurface* RenderTarget)
	{
		m_RenderTarget = static_cast<D3D10RenderTarget*>(RenderTarget);
		//m_Device->GetDevice()->OMSetRenderTargets(1, m_RenderTarget ? m_RenderTarget->GetTexture() : m_BackBuffer->GetTexture(), m_DepthStencil ? m_DepthStencil->GetTexture() : NULL );
	}

	void D3D10RenderSystem::SetDepthStencil(ISurface* DepthStencil)
	{
		m_DepthStencil = static_cast<D3D10DepthStencil*>(DepthStencil);
		//m_Device->GetDevice()->OMSetRenderTargets(1, m_RenderTarget ? m_RenderTarget->GetTexture() : m_BackBuffer->GetTexture(), m_DepthStencil ? m_DepthStencil->GetTexture() : NULL );
	}

	void D3D10RenderSystem::SetViewport(IViewport* Viewport)
	{
		m_Device->GetDevice()->RSSetViewports(1, &static_cast<D3D10Viewport*>(Viewport)->GetD3D10Viewport());
	}

	IViewport* D3D10RenderSystem::CreateViewport(uint Width, uint Height, uint PositionX, uint PositionY)
	{
		Vector2T<uint> Dimensions = Vector2T<uint>(Width, Height);
		Vector2T<uint> Position = Vector2T<uint>(PositionX, PositionY);

		D3D10Viewport* Viewport = new D3D10Viewport(Dimensions, Position);
		Viewport->Load();
		m_Viewports.Push_Back(Viewport);

		return Viewport;
	}

	IViewport* D3D10RenderSystem::CreateViewport(Vector2T<uint> Size, Vector2T<uint> Position)
	{
		D3D10Viewport* Viewport = new D3D10Viewport(Size, Position);
		Viewport->Load();
		m_Viewports.Push_Back(Viewport);

		return Viewport;
	}

	IViewport* D3D10RenderSystem::GetViewport(uint Index)
	{
		return m_Viewports.At(Index);
	}

	IFont* D3D10RenderSystem::CreateAFont()
	{
		D3D10Font* Font = new D3D10Font(15, 10, IFont::FONTFLAGS_Light);
		if( !Font->Load() )
		{
			Font->UnLoad();
			return NULL;
		}

		m_Fonts.Push_Back( (IFont*)Font );
		return (IFont*)Font;
	}

	IFont* D3D10RenderSystem::GetFont(uint Index)
	{
		return m_Fonts.At(Index);
	}
	
	IBuffer* D3D10RenderSystem::CreateBuffer(IBuffer::BufferType Type, IBuffer::Usage Usage, char* Data, ulong DataSize)
	{
		IBuffer* Buffer = NULL;
		if(Type == IBuffer::BUFFERTYPE_VertexBuffer)
		{
			Buffer = new D3D10VertexBuffer(Usage, (float*)Data, DataSize);
		}
		else if(Type == IBuffer::BUFFERTYPE_IndexBuffer)
		{
			Buffer = new D3D10IndexBuffer(Usage, (ulong*)Data, DataSize);
		}
		else if(Type == IBuffer::BUFFERTYPE_PhysicalMemory)
		{
		}

		return Buffer;
	}

	IBuffer* D3D10RenderSystem::CreateBuffer(IBuffer::BufferType Type, IBuffer::Usage Usage, ulong DataSize)
	{
		IBuffer* Buffer = NULL;
		if(Type == IBuffer::BUFFERTYPE_VertexBuffer)
		{
			Buffer = new D3D10VertexBuffer(Usage, NULL, DataSize);
		}
		else if(Type == IBuffer::BUFFERTYPE_IndexBuffer)
		{
			Buffer = new D3D10IndexBuffer(Usage, NULL, DataSize);
		}

		return Buffer;
	}

	bool D3D10RenderSystem::SetBuffer(IBuffer::BufferType Type, IBuffer* Buffer)
	{
		if(!Buffer) 
			return false;

		if(Type == IBuffer::BUFFERTYPE_VertexBuffer)
		{
			D3D10VertexBuffer* VertexBuffer = static_cast<D3D10VertexBuffer*>(Buffer);
			m_Device->GetDevice()->IASetVertexBuffers(0, 1, VertexBuffer->GetVideoBufferPtr(), NULL, NULL);
		}
		else if(Type == IBuffer::BUFFERTYPE_IndexBuffer)
		{
			D3D10IndexBuffer* IndexBuffer = static_cast<D3D10IndexBuffer*>(Buffer);
			m_Device->GetDevice()->IASetIndexBuffer(IndexBuffer->GetVideoBufferPtr(), IndexBuffer->Is32Bit() ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT, 0);
		}

		return false;
	}

	bool D3D10RenderSystem::SetTopology(Topology Type)
	{
		D3D10_PRIMITIVE_TOPOLOGY Topology = D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED;

		switch(Type)
		{
		case TOPOLOGY_PointList:
			Topology = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
			break;
		case TOPOLOGY_LineList:
			Topology = D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
			break;
		case TOPOLOGY_TriangleList:
			Topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case TOPOLOGY_TriangleStrip:
			Topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;
		}

		m_Device->GetDevice()->IASetPrimitiveTopology(Topology);
		return (Topology != D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED);
	}
		
	void D3D10RenderSystem::DrawPrimitive(MeshID& ID)
	{
		m_Device->GetDevice()->DrawIndexed(ID.IndexCount, ID.FaceStart * 3, ID.VertexStart);
	}

	void D3D10RenderSystem::SetVertexDeclaration(VertexDeclaration* VertexDecl, ulong Size)
	{
		if(!m_BoundShader)
			return;

		if(!m_BoundShader->GetBoundPass())
			return;

		Vector<D3D10_INPUT_ELEMENT_DESC> Layout;
		Layout.Resize(Size);
		unsigned Offset = 0;

		for(ulong Index = 0; Index < Size; ++Index)
		{
			String Semantic = "";
			Layout[Index].AlignedByteOffset = Offset;
			switch(VertexDecl[Index])
			{
				case VERTEXDECL_Position:
				{
					Semantic = "POSITION";
					Layout[Index].Format = DXGI_FORMAT_R32G32B32_FLOAT;
					Offset += 3 * sizeof(float);
					break;
				}
				case VERTEXDECL_Normal:
				{
					Semantic = "NORMAL";
					Layout[Index].Format = DXGI_FORMAT_R32G32B32_FLOAT;
					Offset += 3 * sizeof(float);
					break;
				}
				case VERTEXDECL_TexCoord:
				{
					Semantic = "TEXCOORD0";
					Layout[Index].Format = DXGI_FORMAT_R32G32_FLOAT;
					Offset += 2 * sizeof(float);
					break;
				}
				case VERTEXDECL_TexCoord1:
				{
					Semantic = "TEXCOORD1";
					Layout[Index].Format = DXGI_FORMAT_R32G32_FLOAT;
					Offset += 2 * sizeof(float);
					break;
				}
				case VERTEXDECL_Tangent:
				{
					Semantic = "TANGENT";
					Layout[Index].Format = DXGI_FORMAT_R32G32B32_FLOAT;
					Offset += 3 * sizeof(float);
					break;
				}
				case VERTEXDECL_Binormal:
				{
					Semantic = "BINORMAL";
					Layout[Index].Format = DXGI_FORMAT_R32G32B32_FLOAT;
					Offset += 3 * sizeof(float);
					break;
				}
				case VERTEXDECL_Color:
				{
					Semantic = "COLOR";
					Layout[Index].Format = DXGI_FORMAT_R32G32B32_FLOAT;
					Offset += 3 * sizeof(float);
					break;
				}
			}

			Layout[Index].SemanticName = Semantic.c_str();
			Layout[Index].SemanticIndex = 0;
			Layout[Index].InputSlot = 0;
			Layout[Index].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
			Layout[Index].InstanceDataStepRate = 0;
		}

		D3D10_PASS_DESC Desc;
		m_BoundShader->GetBoundPass()->GetDesc(&Desc);
		m_Device->GetDevice()->CreateInputLayout(&Layout[0], Size, Desc.pIAInputSignature, Desc.IAInputSignatureSize, &m_InputLayout);
		m_Device->GetDevice()->IASetInputLayout(m_InputLayout);
	}
	
	void D3D10RenderSystem::SetClearColor(float A, float R, float G, float B)
	{
		m_ClearColor[0] = A;
		m_ClearColor[1] = R;
		m_ClearColor[2] = G;
		m_ClearColor[3] = B;
	}

	D3D10Device* D3D10RenderSystem::GetDevice()
	{
		return m_Device;
	}

	D3D10RenderTarget* D3D10RenderSystem::GetBackBuffer()
	{
		return m_BackBuffer;
	}


} //Namespace