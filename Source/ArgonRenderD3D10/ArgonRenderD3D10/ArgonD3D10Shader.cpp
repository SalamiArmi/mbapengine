#include "ArgonD3D10Shader.h"
#include "ArgonD3D10Texture.h"
#include "ArgonD3D10RenderTarget.h"
#include <Standard/ArgonString.h>

namespace Argon
{
	D3D10Shader::D3D10Shader(String Name, String ShaderBuffer)
		: m_Name(Name),
		m_ShaderBuffer(ShaderBuffer),
		m_Shader(NULL),
		m_BoundTechnique(NULL),
		m_BoundPass(NULL)
	{
	}

	D3D10Shader::~D3D10Shader()
	{
	}

	bool D3D10Shader::Load()
	{
		++m_RefCount;
		HRESULT hr = D3D10CreateEffectFromMemory((void *)m_ShaderBuffer.c_str(), m_ShaderBuffer.Length(), 0, D3D10RenderSystem::instance()->GetDevice()->GetDevice(), NULL, &m_Shader);
	
		return (hr == S_OK);
	}

	bool D3D10Shader::UnLoad()
	{
		if(m_RefCount > 1)
		{
			--m_RefCount;
			return false;
		}
		else
		{
#if _DEBUG
			assert(m_Shader->Release() == 0);
			m_Shader = NULL;
#else
			m_Shader->Release();
#endif
			
			return IArgonUnknownImp<IShader, GUID_IShader>::UnLoad();
		}
	}

	String D3D10Shader::GetName()
	{
		return m_Name;
	}

	bool D3D10Shader::Bind(ulong Pass)
	{
		if(!m_BoundTechnique)
			return false;

		m_BoundPass = m_BoundTechnique->GetPassByIndex((uint)Pass);
		return ((m_BoundPass) && m_BoundPass->Apply(NULL) == S_OK);
	}

	bool D3D10Shader::UnBind()
	{
		if(!m_BoundTechnique)
			return false;

		m_BoundPass = NULL;
		return true;
	}

	bool D3D10Shader::SetTechnique(String TechniqueName)
	{
		if(!m_Shader) 
			return false;
		
		m_BoundTechnique = m_Shader->GetTechniqueByName(TechniqueName.c_str());

		if(m_BoundTechnique != NULL)
		{
			m_TechniqueName = TechniqueName;
			return true;
		}

		return false; 
	}

	String D3D10Shader::GetTechnique()
	{
		return m_TechniqueName;
	}

	void D3D10Shader::SetMatrix(String VariableName, Matrix4 Matrix)
	{
		if(!m_Shader)
			return;

		ID3D10EffectVariable* Variable = m_Shader->GetVariableByName(VariableName.c_str());
		if(Variable)
		{
			Variable->AsMatrix()->SetMatrix(&Matrix[0]);
		}
	}

	void D3D10Shader::SetTexture(String VariableName, ITexture* Texture)
	{
		if(!m_Shader) 
			return;

		ID3D10EffectVariable* Variable = m_Shader->GetVariableByName(VariableName.c_str());
		if(Variable)
		{
			D3D10Texture* ShaderTexture = reinterpret_cast<D3D10Texture*>(Texture);
			Variable->AsShaderResource()->SetResource(ShaderTexture->GetD3D10ShaderResource());
		}
	}

	void D3D10Shader::SetFloat(String VariableName, float FloatingPointValue)
	{
		if(!m_Shader) 
			return;

		ID3D10EffectVariable* Variable = m_Shader->GetVariableByName(VariableName.c_str());
		if(Variable)
		{
			Variable->AsScalar()->SetFloat(FloatingPointValue);
		}
	}

	void D3D10Shader::SetBoolean(String VariableName, bool Boolean)
	{
		if(!m_Shader) 
			return;

		ID3D10EffectVariable* Variable = m_Shader->GetVariableByName(VariableName.c_str());
		if(Variable)
		{
			Variable->AsScalar()->SetBool(Boolean);
		}
	}

