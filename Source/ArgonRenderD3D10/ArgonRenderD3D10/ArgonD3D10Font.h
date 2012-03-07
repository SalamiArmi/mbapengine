#ifndef _ARGOND3D10FONT_HEADER_
#define _ARGOND3D10FONT_HEADER_

#include <Interface/IFrameListner.h>
#include <Interface/IFont.h>

#include "ArgonD3D10RenderSystem.h"

namespace Argon
{
	class D3D10Font : IArgonUnknownImp<IFont, GUID_IFont>
	{
	public:
		D3D10Font(uint Height, uint Width, IFont::FontFlags Flags);

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
		bool Draw(String Text, Vector4 Col, Vector3 Position, Vector3 Scale, TextAlign Align);

		///UNBIND(BOOL)
		///
		/// Remove the font from the device and reset any render states
		///
		///No Params:
		bool UnBind();

	private:
		~D3D10Font();

		uint						m_Height;
		uint						m_Width;
		FontFlags					m_Flags;

		ID3DX10Font*				m_Font;
		static ID3DX10Sprite*		m_Sprite;
	};
} //Namespace

#endif //_ARGOND3D10FONT_HEADER_