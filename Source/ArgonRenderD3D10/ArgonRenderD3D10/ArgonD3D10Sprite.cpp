#include "ArgonD3D10Sprite.h"

namespace Argon
{
	D3D10Sprite::D3D10Sprite(uint InstanceMax)
		: m_Sprite(NULL),
		m_InstanceMax(InstanceMax)
	{
		m_BufferedSprites.Clear();
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

		return IArgonUnknownImp<IFont, GUID_IFont>::UnLoad();
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
			return (m_Sprite->DrawSpritesImmediate(&m_BufferedSprites[0], m_BufferedSprites.Size(), sizeof(D3DX10_SPRITE)) == S_OK);
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
			m_BufferedSprites.Push_Back(D3DX10_SPRITE()));

			m_BufferedSprites.Back().matWorld = (D3DXMATRIX)Worldtransform;

			m_BufferedSprites.Back().TexCoord = (D3DXVECTOR2)TexCoord;
			m_BufferedSprites.Back().TexSize = (D3DXVECTOR2)TextureSize;

			m_BufferedSprites.Back().pTexture = Texture->GetD3D10ShaderResource();

			m_BufferedSprites.Back().TextureIndex = 1;

			return true;
		}

		return false;
	}

	void D3D10Sprite::SetTransform(IRenderSystem::MatrixType MatrixType, Matrix4& Matrix)
	{

	}
	
} //namespace