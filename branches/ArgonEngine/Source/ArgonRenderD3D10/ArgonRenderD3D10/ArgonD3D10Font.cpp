#include "ArgonD3D10Font.h"
#include "ArgonD3D10RenderTarget.h"
#include "ArgonD3D10ShaderCompiler.h"

#include "Dxerr.h"

namespace Argon
{
	ID3DX10Sprite* D3D10Font::m_Sprite = NULL;

	D3D10Font::D3D10Font(uint Height, uint Width, IFont::FontFlags Flags)
		: m_Height(Height),
		m_Width(Width),
		m_Flags(Flags)
	{

	}

	D3D10Font::~D3D10Font()
	{

	}

	bool D3D10Font::Load()
	{
		++m_RefCount;
		
		ID3D10Device* Device = D3D10RenderSystem::instance()->GetDevice()->GetDevice();

		if(!m_Sprite)
		{
			if(D3DX10CreateSprite(Device, 1, &m_Sprite) != S_OK)
			{
				assert(false);
			}
		}

		
		if(D3DX10CreateFontA(Device, m_Height, m_Width, m_Flags, 1, 0, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &m_Font) == S_OK)
		{
			return true;
		}

		return false;
	}

	bool D3D10Font::UnLoad()
	{
		if(m_RefCount > 1)
		{
			--m_RefCount;
		}
		else
		{
			//Release D3D10 Resources
			assert(m_Font->Release() == 0);

			//Unload this object
			IArgonUnknownImp<IFont, GUID_IFont>::UnLoad();
		}

		return false;
	}

	bool D3D10Font::Bind()
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

	bool D3D10Font::Draw(String Text, Vector4 Col, Vector3 Position, Vector3 Scale, TextAlign Align)
	{
		RECT Rectangle;
		Rectangle.left = (long)Position.x;
		Rectangle.top = (long)Position.y;
		Rectangle.right = 0;
		Rectangle.bottom = 0;

		HRESULT hr = S_OK;
		hr = m_Font->PreloadTextA(Text.c_str(), Text.Length());
		hr = m_Font->DrawTextA(m_Sprite, Text.c_str(), Text.Length(), &Rectangle, Align | DT_NOCLIP, D3DXCOLOR(Col.x, Col.y, Col.z, Col.w));

		const char* Error = DXGetErrorStringA(hr);
		const char* Desc = DXGetErrorDescriptionA(hr);

		char Dir[4096];
		Dir[4095] = '\0';
		GetCurrentDirectoryA(4096, Dir);

		if(hr == S_OK)
			return true;

		return false;
	}

	bool D3D10Font::UnBind()
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
}