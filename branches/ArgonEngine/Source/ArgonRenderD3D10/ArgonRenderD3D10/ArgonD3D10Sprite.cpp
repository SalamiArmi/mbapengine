#include "ArgonD3D10Sprite.h"
#include "ArgonD3D10Texture.h"

namespace Argon
{
	D3D10Sprite::D3D10Sprite(uint InstanceMax)
		: m_Sprite(NULL),
		m_InstanceMax(InstanceMax)
	{
		m_BufferedSprites.Clear();
		m_RefCount = 0;
	}

	D3D10Sprite::~D3D10Sprite()
	{
		
	}

	bool D3D10Sprite::Load()
	{
		ArgonAssert(m_RefCount == 0);
		++m_RefCount;

		if(!m_Sprite)
		{
			if(D3DX10CreateSprite(D3D10RenderSystem::instance()->GetDevice()->GetDevice(), m_InstanceMax, &m_Sprite) != S_OK)
			{
				ArgonAssert(false);
			}
		}

		return true;
	}

	bool D3D10Sprite::UnLoad()
	{
		if(m_Sprite)
		{
			if(m_Sprite->Release() != 0)
			{
				ArgonAssert(false);
			}
		}

		return IArgonUnknownImp<ISprite, GUID_ISprite>::UnLoad();
	}

	bool D3D10Sprite::Bind()
	{
		if(m_Sprite)
		{
			if(m_Sprite->Begin(D3DX10_SPRITE_SORT_DEPTH_FRONT_TO_BACK) == S_OK)
			{
				return true;
			}
		}

		return false;
	}

	bool D3D10Sprite::Draw(bool Clear)
	{
		if(m_BufferedSprites.Size() > 0)
		{
			bool Success = (m_Sprite->DrawSpritesImmediate(&m_BufferedSprites[0], m_BufferedSprites.Size(), sizeof(D3DX10_SPRITE), 0) == S_OK);
			
			if(Clear) 
				m_BufferedSprites.Clear();

			return Success;
		}		
		return false;
	}

	bool D3D10Sprite::UnBind()
	{
		if(m_Sprite)
		{
			if(m_Sprite->End() == S_OK)
			{
				return true;
			}
		}

		return false;
	}

	bool D3D10Sprite::AddSpriteInstance(Matrix4 Worldtransform, Vector2 TexCoord, Vector2 TextureSize, ITexture* TextureResource)
	{
		D3D10Texture* Texture = reinterpret_cast<D3D10Texture*>(TextureResource);

		if(Texture->GetD3D10ShaderResource())
		{
			Vector2 NormalizedTexCoord;
			NormalizedTexCoord.x = TexCoord.x / TextureResource->GetWidth();
			NormalizedTexCoord.y = TexCoord.y / TextureResource->GetHeight();

			Vector2 NormalizedTexSize;
			NormalizedTexSize.x = TextureSize.x / TextureResource->GetWidth();
			NormalizedTexSize.y = TextureSize.y / TextureResource->GetHeight();

			m_BufferedSprites.Push_Back(D3DX10_SPRITE());

			m_BufferedSprites.Back().matWorld = (*((D3DXMATRIX*)&Worldtransform));

			m_BufferedSprites.Back().TexCoord = (*((D3DXVECTOR2*)&NormalizedTexCoord));
			m_BufferedSprites.Back().TexSize = (*((D3DXVECTOR2*)&NormalizedTexSize));

			m_BufferedSprites.Back().ColorModulate = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

			m_BufferedSprites.Back().pTexture = Texture->GetD3D10ShaderResource();

			m_BufferedSprites.Back().TextureIndex = 0;

			return true;
		}

		return false;
	}

	uint D3D10Sprite::GetSpriteInstanceCount()
	{
		return m_BufferedSprites.Size();
	}

	void D3D10Sprite::ClearSpriteInstances()
	{
		m_BufferedSprites.Clear();
	}

	void D3D10Sprite::SetTransform(IRenderSystem::MatrixType MatrixType, Matrix4& Matrix)
	{
		MatrixType;
		Matrix;
	}
	
} //namespace