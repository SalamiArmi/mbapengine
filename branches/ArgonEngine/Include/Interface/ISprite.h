#ifndef _ARGONISPRITE_HEADER_
#define _ARGONISPRITE_HEADER_

#include <Interface/ArgonInterface.h>
#include <Interface/IArgonUnknown.h>
#include <Interface/ITexture.h>

#include <Standard/ArgonString.h>
#include <Standard/ArgonMatrix4.h>
#include <Standard/ArgonVector2.h>

//#include <Interface/IRenderSystem.h>

namespace Argon
{
	DeclareBasedInterface(ISprite, IArgonUnknown)

		///BIND(BOOL)
		///
		/// Set all resources to the device and set all the render states and preserve current states
		///
		///No Params:
		virtual bool Bind() = 0;

		///DRAW(BOOL)
		///
		/// Draw the Graphical object
		///
		///No Params:
		virtual bool Draw(bool Clear = true) = 0;

		///UNBIND(BOOL)
		///
		/// Remove the font from the device and reset any render states
		///
		///No Params:
		virtual bool UnBind() = 0;

		///ADDSPRITEINSTANCE(VOID)
		///
		/// Add a new sprite instance, each instance will be drawn on the draw call.
		///
		///Param Worldtransform: The sprite's model-world transformation. This defines the position and orientation of the sprite in world space.
		///Param TexCoord: Offset from the upper-left corner of the texture indicating where the sprite image should start in the texture. TexCoord is in texture coordinates.
		///Param TextureSize: A vector containing the width and height of the sprite in texture coordinates.
		///Param TextureResource: A texture that will represent this Sprites Instance Texture
		virtual bool AddSpriteInstance(Matrix4 Worldtransform, Vector2 TexCoord, Vector2 TextureSize, ITexture* TextureResource) = 0;

		///GETSPRITEINSTANCECOUNT(UINT)
		///
		/// Get the current amount of sprite instances in the draw list
		///
		///No Params:a
		virtual uint GetSpriteInstanceCount() = 0;

		///CLEARSPRITEINSTANCES(VOID)
		///
		/// Clear all the render instances from this Sprite
		///
		///No Params:
		virtual void ClearSpriteInstances() = 0;

		///SETTRANSFORM(VOID)
		///
		/// Remove the font from the device and reset any render states
		///
		///Param Type: Which type of matrix will be set
		///Param Matrix: The Matrix that will be bound the the sprite
		//virtual void SetTransform(IRenderSystem::MatrixType Type, Matrix4& Matrix) = 0;

	EndInterface(ISprite)

} //Namespace

#endif //_ARGONISPRITE_HEADER_