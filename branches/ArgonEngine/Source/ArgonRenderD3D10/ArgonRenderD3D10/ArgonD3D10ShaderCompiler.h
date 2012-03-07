#ifndef _ARGOND3D10SHADERCOMPILER_
#define _ARGOND3D10SHADERCOMPILER_

#include <Standard/ArgonSingleton.h>
#include <Standard/ArgonString.h>

#include "ArgonD3D10Device.h"

namespace Argon
{
	class D3D10ShaderCompiler : public singleton<D3D10ShaderCompiler>
	{
	public:

		enum ShaderModel
		{
			SHADERMODEL_FX_4_0 = 0,
			SHADERMODEL_FX_3_0,
		};

		D3D10ShaderCompiler();
		
		///COMPILESHADER(ID3D10BLOB)
		///
		/// Compile a shader from a HLSL file.
		///
		///Param FileName: The File to compile from
		///Param Model: The shader model type that will be used to compile
		ID3DBlob* CompileShader(String FileName, ShaderModel Model);

		///COMPILESHADER(ID3D10BLOB)
		///
		/// Compile a shader from a compiled block of memory
		///
		///Param ShaderData: The file data in binary format
		///Param FileName: The File to compile from
		ID3DBlob* CompileShader(String FileName, const char* ShaderData);

		///COMPILESHADER(VOID)
		///
		/// Compile a shader into binary file then save to the desired file.
		///
		///Params FromFile: The HLSL Shader that will be compiled
		///Params ToFile: The new binary file that will be saved to the harddrive
		void		SaveToFile(String FromFile, String ToFIle);

	protected:
		~D3D10ShaderCompiler();
	};
} //namespace

#endif //_ARGOND3D10SHADERCOMPILER_