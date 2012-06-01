#include "ArgonD3D10Texture.h"
#include "ArgonD3D10Utils.h"

namespace Argon
{
	D3D10Texture::D3D10Texture(const Vector<char>& FileData)
		: m_Renderable(false),
		m_Width(0),
		m_Height(0),
		m_MipLevels(1),
		m_FileData(FileData),
		m_Format(FORMAT_Unknown),
		m_Pool(POOL_Managed),
		m_D3D10Texture(NULL),
		m_D3D10ShaderResource(NULL)
	{
	}

	D3D10Texture::D3D10Texture(uint Width, uint Height, Format TextureFormat, bool Renderable, uint MipLevels)
		: m_Renderable(Renderable),
		m_Width(Width),
		m_Height(Height),
		m_MipLevels(MipLevels),
		m_Format(TextureFormat),
		m_Pool(Renderable ? POOL_Default : POOL_Managed),
		m_D3D10Texture(NULL),
		m_D3D10ShaderResource(NULL)
	{
	}

	D3D10Texture::D3D10Texture(const Vector<char>& FileData, uint Width, uint Height, Format TextureFormat, bool Renderable, uint MipLevels)
		: m_Renderable(Renderable),
		m_Width(Width),
		m_Height(Height),
		m_MipLevels(MipLevels),
		m_FileData(FileData),
		m_Format(TextureFormat),
		m_Pool(Renderable ? POOL_Default : POOL_Managed),
		m_D3D10Texture(NULL),
		m_D3D10ShaderResource(NULL)
	{
	}

	D3D10Texture::~D3D10Texture()
	{
	}
	
	bool D3D10Texture::Load()
	{
		ID3D10Device* Device = D3D10RenderSystem::instance()->GetDevice()->GetDevice();

		if(m_FileData.Size() > 0)
		{
			//Check if the File Exists
			D3DX10_IMAGE_INFO ImageInfo;
			HRESULT hr = D3DX10GetImageInfoFromMemory(&m_FileData[0], m_FileData.Size(), NULL, &ImageInfo, NULL);

			D3DX10_IMAGE_LOAD_INFO LoadInfo;
			ZeroMemory(&LoadInfo, sizeof(D3DX10_IMAGE_LOAD_INFO));
			LoadInfo.Width = (m_Width == 0) ? ImageInfo.Width : m_Width;
			LoadInfo.Height = (m_Height == 0) ? ImageInfo.Height : m_Height;
			LoadInfo.MipLevels = m_MipLevels;
			LoadInfo.Usage = (m_Pool == POOL_Default) ? D3D10_USAGE_DYNAMIC : D3D10_USAGE_DEFAULT;
			//LoadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE | (m_Renderable ? D3D10_BIND_RENDER_TARGET : 0x0);
			//LoadInfo.CpuAccessFlags = D3D10_CPU_ACCESS_WRITE | D3D10_CPU_ACCESS_READ;
			//LoadInfo.MiscFlags = D3D10_RESOURCE_MISC_GENERATE_MIPS;
			//LoadInfo.Format = (m_Format == FORMAT_Unknown) ? ImageInfo.Format : ArgonFormatToD3D10(m_Format);
			//LoadInfo.Filter = D3DX10_FILTER_LINEAR;
			//LoadInfo.MipFilter = D3DX10_FILTER_LINEAR;
			//LoadInfo.pSrcInfo = &ImageInfo;

			if(hr == S_OK)
			{
				ID3D10Resource* D3D10Resource = NULL;
				hr = D3DX10CreateTextureFromMemory(Device, &m_FileData[0], m_FileData.Size(), NULL, NULL, &D3D10Resource, NULL);
				if(hr == S_OK)
				{
					m_Width = ImageInfo.Width;
					m_Height = ImageInfo.Height;

					hr = D3D10Resource->QueryInterface(__uuidof(ID3D10Texture2D), (void**)&m_D3D10Texture);
					if(hr == S_OK)
					{
						D3D10_SHADER_RESOURCE_VIEW_DESC ResourceViewDesc;
						ResourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
						ResourceViewDesc.Format = LoadInfo.Format;
						ResourceViewDesc.Texture2D.MipLevels = LoadInfo.MipLevels;
						ResourceViewDesc.Texture2D.MostDetailedMip = LoadInfo.FirstMipLevel;

						hr = Device->CreateShaderResourceView(D3D10Resource, &ResourceViewDesc, &m_D3D10ShaderResource);
						return (hr == S_OK);
					}
				}
			}
		}
		else
		{
			D3D10_TEXTURE2D_DESC TextureDesc;
			TextureDesc.Width = m_Width;
			TextureDesc.Height = m_Height;
			TextureDesc.MipLevels = m_MipLevels;
			TextureDesc.ArraySize = 1;
			TextureDesc.Format = ArgonFormatToD3D10(m_Format);
			TextureDesc.SampleDesc.Count = 1;
			TextureDesc.Usage = D3D10_USAGE_DEFAULT;
			TextureDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE | (m_Renderable ? D3D10_BIND_RENDER_TARGET : 0x0);

			HRESULT hr = Device->CreateTexture2D(&TextureDesc, NULL, &m_D3D10Texture);
			if(hr == S_OK)
			{
				D3D10_SHADER_RESOURCE_VIEW_DESC ResourceViewDesc;
				ResourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
				ResourceViewDesc.Format = TextureDesc.Format;
				ResourceViewDesc.Texture2D.MipLevels = 1;
				ResourceViewDesc.Texture2D.MostDetailedMip = 0;

				hr = Device->CreateShaderResourceView(m_D3D10Texture, &ResourceViewDesc, &m_D3D10ShaderResource);

				if(hr == S_OK)
				{
					return true;
				}
				m_D3D10Texture->Release();
				m_D3D10Texture = NULL;
			}
			
		}

		return false;
	}

	bool D3D10Texture::UnLoad()
	{
		if(m_RefCount > 1)
		{
			--m_RefCount;
			return false;
		}
		else
		{
			return IArgonUnknownImp<ITexture, GUID_ITexture>::UnLoad();
		}
	}

	uint D3D10Texture::GetHeight()
	{
		return m_Height;
	}

	uint D3D10Texture::GetWidth()
	{	
		return m_Width;
	}

	MemoryPool D3D10Texture::GetPoolType()
	{
		return m_Pool;
	}

	uint D3D10Texture::GetMipLevelCount()
	{
		return m_MipLevels;
	}

	ISurface* D3D10Texture::GetMipLevel(uint MipIndex)
	{
		MipIndex;
		return NULL;
	}

	bool D3D10Texture::GetRenderable()
	{
		return m_Renderable;
	}

	ID3D10Texture2D* D3D10Texture::GetD3D10Texture() const
	{
		return m_D3D10Texture;
	}

	ID3D10ShaderResourceView* D3D10Texture::GetD3D10ShaderResource() const
	{
		return m_D3D10ShaderResource;
	}

} //Namespace