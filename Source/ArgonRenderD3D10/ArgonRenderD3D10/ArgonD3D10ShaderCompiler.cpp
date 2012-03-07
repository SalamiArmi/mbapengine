#include "ArgonD3D10ShaderCompiler.h"

namespace Argon
{
	D3D10ShaderCompiler::D3D10ShaderCompiler()
	{
	}

	D3D10ShaderCompiler::~D3D10ShaderCompiler()
	{
	}

	ID3DBlob* D3D10ShaderCompiler::CompileShader(String FileName, ShaderModel Model)
	{
		ID3DBlob* Shader = NULL;
		ID3DBlob* ErrorBlob = NULL;
		char* ShaderModel = "fx_4_0";

		switch(Model)
		{
		case SHADERMODEL_FX_3_0:
			ShaderModel = "fx_3_0";
			break;
		case SHADERMODEL_FX_4_0:
			ShaderModel = "fx_4_0";
			break;
		}
		
		//Attempt to compile the shader
		HRESULT hr = D3DX10CompileFromFileA( FileName.c_str(), NULL, NULL, NULL, ShaderModel, NULL, NULL, NULL, &Shader, &ErrorBlob, NULL);
		assert((hr == S_OK) && Shader);
		if(ErrorBlob)
		{
			ErrorBlob->Release();
		}

		return Shader;
	}

	ID3DBlob* D3D10ShaderCompiler::CompileShader(String FileName, const char* ShaderData)
	{
		ID3DBlob* Shader = NULL;
		ID3DBlob* ErrorBlob = NULL;
		
		//Attempt to compile the shader
		HRESULT hr = D3DX10CompileFromMemory(ShaderData, strlen(ShaderData), FileName.c_str(), NULL, NULL, NULL, NULL, NULL, NULL, NULL, &Shader, &ErrorBlob, NULL);
		assert((hr == S_OK) && Shader);
		if(ErrorBlob)
		{
			ErrorBlob->Release();
		}

		return Shader;
	}

} //namespace