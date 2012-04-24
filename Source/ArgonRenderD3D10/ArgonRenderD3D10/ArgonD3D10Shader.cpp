#include "ArgonD3D10Shader.h"
#include "ArgonD3D10Texture.h"
#include "ArgonD3D10RenderTarget.h"
#include <Standard/ArgonString.h>

namespace Argon
{
	D3D10Shader::D3D10Shader(const char* ShaderBuffer)
		: m_ShaderBuffer(ShaderBuffer),
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
		return (m_BoundTechnique != NULL);
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

	ID3D10EffectTechnique* D3D10Shader::GetBoundTechnique()
	{
		return m_BoundTechnique;
	}

	ID3D10EffectPass* D3D10Shader::GetBoundPass()
	{
		return m_BoundPass;
	}

} //Namespace