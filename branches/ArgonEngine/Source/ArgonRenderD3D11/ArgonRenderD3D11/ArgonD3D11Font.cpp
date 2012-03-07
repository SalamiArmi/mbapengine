#include "ArgonD3D11Font.h"
#include "ArgonD3D11RenderTarget.h"
#include "ArgonD3D11ShaderCompiler.h"

namespace Argon
{
#define FontFile "ArgonEngine\\Content\\Font.dds"

	ID3D11InputLayout* D3D11Font::m_Decleration = NULL;

	D3D11Font::D3D11Font()
		: m_BufferBytes(0),
		m_FontBuffer(NULL)
	{

	}

	D3D11Font::~D3D11Font()
	{

	}

	bool D3D11Font::Load()
	{
		++m_RefCount;

		ID3D11Device* Device = D3D11RenderSystem::instance()->GetDevice()->GetDevice();

		m_Shader = D3D11ShaderCompiler::instance()->CompileShader( "ArgonText.ArgonShader", D3D11ShaderCompiler::SHADERMODEL_FX_3_0 );

		//Create the Vertex Decleration
		if( !m_Decleration )
		{
			//Create shader for rendering the textures
			const D3D11_INPUT_ELEMENT_DESC VertexDecl[] =
			{
				{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,       0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			Device->CreateInputLayout( VertexDecl, 3, m_Shader->GetBufferPointer(), m_Shader->GetBufferSize(), &m_Decleration );
		}

		//Create the resource for the font
		HRESULT hr = D3DX11CreateShaderResourceViewFromFileA( Device, FontFile, NULL, NULL, &m_Font, NULL);


		//if(hr != S_OK)
		//{
		//	//Log Error

		//	return false;
		//}

		return true;
	}

	bool D3D11Font::UnLoad()
	{
		if(m_RefCount > 1)
		{
			--m_RefCount;
		}
		else
		{
			//Release D3D11 Resources
			assert(m_Font->Release() == 0);

			//Unload this object
			IArgonUnknownImp<IFont, GUID_IFont>::UnLoad();
		}

		return false;
	}

	bool D3D11Font::Bind()
	{
		return false;
	}

	bool D3D11Font::Draw(String Text, Color Col, Vector3 Position, Vector3 Scale, IText::TextAlign Align)
	{
		uint BBWidth = D3D11RenderSystem::instance()->GetBackBuffer()->GetWidth();
		uint BBHeight = D3D11RenderSystem::instance()->GetBackBuffer()->GetHeight();

		float CharTexSizeX = 0.010526315f;
		float GlyphSizeX = 15.0f / (float)BBWidth;
		float GlyphSizeY = 42.0f / (float)BBHeight;

		float RectLeft = Position.x / BBWidth;
		float RectTop = 1.0f - Position.y / BBHeight;

		RectLeft = RectLeft * 2.0f - 1.0f;
		RectTop = RectTop * 2.0f - 1.0f;

		ulong TextLength = Text.Length();
		if (Align == IText::TEXTALIGN_Center) 
		{
			float RectRight = (Position.x + Scale.x) / BBWidth;
			RectRight = RectRight * 2.0f - 1.0f;
			float RectBottom = 1.0f - (Position.y + Scale.y) / BBHeight;
			RectBottom = RectBottom * 2.0f - 1.0f;
			float CenterX = ((RectRight - RectLeft) - (float)TextLength* GlyphSizeX) * 0.5f;
			float CenterY = ((RectTop - RectBottom) - (float)1 * GlyphSizeY) * 0.5f;
			RectLeft += CenterX ;    
			RectTop -= CenterY;
		}

		float OriginalLeft = RectLeft;
		float TexTop = 0.0f;
		float TexBottom = 1.0f;

		float Depth = 0.5f;
		for(ulong i=0; i< TextLength; ++i)
		{
			if( Text.At(i) == '\n' )
			{
				RectLeft = OriginalLeft;
				RectTop -= GlyphSizeY;

				continue;
			}
			else if( Text.At(i) < 32 || Text.At(i) > 126 )
			{
				continue;
			}

			// Add 6 font vertices
			FontVertex Vertex;
			float RectRight = RectLeft + GlyphSizeX;
			float RectBottom = RectTop - GlyphSizeY;
			float TexLeft = ( Text.At(i) - 32 ) * CharTexSizeX;
			float TexRight = TexLeft + CharTexSizeX;

			// tri1
			Vertex.Position = Vector3( RectLeft, RectTop, Depth );
			Vertex.TextCoord = Vector2( TexLeft, TexTop );
			Vertex.Col = Col;
			m_FontVerts.Push_Back( Vertex );

			Vertex.Position = Vector3( RectRight, RectTop, Depth );
			Vertex.TextCoord = Vector2( TexRight, TexTop );
			Vertex.Col = Col;
			m_FontVerts.Push_Back( Vertex );

			Vertex.Position = Vector3( RectLeft, RectBottom, Depth );
			Vertex.TextCoord = Vector2( TexLeft, TexBottom );
			Vertex.Col = Col;
			m_FontVerts.Push_Back( Vertex );

			// tri2
			Vertex.Position = Vector3( RectRight, RectTop, Depth );
			Vertex.TextCoord = Vector2( TexRight, TexTop );
			Vertex.Col = Col;
			m_FontVerts.Push_Back( Vertex );

			Vertex.Position = Vector3( RectRight, RectBottom, Depth );
			Vertex.TextCoord = Vector2( TexRight, TexBottom );
			Vertex.Col = Col;
			m_FontVerts.Push_Back( Vertex );

			Vertex.Position = Vector3( RectLeft, RectBottom, Depth );
			Vertex.TextCoord = Vector2( TexLeft, TexBottom );
			Vertex.Col = Col;
			m_FontVerts.Push_Back( Vertex );

			RectLeft += GlyphSizeX;
		}

		// ensure our buffer size can hold our sprites
		uint FontDataBytes = m_FontVerts.Size() * sizeof(FontVertex);
		if(m_BufferBytes < FontDataBytes)
		{
			m_FontBuffer->Release();
			m_BufferBytes = FontDataBytes;

			D3D11_BUFFER_DESC BufferDesc;
			BufferDesc.ByteWidth = m_BufferBytes;
			BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			BufferDesc.MiscFlags = 0;

			//Create the Buffer
			D3D11RenderSystem::instance()->GetDevice()->GetDevice()->CreateBuffer(&BufferDesc, NULL, &m_FontBuffer);
		}

		ID3D11DeviceContext* Context = D3D11RenderSystem::instance()->GetDevice()->GetDeviceContext();

		// Copy the sprites over
		D3D11_BOX Region;
		Region.left = 0;
		Region.right = FontDataBytes;
		Region.top = 0;
		Region.bottom = 1;
		Region.front = 0;
		Region.back = 1;
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		if ( S_OK == Context->Map(m_FontBuffer, 0x0, D3D11_MAP_WRITE_DISCARD, 0x0, &MappedResource) ) 
		{ 
			CopyMemory(MappedResource.pData, (void*)&m_FontVerts[0], m_BufferBytes);
			D3D11RenderSystem::instance()->GetDevice()->GetDeviceContext()->Unmap(m_FontBuffer, 0x0);
		}

		ID3D11ShaderResourceView* OldTexture = NULL;
		Context->PSGetShaderResources( 0, 1, &OldTexture );
		Context->PSSetShaderResources( 0, 1, &m_Font );

		// Draw
		uint Stride = sizeof(FontVertex);
		uint Offset = 0;
		Context->IASetVertexBuffers( 0, 1, &m_FontBuffer, &Stride, &Offset );
		Context->IASetInputLayout( m_Decleration );
		Context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		Context->Draw( m_FontVerts.Size(), 0 );

		Context->PSSetShaderResources( 0, 1, &OldTexture );
		OldTexture->Release();

		return true;
	}

	bool D3D11Font::UnBind()
	{
		return false;
	}
}