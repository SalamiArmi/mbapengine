#ifndef _ARGONGUIRESOURCE_HEADER_
#define _ARGONGUIRESOURCE_HEADER_

#include <Interface/ISprite.h>
#include <Interface/IFrameListner.h>

#include "ArgonGUIElement.h"

namespace Argon
{
	class GUIResource : public Entity, public Transform
	{
	public:
		GUIResource(String ResourceName);
		~GUIResource();

		///DRAW(BOOL)
		///
		///Draw the Graphical object
		///
		///Param Pass: The pass that will be preformed
		bool Draw(IFrameListner::RenderPass Pass);

		///SETTEXTURE(VOID)
		///
		///Set the texture that will be used when Rendering this $GUIResource$
		///
		///Param Texture: The texture that will be used to render
		void SetTexture(ITexture* Texture);

		///GETTEXTURE(ITEXTURE)
		///
		///Get the Texture being used to draw
		///
		///No Params:
		ITexture* GetTexture();

		///SETHOTSPOT(VECTOR2)
		///
		///Set the Hot spot of the texture
		///
		///Param HotSpot: The point on the Texture to start drawing from
		void SetHotSpot(Vector2 HotSpot);

		///GETHOTSPOT(ITEXTURE)
		///
		///Get the location of the hot spot
		///
		///No Params:
		Vector2& GetHotSpot();

		///SETDIMENSIONS(VECTOR2)
		///
		///Set the Width and the Height of the texture being drawn
		///
		///Param Dimensions: The Width and the Height of the texture being drawn
		void SetDimensions(Vector2 Dimensions);

		///GETDIMENSIONS(ITEXTURE)
		///
		///Get the Width and the Height of the texture being drawn
		///
		///No Params:
		Vector2& GetDimensions();

	private:
		Vector2		m_HotSpot;
		Vector2		m_Dimensions;

		ITexture*	m_Texture;
	}; //class
} //namespace

#endif //_ARGONGUIRESOURCE_HEADER_