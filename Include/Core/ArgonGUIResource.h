#ifndef _ARGONGUIRESOURCE_HEADER_
#define _ARGONGUIRESOURCE_HEADER_

#include <Interface/ISprite.h>
#include <Interface/IFrameListner.h>

#include <Interface/IArgonUnknownImp.h>
#include <Interface/IDrawable.h>

#include "ArgonTextureResource.h"

#include "ArgonEntity.h"

namespace Argon
{
	class GUIResource : public Entity, public IArgonUnknownImp<IDrawable, GUID_IDrawable>
	{
	public:
		GUIResource(String ResourceName);
		~GUIResource();

		///LOAD(BOOL)
		///
		///Load and init the Root
		///
		///No Params:
		bool Load();

		///SETTEXTURE(VOID)
		///
		///Set the texture that will be used when Rendering this $GUIResource$
		///
		///Param Texture: The texture that will be used to render
		void SetTexture(TextureResource* Texture);

		///GETTEXTURE(ITEXTURE)
		///
		///Get the Texture being used to draw
		///
		///No Params:
		TextureResource* GetTexture();

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

		///GETDIMENSIONS(GETRENDERORDER)
		///
		///Get the Renderorder for this $GUIResource$
		///
		///No Params:
		int& GetDrawOrder();

		///SETRENDERORDER(VOID)
		///
		///Set the Renderorder for this $GUIResource$
		///
		///Param DrawOrder: The new DrawOrder, the higher the number the later it will be drawn
		void SetDrawOrder(int DrawOrder);

	private:

		///SUPPORTSPASS(BOOL)
		///
		///Check if this Renderable Supports a pass
		///
		///Param Pass: The pass that will be checked against this is the current pass
		bool SupportsPass(IFrameListner::RenderPass Pass);

		///BIND(BOOL)
		///
		///Set all resources to the device and set all the render states and preserve current states
		///
		///No Params:
		bool Bind();

		///BIND(BOOL)
		///
		///Attempt to draw the Renderable
		///
		///No Params:
		bool FrameDraw();

		///UNBIND(BOOL)
		///
		/// Remove the Renderable from the device and reset any render states
		///
		///No Params:
		bool UnBind();

		int					m_DrawOrder;

		Vector2				m_HotSpot;
		Vector2				m_Dimensions;

		TextureResource*	m_Texture;
	}; //class
} //namespace

#endif //_ARGONGUIRESOURCE_HEADER_