	void D3D10Shader::SetInteger(String VariableName, int Integer)
	{
		if(!m_Shader) 
			return;

		ID3D10EffectVariable* Variable = m_Shader->GetVariableByName(VariableName.c_str());
		if(Variable)
		{
			Variable->AsScalar()->SetInt(Integer);
		}
	}

	void D3D10Shader::SetRenderTarget(String VariableName, ISurface* Surface)
	{
		if(!m_Shader) 
			return;

		ID3D10EffectVariable* Variable = m_Shader->GetVariableByName(VariableName.c_str());
		if(Variable)
		{
			D3D10RenderTarget* RenderTarget = reinterpret_cast<D3D10RenderTarget*>(Surface);
			Variable->AsRenderTargetView()->SetRenderTarget(RenderTarget->GetTexture());
		}
	}

	bool D3D10Shader::GetVariableName(uint Index, String& VariableName)
	{
		ID3D10EffectVariable* Variable = m_Shader->GetVariableByIndex(Index);

		if(m_Shader->IsValid())
		{
			ArgonAssert(Variable);
			D3D10_EFFECT_VARIABLE_DESC Desc;
			Variable->GetDesc(&Desc);
			VariableName = Desc.Name;

			return (VariableName.Length() > 0);
		}
		return false;
	}

	IShader::VariableType D3D10Shader::GetVariableType(String VariableName)
	{
		ID3D10EffectVariable* Variable = m_Shader->GetVariableByName(VariableName.c_str());

		if(m_Shader->IsValid())
		{
			ArgonAssert(Variable);
			ID3D10EffectType* VariableType = Variable->GetType();
			
			ArgonAssert(VariableType);
			D3D10_EFFECT_TYPE_DESC Desc;
			VariableType->GetDesc(&Desc);

			switch(Desc.Type)
			{
				case D3D10_SVT_BOOL:
					return IShader::TYPE_Bool;
				case D3D10_SVT_STRING:
					return IShader::TYPE_String;
				case D3D10_SVT_TEXTURE2D:
					return IShader::TYPE_Texture2D;
				case D3D10_SVT_TEXTURE3D:
					return IShader::TYPE_Texture3D;
				case D3D10_SVT_DEPTHSTENCIL:
					return IShader::TYPE_DepthStencil;
				case D3D10_SVT_RENDERTARGETVIEW:
					return IShader::TYPE_RenderTarget;
				case D3D10_SVT_INT:
				{
					if(Desc.Columns == 0 && Desc.Rows == 1)
					{
						return IShader::TYPE_Integer;
					}
					else if(Desc.Columns == 2 && Desc.Rows == 1)
					{
						return IShader::TYPE_Vector2;
					}
					else if(Desc.Columns == 3 && Desc.Rows == 1)
					{
						return IShader::TYPE_Vector3;
					}

					break;				
				}
				case D3D10_SVT_FLOAT:
				{
					if(Desc.Columns == 0 && Desc.Rows == 1)
					{
						return IShader::TYPE_Float;
					}
					else if(Desc.Columns == 2 && Desc.Rows == 1)
					{
						return IShader::TYPE_Vector2;
					}
					else if(Desc.Columns == 3 && Desc.Rows == 1)
					{
						return IShader::TYPE_Vector3;
					}
					else if(Desc.Columns == 4 && Desc.Rows == 1)
					{
						return IShader::TYPE_Vector4;
					}
					else if(Desc.Columns == 3 && Desc.Rows == 3)
					{
						return IShader::TYPE_Matrix3;
					}
					else if(Desc.Columns == 4 && Desc.Rows == 4)
					{
						return IShader::TYPE_Matrix4;
					}

					break;				
				}
				default:
					return IShader::TYPE_Unknown;
			}
		}

		return IShader::TYPE_Unknown;
	}

	ID3D10EffectTechnique* D3D10Shader::GetBoundTechnique()
	{
		return m_BoundTechnique;
	}

	ID3D10EffectPass* D3D10Shader::GetBoundPass()
	{
		return m_BoundPass;
	}

} //Namespace