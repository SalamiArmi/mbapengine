#ifndef _ARGOND3D10SHADER_HEADER_
#define _ARGOND3D10SHADER_HEADER_

#include <Standard/ArgonVector.h>
#include <Interface/IShader.h>

#include "ArgonD3D10RenderSystem.h"

namespace Argon
{
	class D3D10Shader : public IArgonUnknownImp<IShader, GUID_IShader>
	{
	public:
		D3D10Shader(String Name, String ShaderBuffer);
		~D3D10Shader();

		///LOAD(BOOLEAN)
		///
		///
		///
		///No Param:
		bool	Load();

		///UNLOAD(BOOLEAN)
		///
		///
		///
		///No Param:
		bool	UnLoad();

		///GETNAME(STRING)
		///
		///Get the Resource name of this shader
		///
		///No Params
		String GetName();

		///BIND(BOOL)
		///
		///Attempt to bind the Shader to the rendering system
		///IF NO TECHNIQUE IS SET THE BIND WILL FAIL!
		///
		///Param Pass: The Technique Pass
		bool	Bind(ulong Pass);

		///UNBIND(BOOL)
		///
		///Unbind the shader from the RenderSystem
		///
		///No Param:
		bool	UnBind();

		///SETTECHNIQUE(VOID)
		///
		///Attempt to set the technique of the desired shader
		///
		///Param TechniqueName: The Technique that will be set in the shader
		bool	SetTechnique(String TechniqueName);

		///SETTECHNIQUE(STRING)
		///
		///Get the current Technique name
		///
		///No Params:
		String	GetTechnique();

		///SETMATRIX(VOID)
		///
		///Attempt to set the technique of the desired shader
		///
		///Param TechniqueName: The Technique that will be set in the shader
		void	SetMatrix(String VariableName, Matrix4 Matrix);

		///SETTEXTURE(VOID)
		///
		///Attempt to set the Texture to the Variable with the Name(VariableName)
		///
		///Param VariableName: The Global Variable in String form
		///Param Texture: The Texture that will be assigned to the shader
		void	SetTexture(String VariableName, ITexture* Texture);

		///SETFLOAT(VOID)
		///
		///Attempt to set the FloatingValue to the Variable with the Name(VariableName)
		///
		///Param VariableName: The Global Variable in String form 
		///Param FloatingPointValue: The Floating Value that will be assigned to the shader
		void	SetFloat(String VariableName, float FloatingPointValue);

		///SETBOOLEAN(VOID)
		///
		///Attempt to set the Boolean to the Variable with the Name(VariableName)
		///
		///Param VariableName: The Global Variable in String form
		///Param Boolean: The Boolean that will be assigned to the shader
		void	SetBoolean(String VariableName, bool Boolean);

		///SETINTEGER(VOID)
		///
		///Attempt to set the Integer to the Variable with the Name(VariableName)
		///
		///Param VariableName: The Global Variable in String form
		///Param Integer: The Integer that will be assigned to the shader
		void	SetInteger(String VariableName, int Integer);

		///SETRENDERTARGET(VOID)
		///
		///Attempt to set the RenderTarget to the Variable with the Name(VariableName)
		///
		///Param VariableName: The Global Variable in String form
		///Param Surface: The Texture that will be assigned to the shader
		void	SetRenderTarget(String VariableName, ISurface* Surface);

		///GETVARIABLENAME(BOOL)
		///
		///Attempt to get the name of a Variable in the Shader
		///
		///Param Index: The index of the Variable that is being retrieved
		///Param Surface: The name of the Variable will be placed into here.
		bool GetVariableName(uint Index, String& VariableName);

		///GETVARIABLETYPE(TYPE)
		///
		///Attempt to get the $Type$ of a Variable in the Shader
		///
		///Param VariableName: The name of the Variable
		VariableType GetVariableType(String VariableName);

		///GETBOUNDTECHNIQUE(ID3D10EFFECTTECHNIQUE)
		///
		///Get the currently Bound Technique
		///
		///No Param:
		ID3D10EffectTechnique* GetBoundTechnique();

		///GETBOUNDPASS(ID3D10EFFECTPASS)
		///
		///Get the currently Bound Pass
		///
		///No Param:
		ID3D10EffectPass* GetBoundPass();

	private:
		String						m_Name;
		String						m_ShaderBuffer;
		String						m_TechniqueName;

		ID3D10Effect*				m_Shader;
		ID3D10EffectTechnique*		m_BoundTechnique;
		ID3D10EffectPass*			m_BoundPass;
	};
}//Namespace

#endif //_ARGOND3D10SHADER_HEADER_