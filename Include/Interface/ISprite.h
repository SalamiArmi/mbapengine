#ifndef _ARGONISPRITE_HEADER_
#define _ARGONISPRITE_HEADER_

namespace Argon
{
	DeclareBasedInterface(ISprite, IArgonUnknown)

		///BIND(BOOL)
		///
		/// Set all resources to the device and set all the render states and preserve current states
		///
		///No Params:
		bool Bind();

		///DRAW(BOOL)
		///
		/// Draw the Graphical object
		///
		///No Params:
		bool Draw(bool Clear = true);

		///UNBIND(BOOL)
		///
		/// Remove the font from the device and reset any render states
		///
		///No Params:
		bool UnBind();

		///ADDSPRITEINSTANCE(VOID)
		///
		/// Add a new sprite instance, each instance will be drawn on the draw call.
		///
		///Param Worldtransform: The sprite's model-world transformation. This defines the position and orientation of the sprite in world space.
		///Param TexCoord: Offset from the upper-left corner of the texture indicating where the sprite image should start in the texture. TexCoord is in texture coordinates.
		///Param TextureSize: A vector containing the width and height of the sprite in texture coordinates.
		///Param TextureResource: A texture that will represent this Sprites Instance Texture
		bool AddSpriteInstance(Matrix4 Worldtransform, Vector2 TexCoord, Vector2 TextureSize, ITexture* TextureResource);

		///GETSPRITEINSTANCECOUNT(UINT)
		///
		/// Get the current amount of sprite instances in the draw list
		///
		///No Params:a
		uint GetSpriteInstanceCount();

		///CLEARSPRITEINSTANCES(VOID)
		///
		/// Clear all the render instances from this Sprite
		///
		///No Params:
		void ClearSpriteInstances();

		///SETTRANSFORM(VOID)
		///
		/// Remove the font from the device and reset any render states
		///
		///Param MatrixType: Which type of matrix will be set
		///Param Matrix: The Matrix that will be bound the the sprite
		void SetTransform(IRenderSystem::MatrixType MatrixType, Matrix4& Matrix);

	EndInterface(ISprite)
} //Namespace

#endif //_ARGONIFONT_HEADER_