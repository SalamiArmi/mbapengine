#ifndef _ARGOND3D10SPRITE_HEADER_
#define _ARGOND3D10SPRITE_HEADER_

#include <Interface/ISprite.h>
#include <Interface/IArgonUnknownImp.h>

#include <Standard/ArgonVector.h>

#include "ArgonD3D10RenderSystem.h"

namespace Argon
{
	class D3D10Sprite : public IArgonUnknownImp<ISprite, GUID_ISprite>
	{
	public:
		D3D10Sprite(uint InstanceMax);
		~D3D10Sprite();

		///LOAD(BOOL)
		///
		///Load the Interface All interfaces must use this
		///
		///No Params:
		bool Load();

		///RELEASE(BOOL)
		///
		///Either Release a reference or release the object
		///
		///No Params:
		bool UnLoad();

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
		bool Draw(bool Clear);

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
		///No Params:
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
		///Param Type: Which type of matrix will be set
		///Param Matrix: The Matrix that will be bound the the sprite
		void SetTransform(IRenderSystem::MatrixType Type, Matrix4& Matrix);

	private:
		Vector<D3DX10_SPRITE>	m_BufferedSprites;
		ID3DX10Sprite*			m_Sprite;
		uint					m_InstanceMax;
	}; //Class
} //Namespace

#endif //_ARGOND3D10SPRITE_HEADER_