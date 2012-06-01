#ifndef _ARGOND3D10TEXTURE_HEADER_
#define _ARGOND3D10TEXTURE_HEADER_

#include <Interface/ITexture.h>
#include <Standard/ArgonString.h>

#include "ArgonD3D10RenderSystem.h"

namespace Argon
{
	class D3D10Texture : public IArgonUnknownImp<ITexture, GUID_ITexture>
	{
	public:
		D3D10Texture(const Vector<char>& Filedata);
		D3D10Texture(uint Width, uint Height, Format TextureFormat, bool Renderable, uint MipLevels);
		D3D10Texture(const Vector<char>& Filedata, uint Width, uint Height, Format TextureFormat, bool Renderable, uint MipLevels);
		~D3D10Texture();

		bool		UnLoad();
		bool		Load();

		///GETHEIGHT(UNSIGNEDINT)
		///
		///Get the Height of the Surface
		///
		///No Params:
		uint GetHeight();

		///GETWIDTH(UNSIGNEDINT)
		///
		///Get the Width of the Surface
		///
		///No Params
		uint GetWidth();

		///GETPOOLTYPE(MEMORYPOOL)
		///
		///Get the type of pool this item was created on
		///
		///No Params:
		MemoryPool GetPoolType();

		///GETMIPLEVELCOUNT(UNSIGNEDINT)
		///
		///Get how many MipMaps this Texture Resource contains
		///
		///No Params:
		uint GetMipLevelCount();

		///GETMIPLEVEL(ISURFACE)
		///
		///Get a specific MipLevel
		///
		///Param MipIndex: The Index of the desired MipMap
		ISurface* GetMipLevel(uint MipIndex);

		///GETRENDERABLE(BOOL)
		///
		///Can the Texture be Rendered to Via the surface
		///
		///No Params:
		bool GetRenderable();

		ID3D10Texture2D* GetD3D10Texture() const;
		ID3D10ShaderResourceView* GetD3D10ShaderResource() const;

	private:
		bool						m_Renderable;
		uint						m_Width;
		uint						m_Height;
		uint						m_MipLevels;
		Vector<char>				m_FileData;
		
		Format						m_Format;
		MemoryPool					m_Pool;

		ID3D10Texture2D*			m_D3D10Texture;
		ID3D10ShaderResourceView*	m_D3D10ShaderResource;
	};

} //Namespace

#endif //_ARGOND3D10TEXTURE_HEADER_