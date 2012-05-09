#ifndef _ISHADER_HEADER_
#define _ISHADER_HEADER_

#include <Standard/ArgonString.h>
#include <Interface/IArgonUnknown.h>
#include <Interface/ITexture.h>
#include <Interface/ISurface.h>

#include <Standard/ArgonMatrix4.h>

namespace Argon
{
	DeclareBasedInterface(IShader, IArgonUnknown) 

		enum VariableType
		{
			TYPE_Unknown,
			TYPE_Bool,
			TYPE_Integer,
			TYPE_Float,
			TYPE_Vector2,
			TYPE_Vector3,
			TYPE_Vector4,
			TYPE_Matrix3,
			TYPE_Matrix4,
			TYPE_String,
			TYPE_Texture2D,
			TYPE_Texture3D,
			TYPE_DepthStencil,
			TYPE_RenderTarget
		};

		///GETNAME(STRING)
		///
		///Get the Resource name of this shader
		///
		///No Params
		virtual String GetName() = 0;

		///BIND(BOOL)
		///
		///Attempt to bind the Shader to the rendering system
		///IF NO TECHNIQUE IS SET THE BIND WILL FAIL!
		///
		///Param Pass: The Technique Pass
		virtual bool Bind(ulong Pass) = 0;

		///UNBIND(BOOL)
		///
		///Unbind the shader from the RenderSystem
		///
		///No Param:
		virtual bool UnBind() = 0;

		///SETTECHNIQUE(VOID)
		///
		///Attempt to set the technique of the desired shader
		///
		///Param TechniqueName: The Technique that will be set in the shader
		virtual bool SetTechnique(String TechniqueName) = 0;

		///SETTECHNIQUE(STRING)
		///
		///Get the current Technique name
		///
		///No Params:
		virtual String GetTechnique() = 0;

		///SETMATRIX(VOID)
		///
		///Attempt to set the technique of the desired shader
		///
		///Param TechniqueName: The Technique that will be set in the shader
		virtual void SetMatrix(String VariableName, Matrix4 Matrix) = 0;

		///SETTEXTURE(VOID)
		///
		///Attempt to set the Texture to the Variable with the Name(VariableName)
		///
		///Param VariableName: The Global Variable in String form
		///Param Texture: The Texture that will be assigned to the shader
		virtual void SetTexture(String VariableName, ITexture* Texture) = 0;

		///SETFLOAT(VOID)
		///
		///Attempt to set the FloatingValue to the Variable with the Name(VariableName)
		///
		///Param VariableName: The Global Variable in String form 
		///Param FloatingPointValue: The Floating Value that will be assigned to the shader
		virtual void	SetFloat(String VariableName, float FloatingPointValue)		= 0;

		///SETBOOLEAN(VOID)
		///
		///Attempt to set the Boolean to the Variable with the Name(VariableName)
		///
		///Param VariableName: The Global Variable in String form
		///Param Boolean: The Boolean that will be assigned to the shader
		virtual void	SetBoolean(String VariableName, bool Boolean)		= 0;

		///SETINTEGER(VOID)
		///
		///Attempt to set the Integer to the Variable with the Name(VariableName)
		///
		///Param VariableName: The Global Variable in String form
		///Param Integer: The Integer that will be assigned to the shader
		virtual void	SetInteger(String VariableName, int Integer)		= 0;

		///SETRENDERTARGET(VOID)
		///
		///Attempt to set the RenderTarget to the Variable with the Name(VariableName)
		///
		///Param VariableName: The Global Variable in String form
		///Param Surface: The Texture that will be assigned to the shader
		virtual void	SetRenderTarget(String VariableName, ISurface* Surface)		= 0;

		///GETVARIABLENAME(BOOL)
		///
		///Attempt to get the name of a Variable in the Shader
		///
		///Param Index: The index of the Variable that is being retrieved
		///Param Surface: The name of the Variable will be placed into here.
		virtual bool GetVariableName(uint Index, String& VariableName);

		///GETVARIABLETYPE(TYPE)
		///
		///Attempt to get the $Type$ of a Variable in the Shader
		///
		///Param VariableName: The name of the Variable
		virtual VariableType GetVariableType(String VariableName);

	EndInterface(IShader) //Interface
} //Namespace

#endif //_ISHADER_HEADER_